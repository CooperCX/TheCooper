#include <cairo.h>
#include <pango/pangocairo.h>
#include <iostream>
#include <string>
#include <vector>
#include <unicode/unistr.h>
#include <fontconfig/fontconfig.h>

#include "cppjieba/include/cppjieba/Jieba.hpp"
#include "timer.h"

// 初始化静态成员变量
std::map<std::string, long long> Timer::totalTime;
std::chrono::high_resolution_clock::time_point Timer::globalStart;

// 定义 jieba 分词所需的词典路径
const char *const DICT_PATH = "/Users/chengxun01/baidu/code/baidu/newapp/newapp_cover_gen/cppjieba/dict/jieba.dict.utf8";  // 词典文件
const char *const HMM_PATH = "/Users/chengxun01/baidu/code/baidu/newapp/newapp_cover_gen/cppjieba/dict/hmm_model.utf8";    // HMM 模型文件
const char *const USER_DICT_PATH = "/Users/chengxun01/baidu/code/baidu/newapp/newapp_cover_gen/cppjieba/dict/user.dict.utf8"; // 用户词典文件（可选）
const char *const IDF_PATH = "/Users/chengxun01/baidu/code/baidu/newapp/newapp_cover_gen/cppjieba/dict/idf.utf8";          // IDF 文件（可选）
const char *const STOP_WORD_PATH = "/Users/chengxun01/baidu/code/baidu/newapp/newapp_cover_gen/cppjieba/dict/stop_words.utf8"; // 停用词文件（可选）
cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
cppjieba::KeywordExtractor extractor(DICT_PATH, HMM_PATH, IDF_PATH, STOP_WORD_PATH);

// 定义分词函数
std::vector<std::string> segmentText(const std::string& text) {
    std::vector<std::string> words;
    jieba.Cut(text, words);

    return words;
}

// 分词并提取关键词
int segmentTextAndExtractTopKeyword(const std::string& text, std::vector<std::string>& words) {
    Timer t("segmentTextAndExtractTopKeyword");
    jieba.Cut(text, words);

    // 提取关键词
    std::vector<std::pair<std::string, double>> key_words;
    extractor.Extract(text, key_words, 5); // 提取前5个关键词

    for (const auto& keyword : key_words) {
        const std::string& key = keyword.first;
        for (size_t i = 0; i < words.size(); ++i) {
            if (words[i] == key) {
                return static_cast<int>(i);  // 返回关键词的索引
            }
        }
    }

    return -1;
}

bool is_emoji(const std::string& str) {
    // 使用 ICU 库来检测是否为 emoji
    icu::UnicodeString unicode_str(str.c_str(), str.size());
    // 检查字符是否属于 Emoji 范围
    UChar32 ch = unicode_str[0];
    return (ch >= 0xD800 && ch <= 0xDBFF) || (ch >= 0xDC00 && ch <= 0xDFFF) || (ch >= 0x1F600 && ch <= 0x1F64F);
}

