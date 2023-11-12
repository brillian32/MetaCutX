cmake_minimum_required(VERSION 3.26)
project(MXRender)

message(------MXRender------)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(FFMPEG REQUIRED)
find_package(GLEW REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(spdlog CONFIG REQUIRED)

include_directories(Core/MXRender)


set(src ./MXRenderTest.cpp ./MXRenderTest.h DecodeVideo.cpp DecodeVideo.h VideoInfo.cpp VideoInfo.h
        )

add_library(${PROJECT_NAME} ${src})

target_include_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${FFMPEG_LIBRARIES} ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets spdlog::spdlog)


#add_subdirectory(example)
