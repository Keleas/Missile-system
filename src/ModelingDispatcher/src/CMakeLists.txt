cmake_minimum_required(VERSION 3.19)

set(projectName modeling_dispatcher)

project(${projectName})

set(HEADERS
        abstractmodel.h
        ModelingDispatcher.h
        modelfactory.h
        )

set(SOURCES
        ModelingDispatcher.cpp
        )

add_library(${projectName} STATIC
        ${HEADERS}
        ${SOURCES}
        )

target_include_directories(${projectName} PUBLIC
        ${PROJECT_ROOT}/MessageManager/src
        )
target_link_libraries(${projectName} PUBLIC
        message_dispatcher
        )