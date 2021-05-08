cmake_minimum_required(VERSION 3.19)

set(projectName MissileSystem)

project(${projectName})

include(config.cmake)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(MessageManager)
add_subdirectory(ModelingDispatcher)
add_subdirectory(Models)