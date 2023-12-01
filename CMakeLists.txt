cmake_minimum_required(VERSION 3.26)
project(MetaCutX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Core/MXRender)
add_subdirectory(Core/MXUtility)
add_subdirectory(App/MXTimeline)
add_subdirectory(App/MXResource)

include_directories(Core/MXRender)
add_executable(MetaCutX main.cpp
        Core/MXUtility/MXSpdLog.cpp)

target_link_libraries(MetaCutX MXRender)
