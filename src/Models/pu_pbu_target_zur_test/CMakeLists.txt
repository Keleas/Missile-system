cmake_minimum_required(VERSION 3.19)

set(projectName pu_pbu_target_zur_test)

project(${projectName})

set(HEADERS
        rlc_stub.h
        )

set(SOURCES
        rlc_stub.cpp
        main.cpp
        )

message(NOTICE "-----------------------------------------${TARGET_ROOT}")

add_executable(${projectName}
        ${HEADERS}
        ${SOURCES}
        )


target_include_directories(${projectName} PUBLIC
        ${PU_ROOT}/src
        ${TARGET_ROOT}/src
        ${PBU_ROOT}/src
        )

target_link_libraries(${projectName} PUBLIC
        target_model
        pu_model
        pbu_model
        )
