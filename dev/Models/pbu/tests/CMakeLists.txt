cmake_minimum_required(VERSION 3.19)

set(projectName pbu_test)

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

target_include_directories(${projectName} PRIVATE
        ${PBU_ROOT}/src
        )

target_link_libraries(${projectName} PRIVATE
        pbu_model
        )