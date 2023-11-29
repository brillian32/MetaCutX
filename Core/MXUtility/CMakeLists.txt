cmake_minimum_required(VERSION 3.21)
project(MXUtility)
message(------MXUtility------)

find_package(spdlog CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED include/MXSpdLog.h
        src/MXSpdLog.cpp include/GlobalDef.h
        include/Singleton.h)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)

target_link_libraries(${PROJECT_NAME} PUBLIC
        spdlog::spdlog
        )
target_compile_definitions(
        ${PROJECT_NAME} PRIVATE
        EXPORT_DLL
        )
# 设置编译选项，指定编译器为MSVC时，使用utf-8编码
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-finput-charset=UTF-8>
        )
