include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(maxwell SHARED
    common.cpp
    engine.cpp
    scene.cpp
    screen.cpp
    text_screen.cpp
    primitives/primitive.cpp
    primitives/ball.cpp
    primitives/illuminative.cpp
    primitives/parallelogram.cpp
    primitives/plane.cpp
    )

target_link_libraries(maxwell
    tinyxml
    SDL
    )

add_executable(render main.cpp)
target_link_libraries(render maxwell)

set_target_properties(maxwell PROPERTIES SOVERSION 0 VERSION 0.0)

install(TARGETS maxwell LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS render DESTINATION bin)
