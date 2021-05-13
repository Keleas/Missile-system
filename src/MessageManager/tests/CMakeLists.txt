cmake_minimum_required(VERSION 3.19)

set(projectName msg_test)

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
        ${MSG_DISPATCHER_ROOT}/src
        )

target_link_libraries(${projectName} PRIVATE
        message_dispatcher
        )