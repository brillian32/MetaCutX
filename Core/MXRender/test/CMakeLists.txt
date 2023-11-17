cmake_minimum_required(VERSION 3.26)
project(MXRenderTest)
message(STATUS MXRenderTest)

set(CMAKE_CXX_STANDARD 17)
find_package(doctest CONFIG REQUIRED)

include_directories(../)

add_executable(MXRenderTest MXRenderTest.cpp)

target_link_libraries(MXRenderTest PRIVATE doctest::doctest MXRender)
