cmake_minimum_required(VERSION 3.21)
project(MetaCutX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Core/MXRender)
add_subdirectory(Core/MXUtility)

add_subdirectory(Core/UnitTest)
add_subdirectory(App/MXTimeline)
add_subdirectory(App/MXPlayer)

include_directories(Core/MXRender)


