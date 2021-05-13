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

#target_include_directories(${projectName} INTERFACE
#        ${PROJECT_ROOT}/ModelingDispatcher/src
#        ${PROJECT_ROOT}/MessageManager/src
#        )

target_link_libraries(${projectName} INTERFACE
        modeling_dispatcher
        )
