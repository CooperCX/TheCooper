cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(TongrenwenCoverGenerator)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 手动指定头文件和库路径
set(PANGO_INCLUDE_DIR "/opt/homebrew/Cellar/pango/1.56.1/include/pango-1.0")
set(PANGO_LIBRARY "/opt/homebrew/lib/libpango-1.0.dylib")

set(PANGOCAIRO_INCLUDE_DIR "/opt/homebrew/Cellar/pango/1.56.1/include/pango-1.0")
set(PANGOCAIRO_LIBRARY "/opt/homebrew/lib/libpangocairo-1.0.dylib")

set(GLIB_INCLUDE_DIR "/opt/homebrew/Cellar/glib/2.82.4/include/glib-2.0" "/opt/homebrew/Cellar/glib/2.82.4/lib/glib-2.0/include")
set(GLIB_LIBRARY "/opt/homebrew/lib/libglib-2.0.dylib")
set(GOBJECT_LIBRARY "/opt/homebrew/lib/libgobject-2.0.dylib")

set(HARFBUZZ_INCLUDE_DIR "/opt/homebrew/Cellar/harfbuzz/10.2.0/include/harfbuzz")
set(HARFBUZZ_LIBRARY "/opt/homebrew/lib/libharfbuzz.dylib")

set(CAIRO_INCLUDE_DIR "/opt/homebrew/Cellar/cairo/1.18.2/include/cairo")
set(CAIRO_LIBRARY "/opt/homebrew/lib/libcairo.dylib")

set(ICU_INCLUDE_DIR "/opt/homebrew/Cellar/icu4c@76/76.1_1/include")
set(ICU_LIBRARY "/opt/homebrew/opt/icu4c@76/lib/libicuuc.76.dylib")

set(FONTCONFIG_INCLUDE_DIR "/opt/homebrew/Cellar/fontconfig/2.16.0/include")
set(FONTCONFIG_LIBRARY "/opt/homebrew/opt/fontconfig/lib/libfontconfig.dylib")

# 添加可执行文件
add_executable(tongrenwen_cover_gen tongrenwen_cover_gen.cpp)


# 设置 include 目录
target_include_directories(tongrenwen_cover_gen PRIVATE 
    ${PANGO_INCLUDE_DIR}
    ${PANGOCAIRO_INCLUDE_DIR}
    ${GLIB_INCLUDE_DIR} 
    ${HARFBUZZ_INCLUDE_DIR} 
    ${CAIRO_INCLUDE_DIR}
    ${CPPJIEBA_INCLUDE_DIR}
    ${ICU_INCLUDE_DIR}
    ${FONTCONFIG_INCLUDE_DIR}
)

# 链接库
target_link_libraries(tongrenwen_cover_gen 
    ${PANGO_LIBRARY}
    ${PANGOCAIRO_LIBRARY}
    ${GLIB_LIBRARY} 
    ${GOBJECT_LIBRARY} 
    ${HARFBUZZ_LIBRARY} 
    ${CAIRO_LIBRARY}
    ${ICU_LIBRARY}
    ${FONTCONFIG_LIBRARY}
)

# 设置 rpath，确保运行时能找到动态库
set_target_properties(tongrenwen_cover_gen PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE
)