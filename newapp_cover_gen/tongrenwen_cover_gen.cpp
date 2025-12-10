#include <cairo.h>
#include <fontconfig/fontconfig.h>
#include <pango/pangocairo.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include "cmdline.h"


struct RGBA {
    double r, g, b, a;
};

RGBA hexToRGBA(const std::string& hex) {
    if (hex.size() != 9 || hex[0] != '#') {
        throw std::invalid_argument("Invalid hex format. Expected format: #RRGGBBAA");
    }

    int r, g, b, a;
    std::stringstream ss;

    ss << std::hex << hex.substr(1, 2);
    ss >> r;
    ss.clear(); ss.str("");

    ss << std::hex << hex.substr(3, 2);
    ss >> g;
    ss.clear(); ss.str("");

    ss << std::hex << hex.substr(5, 2);
    ss >> b;
    ss.clear(); ss.str("");

    ss << std::hex << hex.substr(7, 2);
    ss >> a;

    return RGBA{r / 255.0, g / 255.0, b / 255.0, a / 255.0};
}

// 将数字转换为 PangoWeight 枚举
PangoWeight get_pango_weight_from_int(int weight) {
    if (weight <= 100) return PANGO_WEIGHT_THIN;
    if (weight <= 200) return PANGO_WEIGHT_ULTRALIGHT;
    if (weight <= 300) return PANGO_WEIGHT_LIGHT;
    if (weight <= 400) return PANGO_WEIGHT_NORMAL;
    if (weight <= 500) return PANGO_WEIGHT_MEDIUM;
    if (weight <= 600) return PANGO_WEIGHT_SEMIBOLD;
    if (weight <= 700) return PANGO_WEIGHT_BOLD;
    if (weight <= 800) return PANGO_WEIGHT_ULTRABOLD;
    return PANGO_WEIGHT_HEAVY;  // 大于 800 时使用 PANGO_WEIGHT_HEAVY
}

bool is_emoji(UChar32 ch) {
    return u_hasBinaryProperty(ch, UCHAR_EMOJI);
}

// 在emoji后面插入一个空格
std::string add_space(const std::string& text) {
    icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(text);
    std::string utf8_text;
    ustr.toUTF8String(utf8_text);  // 获取 UTF-8 版本的文本

    icu::UnicodeString added_text;

    int32_t start = 0;
    while (start < ustr.length()) {
        UChar32 ch = ustr.char32At(start);
        int32_t char_len = U16_LENGTH(ch);
        
        added_text.append(ustr, start, char_len); // 追加当前字符

        if (is_emoji(ch)) {
            added_text.append((UChar32)0x2006); // 插入零宽空格
        }

        start += char_len;  // 移动到下一个字符
    }

    std::string result;
    added_text.toUTF8String(result); // 将icu::UnicodeString转换为UTF-8 std::string
    return result;
}

// 解析字符串，将文字和 Emoji 分离，并生成 Pango Markup
std::string generate_markup_with_line_limit(const std::string& text, 
                                            const std::string& font_family, const double& font_size, const double& font_weight,
                                            const std::string& emoji_font_family, const double& emoji_size, 
                                            const double& dpi_scale, const int& max_line_count) {
    icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(text);
    std::string utf8_text;
    ustr.toUTF8String(utf8_text);  // 获取 UTF-8 版本的文本
    std::ostringstream markup;
    
    // 设置普通文本的 span
    markup << "<span font_desc='" << font_family << "' size='" << static_cast<int>(font_size * PANGO_SCALE * dpi_scale) << "' weight='" << font_weight << "'>";

    std::string text_buffer;
    int32_t start = 0;
    
    while (start < ustr.length()) {
        UChar32 ch = ustr.char32At(start);
        int32_t char_len = U16_LENGTH(ch);
        
        // 获取正确的 UTF-8 位置
        std::string utf8_substring;
        ustr.tempSubStringBetween(start, start + char_len).toUTF8String(utf8_substring);
        int utf8_start = utf8_text.find(utf8_substring);
        int utf8_end = utf8_start + utf8_substring.length();

        if (utf8_start == std::string::npos) {
            start += char_len;
            continue;
        }

        if (is_emoji(ch)) {
            // 结束当前文字 span
            if (!text_buffer.empty()) {
                markup << text_buffer;
                text_buffer.clear();
            }

            // 处理 Emoji
            std::string utf8_char;
            icu::UnicodeString(ch).toUTF8String(utf8_char);
            markup << "</span><span font_desc='" << emoji_font_family 
                << "' size='" << static_cast<int>(emoji_size * PANGO_SCALE * dpi_scale)
                << "' weight='" << font_weight
                << "'>" << utf8_char
                << "</span><span font_desc='" << font_family 
                << "' size='" << static_cast<int>(font_size * PANGO_SCALE * dpi_scale) 
                << "' weight='" << font_weight
                << "'>";
        } else {
            std::string utf8_char;
            icu::UnicodeString(ch).toUTF8String(utf8_char);
            text_buffer += utf8_char;
        }

        start += char_len;  // 移动到下一个字符
    }

    // 输出剩余的文本
    if (!text_buffer.empty()) {
        markup << text_buffer;
    }

    markup << "</span>";
    return markup.str();
}

