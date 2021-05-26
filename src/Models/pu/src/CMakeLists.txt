cmake_minimum_required(VERSION 3.19)

set(projectName pu_model)

project(${projectName})

set(HEADERS
        pu.h
        )

set(SOURCES
        pu.cpp
        )

add_library(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

target_link_libraries(${projectName} INTERFACE
        modeling_dispatcher
        )