// 传入 TTF 字体文件路径，返回可用的 PangoFontDescription
PangoFontDescription* load_ttf_font(const char* font_path) {
    FcConfig* config = FcInitLoadConfigAndFonts();
    if (!config) {
        std::cerr << "FontConfig 初始化失败" << std::endl;
        return nullptr;
    }

    // 添加字体到 FontConfig
    if (!FcConfigAppFontAddFile(config, (const FcChar8*)font_path)) {
        std::cerr << "加载字体失败: " << font_path << std::endl;
        FcConfigDestroy(config);
        return nullptr;
    }

    // 重新扫描字体库
    FcConfigSetCurrent(config);
    FcConfigBuildFonts(config);

    // 通过 TTF 文件路径获取字体名称
    FcPattern* pattern = FcNameParse((const FcChar8*)font_path);
    FcConfigSubstitute(config, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult result;
    FcPattern* font = FcFontMatch(config, pattern, &result);
    if (!font) {
        std::cerr << "无法匹配字体" << std::endl;
        return nullptr;
    }

    // 获取字体名称
    FcChar8* family = nullptr;
    if (FcPatternGetString(font, FC_FAMILY, 0, &family) == FcResultMatch) {
        // std::cout << "成功加载字体: " << family << std::endl;
        return pango_font_description_from_string((const char*)family);
    }

    std::cerr << "无法解析字体名称" << std::endl;
    return nullptr;
}

void draw_text(cairo_t* cr,
               const std::vector<std::string>& words, int keyword_index,
               double x, double y, double width, double height,
               const char* font_path = "../ttf/PingFang HK Regular.ttf", 
               const char* emoji_font = "Apple Color Emoji",
               double min_font_size = 10,
               double emoji_ratio = 0.8,
               double line_spacing = 1.1,
               double word_spacing = 0.1,
               const std::array<double, 3>& keyword_color = {1.0, 0.0, 1.0},
               const std::array<double, 3>& normal_color = {0.0, 0.0, 0.0}) {
    Timer t("draw_text");
    PangoLayout* layout = pango_cairo_create_layout(cr);
    PangoFontDescription* desc = load_ttf_font(font_path);
    PangoFontDescription* emoji_desc = pango_font_description_from_string(emoji_font);

    double low = min_font_size;
    double high = std::min(width, height);
    double font_size = high;  // 先尝试最大可能字体
    double emoji_size = font_size * emoji_ratio; // emoji大小

    while (high - low > 1) {  // 控制精度，防止无限循环
        font_size = (low + high) / 2;  // 取中间值
        emoji_size = font_size * emoji_ratio;
        cairo_save(cr);
        cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
        cairo_paint(cr);
        cairo_restore(cr);
        // 设置字体大小
        pango_font_description_set_size(desc, font_size * PANGO_SCALE);
        pango_font_description_set_size(emoji_desc, emoji_size * PANGO_SCALE);
        pango_layout_set_font_description(layout, desc);

        // 计算行间距和字间距
        int font_width, font_height;
        pango_layout_get_pixel_size(layout, &font_width, &font_height);
        double line_height = font_height * line_spacing;
        double char_spacing = font_width * word_spacing;

        double current_x = x;
        double current_y = y;
        bool overflow = false;

        for (size_t i = 0; i < words.size(); ++i) {
            if (i == static_cast<size_t>(keyword_index)) {
                cairo_set_source_rgb(cr, keyword_color[0], keyword_color[1], keyword_color[2]);
            } else {
                cairo_set_source_rgb(cr, normal_color[0], normal_color[1], normal_color[2]);
            }
            const std::string& word = words[i];

            // 设置字体
            if (is_emoji(word)) {
                pango_layout_set_font_description(layout, emoji_desc);
            } else {
                pango_layout_set_font_description(layout, desc);
            }

            // 计算单词尺寸
            pango_layout_set_text(layout, word.c_str(), -1);
            int word_width, word_height;
            pango_layout_get_pixel_size(layout, &word_width, &word_height);

            // 如果当前行放不下，换行
            if (current_x + word_width > x + width) {
                current_x = x;
                current_y += line_height;
            }

            // 如果超出高度，记录溢出
            if (current_y + word_height > y + height) {
                overflow = true;
                break;
            }

            // 画文本
            cairo_move_to(cr, current_x, current_y);
            pango_cairo_show_layout(cr, layout);

            // 更新 X 坐标
            current_x += word_width + char_spacing;
        }

        if (overflow) {
            high = font_size;  // 过大，减少
        } else {
            low = font_size;  // 过小，增加
        }
    }

    // 释放资源
    pango_font_description_free(desc);
    pango_font_description_free(emoji_desc);
    g_object_unref(layout);
}

// 将 surface 贴到 target_img 的 (x, y) 位置
bool overlay_image(const std::string& target_img, cairo_surface_t* surface, 
                   const std::string& output_img, double x = 0, double y = 0) {
    // 加载目标图片
    cairo_surface_t* target = cairo_image_surface_create_from_png(target_img.c_str());
    if (cairo_surface_status(target) != CAIRO_STATUS_SUCCESS) {
        std::cerr << "Error loading target image: " << target_img << std::endl;
        return false;
    }

    // 获取 target 图片的宽高
    int width = cairo_image_surface_get_width(target);
    int height = cairo_image_surface_get_height(target);

    // 创建 Cairo 绘图环境
    cairo_surface_t* result_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(result_surface);

    // 先绘制 target 作为背景
    cairo_set_source_surface(cr, target, 0, 0);
    cairo_paint(cr);

    // 再绘制 surface 叠加在目标图片上
    cairo_set_source_surface(cr, surface, x, y);
    cairo_paint(cr);

    // 保存最终合成的图片
    cairo_surface_write_to_png(result_surface, output_img.c_str());

    // 释放资源
    cairo_destroy(cr);
    cairo_surface_destroy(result_surface);
    cairo_surface_destroy(target);

    return true;
}

void cover_gen(const std::string& source_img, const std::string& target_img, 
               double x, double y, double width, double height,
               const std::string& text) {
    Timer t("cover_gen");
    HandTimer timer;
    // 通过source_img计算封面尺寸
    int CANVAS_WIDTH = cairo_image_surface_get_width(cairo_image_surface_create_from_png(source_img.c_str()));
    int CANVAS_HEIGHT = cairo_image_surface_get_height(cairo_image_surface_create_from_png(source_img.c_str()));
    // 创建画布
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, CANVAS_WIDTH, CANVAS_HEIGHT);
    cairo_t* cr = cairo_create(surface);
    // 分割文本并提取关键词位置
    std::vector<std::string> words;
    timer.start("segmentTextAndExtractTopKeyword");
    int keyword_index = segmentTextAndExtractTopKeyword(text, words);
    timer.stop("segmentTextAndExtractTopKeyword");
    timer.start("draw_text");
    // 绘制文本
    draw_text(cr, words, keyword_index, x, y, width, height);
    timer.stop("draw_text");
    // 保存输出
    overlay_image(source_img, surface, target_img);
    // 释放资源
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    timer.report();
    std::cout << "纯文本封面生成成功." << std::endl;
}

