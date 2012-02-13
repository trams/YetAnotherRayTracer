cmake_minimum_required(VERSION 2.6)

#find_package(Boost REQUIRED system date_time thread)
#find_package(OpenSSL REQUIRED)

set(CMAKE_CPP_FLAGS_RELEASE  "-DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE  " -g -O2")
set(CMAKE_CXX_FLAGS_DEBUG    " -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -Wall -Wextra -Wconversion -Wcast-qual -fexceptions -pthread -pipe")

# we can't install to /etc with prefix /usr
# without hacks, so we provide CMAKE_INSTALL_SYSCONFDIR
# and use default value as prefix/etc
set(CMAKE_INSTALL_SYSCONFDIR etc CACHE STRING "sysconf directory path")

# providing this for lib/lib64 resolving
set(CMAKE_INSTALL_LIBDIR lib CACHE STRING "library path")

set(RUN_TEST_COMMAND ./utest)

option(BUILD_TESTS "Build Tests" ON)

file(WRITE ${PROJECT_BINARY_DIR}/include/maxwell/config.h "")

add_definitions(
  "-DATTRIBUTE_UNUSED=__attribute__\(\(unused\)\)")

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  ${CMAKE_INSTALL_PREFIX}/include)

add_subdirectory(include)
add_subdirectory(tinyxml)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(bin)

message("
Configuration
-------------
PROJECT_SOURCE_DIR      = ${PROJECT_SOURCE_DIR}
PROJECT_BINARY_DIR      = ${PROJECT_BINARY_DIR}
CMAKE_BUILD_TYPE        = ${CMAKE_BUILD_TYPE}
CXXFLAGS                = $ENV{CXXFLAGS}
CMAKE_CXX_FLAGS         = ${CMAKE_CXX_FLAGS}
CPPFLAGS                = $ENV{CPPFLAGS}
CMAKE_CPP_FLAGS         = ${CMAKE_CPP_FLAGS}
LDFLAGS                 = $ENV{LDFLAGS}
CMAKE_EXE_LINKER_FLAGS  = ${CMAKE_EXE_LINKER_FLAGS}
CMAKE_INSTALL_PREFIX    = ${CMAKE_INSTALL_PREFIX}
CMAKE_INSTALL_LIBDIR    = ${CMAKE_INSTALL_LIBDIR}
CMAKE_INSTALL_SYSCONFDIR= ${CMAKE_INSTALL_SYSCONFDIR}
")
