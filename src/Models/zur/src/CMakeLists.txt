cmake_minimum_required(VERSION 3.19)

set(projectName zur_model)

project(${projectName})

set(HEADERS
        zur.h
	)

set(SOURCES
        zur.cpp
	)

add_library(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

target_include_directories(${projectName} INTERFACE
        ${PROJECT_ROOT}/ModelingDispatcher/src
        PUBLIC ${PROJECT_ROOT}/Models/target/src
        )

target_link_libraries(${projectName} INTERFACE
        modeling_dispatcher
        target_model
        )

