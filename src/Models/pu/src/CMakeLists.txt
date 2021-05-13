cmake_minimum_required(VERSION 3.19)

set(projectName target_model)

project(${projectName})

set(HEADERS
        airtarget.h
        Coordinates.h
        TrajData.h
        Vector3D.h
        )

set(SOURCES
        airtarget.cpp
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
