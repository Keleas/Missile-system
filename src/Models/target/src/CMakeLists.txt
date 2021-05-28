cmake_minimum_required(VERSION 3.19)

set(projectName target_model)

project(${projectName})

set(HEADERS
        airtarget.h
        Coordinates.h
        TrajData.h
        Vector3D.h
        zur.h
        )

set(SOURCES
        airtarget.cpp
        zur.cpp
        )

add_library(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

target_link_libraries(${projectName} INTERFACE
        modeling_dispatcher
        )
