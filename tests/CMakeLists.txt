if (BUILD_TESTS)
    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    add_executable(utest EXCLUDE_FROM_ALL
        commonTest.cc
	intersectionTest.cc
	utest.cpp
        )
    target_link_libraries(utest
        maxwell
	tinyxml
	SDL
        )
    enable_testing()
    add_test(utest utest)
    add_custom_target(check COMMAND ${RUN_TEST_COMMAND}
        DEPENDS utest)
endif ()
