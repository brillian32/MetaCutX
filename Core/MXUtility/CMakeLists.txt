cmake_minimum_required(VERSION 3.21)
project(MXUtility)
message(------MXUtility------)

find_package(spdlog CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED include/MXSpdLog.h
        src/MXSpdLog.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_link_libraries(${PROJECT_NAME} PUBLIC
        spdlog::spdlog
        )