//
// File: MFR_V2_GenerateTrajectoryType.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//
#ifndef MFR_V2_GENERATETRAJECTORYTYPE_H
#define MFR_V2_GENERATETRAJECTORYTYPE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "MFR_V2_Cycle_types.h"

// Function Declarations
extern void MFR_V2_GenerateTrajectoryType(const emxArray_real_T *TG_ID, const
  emxArray_real_T *TG_R0X, const emxArray_real_T *TG_R0Y, const emxArray_real_T *
  TG_R0Z, const emxArray_real_T *TG_VX, const emxArray_real_T *TG_VY, const
  emxArray_real_T *TG_VZ, const emxArray_real_T *TG_RCS, struct1_T *TG);

#endif

//
// File trailer for MFR_V2_GenerateTrajectoryType.h
//
// [EOF]
//
