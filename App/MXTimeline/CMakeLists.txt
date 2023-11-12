cmake_minimum_required(VERSION 3.16)

project(timelineEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 COMPONENTS Quick REQUIRED)

qt_add_executable(apptimelineEditor
    main.cpp
)

qt_add_qml_module(apptimelineEditor
    URI timelineEditor
    VERSION 1.0
    QML_FILES main.qml  TimeScale.qml TrackHead.qml
)
set(viewer_resource_files
        ./lockTrack.png
        ./unlockTrack.png
        ./disableMask.png
        ./addTrack.png
)

qt_add_resources(apptimelineEditor "viewer"
        PREFIX
        "/img"
        FILES
        ${viewer_resource_files}
)

set_target_properties(apptimelineEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(apptimelineEditor
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(apptimelineEditor
    PRIVATE Qt6::Quick)
