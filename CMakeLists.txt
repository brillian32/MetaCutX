cmake_minimum_required(VERSION 3.26)
project(MetaCutX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Core/MXRender)
add_subdirectory(Core/MXUtility)

add_subdirectory(Core/UnitTest)
add_subdirectory(App/MXTimeline)



include_directories(Core/MXRender)
add_executable(MetaCutX main.cpp)

target_link_libraries(MetaCutX MXRender)
