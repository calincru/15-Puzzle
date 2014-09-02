macro( add_test TEST_NAME )
    if( BUILD_TESTS )
        if( NOT TESTS_BASE_CLASS )
            message( FATAL_ERROR "TESTS_BASE_CLASS is not set." )
        else( NOT TESTS_BASE_CLASS )
            set( ${TEST_NAME}_SRCS
                ${TEST_NAME}.cc
                ${TESTS_BASE_CLASS}
                ${ARGN}
            )
            include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
            add_executable( ${TEST_NAME} ${${TEST_NAME}_SRCS} )
        endif( NOT TESTS_BASE_CLASS )
    endif( BUILD_TESTS )
endmacro( add_test TEST_NAME )
