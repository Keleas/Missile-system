#cmake_minimum_required(VERSION 3.19)

#set(projectName pbu_test)

#project(${projectName})

#set(HEADERS
#        )

#set(SOURCES
#        main.cpp
#        parser.cpp
#        )

#find_package(Qt5 COMPONENTS Core REQUIRED)

#set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
#set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

#add_executable(${projectName}
#        ${HEADERS}
#        ${SOURCES}
#        )

#target_include_directories(${projectName} PRIVATE
#        ${PBU_ROOT}/src
#        )

#target_link_libraries(${projectName}
#        PRIVATE pbu_model
#        PUBLIC Qt5::Core
#        )
