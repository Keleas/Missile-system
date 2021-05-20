//
// File: MFR_V2_Cycle_terminate.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//

// Include Files
#include "MFR_V2_Cycle_terminate.h"
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
void MFR_V2_Cycle_terminate()
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
  isInitialized_MFR_V2_Cycle = false;
}

//
// File trailer for MFR_V2_Cycle_terminate.cpp
//
// [EOF]
//
