include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(tinyxml SHARED
    tinystr.cpp
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp
    )

target_link_libraries(tinyxml
    )

set_target_properties(tinyxml PROPERTIES SOVERSION 0 VERSION 0.0)

install(TARGETS tinyxml LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

