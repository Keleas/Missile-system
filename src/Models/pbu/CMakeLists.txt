cmake_minimum_required(VERSION 3.19)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
