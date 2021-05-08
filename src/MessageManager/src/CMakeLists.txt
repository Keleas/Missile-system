cmake_minimum_required(VERSION 3.19)

set(projectName message_dispatcher)

project(${projectName})

set(SOURCES
        )

set(HEADERS
        msg_channel.h
        any_channel.h
        channel_carrier.h
        )

add_library(${projectName} INTERFACE
        ${SOURCES}
        ${HEADERS}
        )