void cover_gen(int cover_width, int cover_height, const std::array<double, 3>& cover_color,
               const std::string& target_img, 
               double x, double y, double width, double height,
               const std::string& text) {
    
    // 创建画布，根据颜色创建纯色背景
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, cover_width, cover_height);
    cairo_t* cr = cairo_create(surface);
    // 设置背景颜色
    cairo_set_source_rgb(cr, cover_color[0], cover_color[1], cover_color[2]);
    cairo_paint(cr);
    // 在纯色背景上绘制文本
    cairo_surface_t* text_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, cover_width, cover_height);
    cairo_t* text_cr = cairo_create(text_surface);
    
    // 分割文本并提取关键词位置
    std::vector<std::string> words;
    int keyword_index = segmentTextAndExtractTopKeyword(text, words);
    // 绘制文本
    draw_text(text_cr, words, keyword_index, x, y, width, height);
    // 将文本绘制到背景上
    cairo_set_source_surface(cr, text_surface, 0, 0);
    cairo_paint(cr);
    // 保存结果
    cairo_surface_write_to_png(surface, target_img.c_str());
    
    // 释放资源
    cairo_destroy(text_cr);
    cairo_surface_destroy(text_surface);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    std::cout << "纯文本封面生成成功." << std::endl;
}

void draw_tongrenwen_text(cairo_t* cr,
               const std::string& text, 
               double x, double y, double width, double height,
               const char* font_path = "../ttf/PingFang HK Regular.ttf", 
               double min_font_size = 10,
               double line_spacing = 1.1,
               double word_spacing = 0.1,
               const std::array<double, 3>& normal_color = {1.0, 1.0, 1.0}) {

    // 创建 Pango 文字布局
    PangoLayout* layout = pango_cairo_create_layout(cr);
    PangoFontDescription* desc = load_ttf_font(font_path);

    // 启用自动换行
    pango_layout_set_width(layout, width * PANGO_SCALE);
    pango_layout_set_wrap(layout, PANGO_WRAP_WORD);

    double low = min_font_size, high = std::min(width, height), font_size = high;
    
    while (high - low > 1) {
        font_size = (low + high) / 2;
        pango_font_description_set_size(desc, font_size * PANGO_SCALE);
        pango_layout_set_font_description(layout, desc);
        pango_layout_set_text(layout, text.c_str(), -1);
        
        int text_width, text_height;
        pango_layout_get_pixel_size(layout, &text_width, &text_height);
        
        if (text_height > height)
            high = font_size;  // 过大，减少字体
        else
            low = font_size;   // 过小，增加字体
    }

    // 设定最终字体大小
    pango_font_description_set_size(desc, low * PANGO_SCALE);
    pango_layout_set_font_description(layout, desc);

    // 设置文本颜色
    cairo_set_source_rgb(cr, normal_color[0], normal_color[1], normal_color[2]);

    // 进行绘制
    cairo_move_to(cr, x, y);
    pango_cairo_show_layout(cr, layout);
    
    // 释放资源
    pango_font_description_free(desc);
    g_object_unref(layout);
}

void cover_tongrenwen_gen(const std::string& source_img, const std::string& target_img, 
               double title_x, double title_y, double title_width, double title_height,
               const std::string& title,
               double x, double y, double width, double height,
               const std::string& content) {
    // 通过source_img计算封面尺寸
    int CANVAS_WIDTH = cairo_image_surface_get_width(cairo_image_surface_create_from_png(source_img.c_str()));
    int CANVAS_HEIGHT = cairo_image_surface_get_height(cairo_image_surface_create_from_png(source_img.c_str()));
    // 创建画布
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, CANVAS_WIDTH, CANVAS_HEIGHT);
    cairo_t* cr = cairo_create(surface);
    // 绘制标题
    draw_tongrenwen_text(cr, title, title_x, title_y, title_width, title_height);
    // 绘制正文
    draw_tongrenwen_text(cr, content, x, y, width, height);
    // 保存输出
    overlay_image(source_img, surface, target_img);
    // 释放资源
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    std::cout << "同人文封面生成成功." << std::endl;
}

int main() {
    // 纯文本生成封面图示例
    cover_gen("../纯文本生成背景图.png", "../纯文本生成封面图.png", 100, 150, 350, 400, "🎯每次快门都是大片感🎯");
    // 纯色背景生成封面示例
    // cover_gen(600, 800, {0.0, 1.0, 0.0}, "../纯色背景生成封面图.png", 100, 150, 350, 400, "🎯每次快门都是大片感🎯");
    // // 同人文生成封面图示例
    // cover_tongrenwen_gen("../同人文生成背景图.png", "../同人文生成封面图.png",
    //                      50, 100, 425, 150, "测试标题测试标题测试标题测试标题",
    //                      50, 300, 425, 300, "正文内容正文内容正文内容正文内容正文内容正文内容正文内容正文内容正文内容正文内容");
    return 0;
}