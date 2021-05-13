cmake_minimum_required(VERSION 3.19)

set(projectName disp_test)

project(${projectName})

set(MSG_SOURCES
        testmodel.cpp
        main.cpp
        )

set(MSG_HEADERS
        testmodel.h
        )

add_executable(${projectName}
        ${MSG_HEADERS}
        ${MSG_SOURCES}
        )

target_include_directories(${projectName} PRIVATE
        ${MODELING_DISPATCHER_ROOT}/src
        )

target_link_libraries(${projectName} PRIVATE
        modeling_dispatcher
        )