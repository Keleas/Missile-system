cmake_minimum_required(VERSION 3.19)

set(projectName pbu_model)

project(${projectName})

set(HEADERS
        PBU.h
        )

set(SOURCES
        PBU.cpp
        )

add_library(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

target_link_libraries(${projectName} INTERFACE
        modeling_dispatcher
        )
