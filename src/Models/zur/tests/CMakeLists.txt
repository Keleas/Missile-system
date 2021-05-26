cmake_minimum_required(VERSION 3.19)

set(projectName zur_test)

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
        ${ZUR_ROOT}/src
        )

target_link_libraries(${projectName} PRIVATE
        zur_model
        )