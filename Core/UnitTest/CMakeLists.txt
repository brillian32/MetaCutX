cmake_minimum_required(VERSION 3.21)
project(UnitTest)
message(STATUS UnitTest)

set(CMAKE_CXX_STANDARD 17)
find_package(doctest CONFIG REQUIRED)
add_executable(UnitTest MXRenderTest.cpp)

target_link_libraries(UnitTest PRIVATE doctest::doctest MXRender MXUtility)
#target_compile_options(UnitTest PRIVATE
#        $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>
#        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-finput-charset=UTF-8>
#        )

#if(MSVC)
#        file(GLOB_RECURSE dllFiles ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/*.dll})
#        message(STATUS "will copy Files: " ${dllFiles})
#        add_custom_command(TARGET UnitTest POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                ${dllFiles}
#                ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
#                COMMENT "Copying file after build"
#                )
#endif()