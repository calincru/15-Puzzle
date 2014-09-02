# Used by add_test macro to generate the executable
set( TESTS_BASE_CLASS Test.cc )

add_definitions( -Wall -Wextra -Werror -std=c++0x )
include_directories(
    ../include
    ../src
)

install( DIRECTORY testfiles
         DESTINATION ${CMAKE_BINARY_DIR}/tests )

set( BoardTest_DEPENDS ../src/Board.cc )
add_test( BoardTest ${BoardTest_DEPENDS} )
