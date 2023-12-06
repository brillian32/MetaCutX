cmake_minimum_required(VERSION 3.21)
project(MetaCutX)

if (MSVC)
    # 对于 Visual Studio 编译器 执行源文件编译，和执行时为utf-8
    #/utf-8 选项 等价于 /source-charset:utf-8 + execution-charset:utf-8。
    message("Using MSVC compiler")
    add_compile_options(/utf-8)
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Core/MXRender)
add_subdirectory(Core/MXUtility)

add_subdirectory(Core/UnitTest)
add_subdirectory(App/MXTimeline)
add_subdirectory(App/MXPlayer)

include_directories(Core/MXRender)


