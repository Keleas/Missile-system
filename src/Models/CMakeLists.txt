cmake_minimum_required(VERSION 3.19)

include_directories(${PROJECT_ROOT}/MessageManager/src)
include_directories(${PROJECT_ROOT}/ModelingDispatcher/src)

set(PBU_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/pbu)
set(PU_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/pu)
set(TARGET_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/target)

add_subdirectory(pbu)
add_subdirectory(target)
add_subdirectory(pu)
add_subdirectory(rls)

#if(BUILD_TESTS)
    add_subdirectory(pu_pbu_target_zur_test)
#endif()
