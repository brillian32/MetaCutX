project(decode_test)
message(------decode_test------)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(FFMPEG REQUIRED)
find_package(GLEW REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(test_src decodeEx.cpp)
add_executable(${PROJECT_NAME} ${test_src})
target_include_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FFMPEG_LIBRARIES})