std::string load_font_family(const std::string& font_path) {
    FcConfig* config = FcInitLoadConfigAndFonts();
    FcPattern* pattern = FcNameParse((const FcChar8*)font_path.c_str());
    FcConfigSubstitute(config, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult result;
    FcPattern* matched_pattern = FcFontMatch(config, pattern, &result);
    std::string font_family;

    if (matched_pattern) {
        FcChar8* font_family_cstr = nullptr;
        if (FcPatternGetString(matched_pattern, FC_FAMILY, 0, &font_family_cstr) == FcResultMatch) {
            font_family = reinterpret_cast<char*>(font_family_cstr);
        }
    }

    FcPatternDestroy(pattern);
    FcConfigDestroy(config);

    return font_family;
}

// 创建文本贴图
cairo_surface_t* draw_text_to_surface(const std::string& text, 
                                      const std::string& font_path, const double& font_size, const double& font_weight, 
                                      const double& emoji_scale, const double& dpi_scale, 
                                      const double& line_spacing, const double& letter_spacing, 
                                      const double& r, const double& g, const double& b, const double& a, 
                                      const double& width, const int& max_line_count, 
                                      double& out_height, int& line_count) {
    // 创建足够大的画布
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, 1000);
    cairo_t* cr = cairo_create(surface);

    // 创建 Pango 布局
    PangoLayout* layout = pango_cairo_create_layout(cr);
    
    // 初始化 FontConfig
    std::string font_family = load_font_family(font_path);
    if (font_family.empty()) {
        font_family = "PingFang SC";
    }

    // 创建属性列表
    PangoAttrList* attr_list = pango_attr_list_new();

    // 字间距
    PangoAttribute* letter_spacing_attr = pango_attr_letter_spacing_new(letter_spacing * PANGO_SCALE);
    pango_attr_list_insert(attr_list, letter_spacing_attr);
    pango_layout_set_attributes(layout, attr_list);

    // 生成带 Emoji 处理的 Pango Markup
    std::string markup_text = generate_markup_with_line_limit(text, font_family, font_size, font_weight, "Apple Color Emoji", font_size * emoji_scale, dpi_scale, max_line_count);

    pango_layout_set_markup(layout, markup_text.c_str(), -1);

    // 设置文字区域宽度
    pango_layout_set_width(layout, width * PANGO_SCALE);
    
    // 文字换行逻辑
    pango_layout_set_wrap(layout, PANGO_WRAP_WORD_CHAR);

    // 左对齐
    pango_layout_set_justify(layout, FALSE);

    // 设置行间距
    pango_layout_set_line_spacing(layout, line_spacing);

    // 获取行数
    line_count = pango_layout_get_line_count(layout);

    // 如果行数超过 max_line_count，需要截断文本
    while (line_count > max_line_count) {
        // 获取第max_line_count行索引
        PangoLayoutLine* last_line = pango_layout_get_line(layout, max_line_count);
        if (last_line) {
            int start_index = last_line->start_index;  // 获取该行的起始位置

            // 预留 3 个字符给 "..."
            if (start_index > 3) {
                start_index -= 3;
            }

            // 截取文本，并添加 "..."
            std::string truncated_text = text.substr(0, start_index) + "...";

            // 重新设置 Pango 布局
            markup_text = generate_markup_with_line_limit(truncated_text, font_family, font_size, font_weight, 
                                                          "Apple Color Emoji", font_size * emoji_scale, dpi_scale, max_line_count);
            pango_layout_set_markup(layout, markup_text.c_str(), -1);
            line_count = pango_layout_get_line_count(layout);
        }
    }

    // 获取文本大小
    int text_width, text_height;
    pango_layout_get_size(layout, &text_width, &text_height);
    text_width /= PANGO_SCALE;
    text_height /= PANGO_SCALE;

    out_height = text_height;

    // 重新创建合适大小的画布
    cairo_surface_t* final_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, text_height);
    cairo_t* final_cr = cairo_create(final_surface);

    // 填充透明背景
    cairo_set_source_rgba(final_cr, 1, 1, 1, 0);
    cairo_paint(final_cr);

    // 设定文本颜色
    cairo_set_source_rgba(final_cr, r, g, b, a);
    cairo_move_to(final_cr, 0, 0);
    pango_cairo_update_layout(final_cr, layout);
    pango_cairo_show_layout(final_cr, layout);

    // 清理
    pango_attr_list_unref(attr_list);
    g_object_unref(layout);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    cairo_destroy(final_cr);

    // 返回绘制的表面
    return final_surface;
}

