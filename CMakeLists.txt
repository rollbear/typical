cmake_minimum_required(VERSION 3.10)
project(typical)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(typical INTERFACE)
target_include_directories(typical INTERFACE $<BUILD_INTERFACE:${INCLUDE_DIR}>)
target_include_directories(typical INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

add_executable(tests main.cpp include/typical/constant.hpp tests/constant.cpp include/typical/conditional.hpp tests/conditional.cpp include/typical/function_support.hpp tests/function_support.cpp include/typical/compose.hpp tests/compose.cpp include/typical/type_manipulation.hpp tests/type_manipulation.cpp include/typical/application.hpp tests/application.cpp include/typical/type_predicates.hpp tests/type_predicates.cpp include/typical/list_predicates.hpp tests/list_predicates.cpp include/typical/algorithms/transform.hpp tests/transform.cpp include/typical/algorithms/join.hpp include/typical/utilities.hpp tests/join.cpp)
target_link_libraries(tests PRIVATE typical)