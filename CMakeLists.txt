cmake_minimum_required( VERSION 2.8 )
project( puzzle-15 )

set( CMAKE_COLOR_MAKEFILE ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH}
)

add_subdirectory(src)
add_subdirectory(include)


if( BUILD_TESTS )
    include( add_test )
    add_subdirectory(tests)
endif( BUILD_TESTS )