// 组合两段文本
cairo_surface_t* combine_text_surfaces(cairo_surface_t* title_surface, cairo_surface_t* body_surface, const double& width, const double& title_height, const double& body_height, const double& spacing) {
    double total_height = title_height + spacing + body_height;
    cairo_surface_t* combined_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, total_height);
    cairo_t* cr = cairo_create(combined_surface);

    // 填充透明背景
    cairo_set_source_rgba(cr, 1, 1, 1, 0);
    cairo_paint(cr);

    // 贴上标题
    cairo_set_source_surface(cr, title_surface, 0, 0);
    cairo_paint(cr);

    // 贴上正文
    cairo_set_source_surface(cr, body_surface, 0, title_height + spacing);
    cairo_paint(cr);

    cairo_destroy(cr);
    return combined_surface;
}

// 将文本贴图粘贴到背景图
void apply_text_to_background(const std::string& bg_path, cairo_surface_t* text_surface, const std::string& output_path) {
    cairo_surface_t* bg_surface = cairo_image_surface_create_from_png(bg_path.c_str());
    cairo_t* cr = cairo_create(bg_surface);

    int bg_width = cairo_image_surface_get_width(bg_surface);
    int bg_height = cairo_image_surface_get_height(bg_surface);
    int text_width = cairo_image_surface_get_width(text_surface);
    int text_height = cairo_image_surface_get_height(text_surface);

    double x = (bg_width - text_width) / 2.0;
    double y = (bg_height - text_height) / 2.0;

    cairo_set_source_surface(cr, text_surface, x, y);
    cairo_paint(cr);

    cairo_surface_write_to_png(bg_surface, output_path.c_str());

    cairo_destroy(cr);
    cairo_surface_destroy(bg_surface);
}

void surface_write_to_png(cairo_surface_t* title_surface, const std::string& output_path) {
    // 目标图片尺寸
    int img_width = cairo_image_surface_get_width(title_surface);
    int img_height = cairo_image_surface_get_height(title_surface);

    // 创建新的白色背景的画布
    cairo_surface_t* final_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, img_width, img_height);
    cairo_t* cr = cairo_create(final_surface);

    // 填充白色背景
    cairo_set_source_rgb(cr, 1, 1, 1);  // RGB(1,1,1) 代表白色
    cairo_paint(cr);

    // 贴上文字贴图
    cairo_set_source_surface(cr, title_surface, 0, 0);
    cairo_paint(cr);

    // 保存最终图片
    cairo_surface_write_to_png(final_surface, output_path.c_str());
}

void parse_init(cmdline::parser& cmd_parser) {
    cmd_parser.add<std::string>("title", 't', "标题文本", true, "默认标题");
    cmd_parser.add<std::string>("body", 'b', "正文文本", true, "默认正文");
    cmd_parser.add<std::string>("bg_path", 'i', "背景图路径", true, "../封面图导出.png");
    cmd_parser.add<std::string>("output_path", 'o', "输出文件路径", true, "../同人文.png");

    cmd_parser.add<double>("bg_scale", 0, "放大比例", false, 1.0);
    cmd_parser.add<double>("width", 0, "统一宽度", false, 145);
    cmd_parser.add<double>("spacing", 0, "标题与正文间距", false, 14);
    cmd_parser.add<double>("emoji_scale", 0, "emoji缩放比例", false, 0.8);
    cmd_parser.add<double>("dpi_scale", 0, "DPI缩放比例", false, 0.75);

    cmd_parser.add<std::string>("title_font", 0, "标题字体", false, "PingFang SC");
    cmd_parser.add<double>("title_font_size", 0, "标题字号", false, 15.0);
    cmd_parser.add<double>("title_font_weight", 0, "标题字重", false, 500);
    cmd_parser.add<double>("title_line_spacing", 0, "标题行间距", false, 1.0);
    cmd_parser.add<double>("title_letter_spacing", 0, "标题字间距", false, 0);
    cmd_parser.add<std::string>("title_color", 0, "标题颜色", false, "#101214D9");

    cmd_parser.add<std::string>("body_font", 0, "正文字体", false, "PingFang SC");
    cmd_parser.add<double>("body_font_size", 0, "正文字号", false, 14.0);
    cmd_parser.add<double>("body_font_weight", 0, "正文字重", false, 300);
    cmd_parser.add<double>("body_line_spacing", 0, "正文行间距", false, 1.25);
    cmd_parser.add<double>("body_letter_spacing", 0, "正文字间距", false, 0);
    cmd_parser.add<std::string>("body_color", 0, "正文颜色", false, "#101214B2");

    cmd_parser.add<int>("title_max_line_count", 0, "标题最大行数", false, 3);
    cmd_parser.add<int>("max_line_count", 0, "总最大行数", false, 8);
}

