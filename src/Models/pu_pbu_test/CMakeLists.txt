cmake_minimum_required(VERSION 3.19)

set(projectName pu_pbu_test)

project(${projectName})

set(HEADERS
        )

set(SOURCES
        main.cpp
        )

add_executable(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

target_include_directories(${projectName} PUBLIC
        ${PU_ROOT}/src
        ${PBU_ROOT}/src
        )

target_link_libraries(${projectName} PUBLIC
        pu_model
        pbu_model
        Qt5::Core
        )
