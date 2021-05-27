cmake_minimum_required(VERSION 3.19)

set(projectName rls_model)

project(${projectName})

set(HEADERS
        rls.h
        issorted.h
        colon.h
        find.h
        inv.h
        ismember.h
        linspace.h
        MFR_V2_Cycle.h
        MFR_V2_Cycle_data.h
        MFR_V2_Cycle_emxAPI.h
        MFR_V2_Cycle_emxutil.h
        MFR_V2_Cycle_initialize.h
        MFR_V2_Cycle_terminate.h
        MFR_V2_GenerateMFRType.h
        MFR_V2_GenerateTrajectoryType.h
        mod.h
        nonzeros.h
        normalize.h
        rt_nonfinite.h
        rtGetInf.h
        rtGetNaN.h
        sort.h
        sortIdx.h
        MFR_V2_Cycle_types.h
        rtwtypes.h
        tmwtypes.h
        )

set(SOURCES
        rls.cpp
        issorted.cpp
        colon.cpp
        find.cpp
        inv.cpp
        ismember.cpp
        linspace.cpp
        MFR_V2_Cycle.cpp
        MFR_V2_Cycle_data.cpp
        MFR_V2_Cycle_emxAPI.cpp
        MFR_V2_Cycle_emxutil.cpp
        MFR_V2_Cycle_initialize.cpp
        MFR_V2_Cycle_terminate.cpp
        MFR_V2_GenerateMFRType.cpp
        MFR_V2_GenerateTrajectoryType.cpp
        mod.cpp
        nonzeros.cpp
        normalize.cpp
        rt_nonfinite.cpp
        rtGetInf.cpp
        rtGetNaN.cpp
        sort.cpp
        sortIdx.cpp
        )

add_library(${projectName}
        ${HEADERS}
        ${SOURCES}
        )

target_include_directories(${projectName} INTERFACE
        ${PROJECT_ROOT}/ModelingDispatcher/src
        )

target_link_libraries(${projectName} INTERFACE
        modeling_dispatcher
        )
