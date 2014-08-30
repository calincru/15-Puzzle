set( puzzle-8_TEST_FILES BoardTest.cpp )

add_definitions( -Wall -Wextra -Werror )
include_directories(
    ../includes
    ../src
)

add_test( BoardTest )
