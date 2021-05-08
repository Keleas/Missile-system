cmake_minimum_required(VERSION 3.19)

set(projectName target_test)

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
        ${TARGET_ROOT}/src
        )

target_link_libraries(${projectName} PRIVATE
        target_model
        )