int main(int argc, char* argv[]) {
    cmdline::parser cmd_parser;
    parse_init(cmd_parser);
    cmd_parser.parse_check(argc, argv);


    std::string title_text = cmd_parser.get<std::string>("title");
    std::string body_text = cmd_parser.get<std::string>("body");
    std::cout << title_text << std::endl;
    std::cout << body_text << std::endl;
    std::string bg_path = cmd_parser.get<std::string>("bg_path");
    std::string output_path = cmd_parser.get<std::string>("output_path");

    double BG_SCALE = cmd_parser.get<double>("bg_scale"); // 放大比例
    double WIDTH = cmd_parser.get<double>("width") * BG_SCALE; // 统一宽度
    double SPACING = cmd_parser.get<double>("spacing") * BG_SCALE; // 标题与正文间距
    double EMOJI_SCALE = cmd_parser.get<double>("emoji_scale"); // emoji缩放比例
    double DPI_SCALE = cmd_parser.get<double>("dpi_scale"); // DPI缩放比例

    std::string TITLE_FONT = cmd_parser.get<std::string>("title_font");         // 标题字体
    double TITLE_FONT_SIZE = cmd_parser.get<double>("title_font_size") * BG_SCALE;   // 标题字号
    double TITLE_FONT_WEIGHT = cmd_parser.get<double>("title_font_weight");           // 标题字重
    double TITLE_LINE_SPACING = cmd_parser.get<double>("title_line_spacing");            // 标题行间距比例
    double TITLE_LETTER_SPACING = cmd_parser.get<double>("title_letter_spacing");          // 标题字间距
    RGBA TITLE_COLOR = hexToRGBA(cmd_parser.get<std::string>("title_color"));    // 标题颜色

    std::string BODY_FONT = cmd_parser.get<std::string>("body_font");          // 正文字体
    double BODY_FONT_SIZE = cmd_parser.get<double>("body_font_size") * BG_SCALE;    // 正文字号
    double BODY_FONT_WEIGHT = cmd_parser.get<double>("body_font_weight");            // 正文字重
    double BODY_LINE_SPACING = cmd_parser.get<double>("body_line_spacing");          // 正文行间距比例
    double BODY_LETTER_SPACING = cmd_parser.get<double>("body_letter_spacing");           // 正文字间距
    RGBA BODY_COLOR = hexToRGBA(cmd_parser.get<std::string>("body_color"));     // 正文颜色

    int TITLE_MAX_LINE_COUNT = cmd_parser.get<int>("title_max_line_count");;             // 标题最大行数
    int MAX_LINE_COUNT = cmd_parser.get<int>("max_line_count");;                   // 最大行数


    double title_height, body_height;
    int title_line_count, body_line_count;
    cairo_surface_t* title_surface = draw_text_to_surface(add_space(title_text), TITLE_FONT, TITLE_FONT_SIZE, TITLE_FONT_WEIGHT, EMOJI_SCALE, DPI_SCALE, TITLE_LINE_SPACING, TITLE_LETTER_SPACING, TITLE_COLOR.r, TITLE_COLOR.g, TITLE_COLOR.b, TITLE_COLOR.a, WIDTH, TITLE_MAX_LINE_COUNT, title_height, title_line_count);

    cairo_surface_t* body_surface = draw_text_to_surface(add_space(body_text), BODY_FONT, BODY_FONT_SIZE, BODY_FONT_WEIGHT, EMOJI_SCALE, DPI_SCALE, BODY_LINE_SPACING, BODY_LETTER_SPACING,  BODY_COLOR.r, BODY_COLOR.g, BODY_COLOR.b, BODY_COLOR.a, WIDTH,MAX_LINE_COUNT - title_line_count, body_height, body_line_count);

    cairo_surface_t* text_surface = combine_text_surfaces(title_surface, body_surface, WIDTH, title_height, body_height, SPACING);

    apply_text_to_background(bg_path, text_surface, output_path);

    cairo_surface_destroy(title_surface);
    cairo_surface_destroy(body_surface);
    cairo_surface_destroy(text_surface);

    std::cout << "同人文封面图已生成，保存至" << output_path << std::endl;

    return 0;
}