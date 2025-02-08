cmake_minimum_required(VERSION 3.20)

project(Vector)

set(CMAKE_CXX_STANDARD 20)

set (SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector.cpp
)

set (HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector.hpp
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(VectorTest ${SOURCES} ${HEADERS})

target_link_libraries(VectorTest ${GTEST_LIBRARIES} pthread)


enable_testing()
add_test(NAME VectorTest COMMAND VectorTest)
