cmake_minimum_required(VERSION 3.10)
project(typical)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(typical INTERFACE)
target_include_directories(typical INTERFACE $<BUILD_INTERFACE:${INCLUDE_DIR}>)
target_include_directories(typical INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

add_executable(tests main.cpp)
target_link_libraries(tests PRIVATE typical)