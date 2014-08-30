set( puzzle-15_SRCS Board.cc Solver.cc TestClient.cc )
include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/includes
)

add_definitions( -I. -Wall -Wextra -Werror -std=c++0x )
add_executable( puzzle-15 ${puzzle-8_SRCS} )
