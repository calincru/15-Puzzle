set( puzzle-15_SRCS Board.cc Solver.cc TestClient.cc )
include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

add_definitions( -I. -Wall -Wextra -Werror -std=c++11 )
add_executable( puzzle-15 ${puzzle-15_SRCS} )
set_target_properties( puzzle-15
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
