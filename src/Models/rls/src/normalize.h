//
// File: normalize.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//
#ifndef NORMALIZE_H
#define NORMALIZE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "MFR_V2_Cycle_types.h"

// Function Declarations
extern void b_normalize(const emxArray_real_T *a, emxArray_real_T *n);
extern void normalize(const double a[3], double n[3]);

#endif

//
// File trailer for normalize.h
//
// [EOF]
//
