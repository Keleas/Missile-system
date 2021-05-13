cmake_minimum_required(VERSION 3.19)

set(projectName rls_model)

project(${projectName})

set(HEADERS
        rls.h
        )

set(SOURCES
        rls.cpp
        )

add_library(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

target_include_directories(${projectName} INTERFACE
        ${PROJECT_ROOT}/ModelingDispatcher/src
        )

target_link_libraries(${projectName} INTERFACE
        modeling_dispatcher
        )
