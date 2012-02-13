include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(cli_render cli_render.cpp)
target_link_libraries(cli_render maxwell)

install(TARGETS cli_render DESTINATION bin)
