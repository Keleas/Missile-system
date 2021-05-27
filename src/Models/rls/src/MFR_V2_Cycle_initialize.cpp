//
// File: MFR_V2_Cycle_initialize.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//

// Include Files
#include "MFR_V2_Cycle_initialize.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_data.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void MFR_V2_Cycle_initialize()
{
  rt_InitInfAndNaN();
  omp_init_nest_lock(&emlrtNestLockGlobal);
  isInitialized_MFR_V2_Cycle = true;
}

//
// File trailer for MFR_V2_Cycle_initialize.cpp
//
// [EOF]
//
