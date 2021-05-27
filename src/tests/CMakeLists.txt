cmake_minimum_required(VERSION 3.19)

set(projectName project)

project(${projectName})

set(HEADERS
        )

set(SOURCES
        main.cpp
        )

add_executable(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

target_include_directories(${projectName} PRIVATE
        ${PROJECT_ROOT}/Models/target/src
        ${PROJECT_ROOT}/Models/rls/src
        ${PROJECT_ROOT}/Models/pbu/src
        ${PROJECT_ROOT}/Models/pu/src
        )

target_link_libraries(${projectName} PRIVATE
        target_model
        rls_model
        pbu_model
	    pu_model
    )