cmake_minimum_required(VERSION 3.19)

set(projectName modeling_dispatcher)

project(${projectName})

set(HEADERS
        abstractmodel.h
        ModelingDispatcher.h
        )

set(SOURCES
        ModelingDispatcher.cpp
        )

add_library(${projectName} INTERFACE
        ${HEADERS}
        ${SOURCES}
        )

target_include_directories(${projectName} INTERFACE
        ${PROJECT_ROOT}/MessageManager/src
        )
target_link_libraries(${projectName} INTERFACE
        message_dispatcher
        )