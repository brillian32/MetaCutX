cmake_minimum_required(VERSION 3.26)
project(MXUtility)
message(------MXUtility------)

find_package(spdlog CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED include/MXSpdLog.h MXSpdLog.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "info:" ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC
        spdlog::spdlog
        )