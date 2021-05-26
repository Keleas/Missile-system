cmake_minimum_required(VERSION 3.19)

set(PU_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/src)

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
