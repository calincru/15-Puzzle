# Used by add_test macro to generate the executable
set( TESTS_BASE_CLASS Test.cc )

add_definitions( -Wall -Wextra -Werror -std=c++0x )
include_directories(
    ../include
    ../src
)

add_test( BoardTest )
