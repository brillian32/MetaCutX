cmake_minimum_required(VERSION 3.16)

project(resourceEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 COMPONENTS Quick REQUIRED)
find_package(Qt6 6.4 COMPONENTS Qml REQUIRED)
find_package(Qt6 6.4 COMPONENTS Gui REQUIRED)

qt_add_executable(appresourceEditor
        main.cpp
)

qt_add_qml_module(appresourceEditor
        URI resourceEditor
        VERSION 1.0
        QML_FILES main.qml Libriry.qml Tools.qml SearchLine.qml ShowArea.qml

)
set(viewer_resource_files
        ./Audio.png
        ./Effects.png
        ./Media.png

)

qt_add_resources(appresourceEditor "viewer"
        PREFIX
        "/img"
        FILES
        ${viewer_resource_files}
)

set_target_properties(appresourceEditor PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appresourceEditor
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appresourceEditor
        PRIVATE Qt6::Quick)
target_link_libraries(appresourceEditor
        PRIVATE Qt6::Qml)
target_link_libraries(appresourceEditor
        PRIVATE Qt6::Gui)
