cmake_minimum_required(VERSION 3.19)

set(projectName pu_test)

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
        ${PU_ROOT}/src
        )

target_link_libraries(${projectName} PRIVATE
        pu_model
        )