cmake_minimum_required(VERSION 3.19)

include_directories(${PROJECT_ROOT}/MessageManager/src)
include_directories(${PROJECT_ROOT}/ModelingDispatcher/src)

add_subdirectory(pbu)
add_subdirectory(target)