cmake_minimum_required(VERSION 3.16)

project(appPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 COMPONENTS Quick Widgets Multimedia REQUIRED)
#find_package(libyuv REQUIRED)

qt_add_executable(appPlayer
        main.cpp
        FrameProvider.h FrameProvider.cpp
        PlayController.cpp PlayController.h)

qt_add_qml_module(appPlayer
        URI Player
        VERSION 1.0
        QML_FILES main.qml PlayerSlider.qml PlayerToolBox.qml
        )
set(viewer_resource_files
        img/pause.png
        img/play.png
        img/pre.png
        img/next.png
        )

qt_add_resources(appPlayer "viewer"
        PREFIX
        "/"
        FILES
        ${viewer_resource_files}
        )

set_target_properties(appPlayer PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appPlayer
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appPlayer
        PRIVATE
        Qt6::Quick
        Qt6::Widgets
        Qt6::Multimedia
#        yuv
        MXUtility
        MXRender
    )
