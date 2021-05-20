//
// File: ismember.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//
#ifndef ISMEMBER_H
#define ISMEMBER_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "MFR_V2_Cycle_types.h"

// Function Declarations
extern void b_local_ismember(const emxArray_real_T *a, const emxArray_real_T *s,
  emxArray_boolean_T *tf, emxArray_int32_T *loc);
extern void c_local_ismember(const emxArray_real_T *a, const emxArray_real_T *s,
  emxArray_boolean_T *tf);
extern void local_ismember(const emxArray_real_T *a, const emxArray_real_T *s,
  emxArray_boolean_T *tf, emxArray_int32_T *loc);

#endif

//
// File trailer for ismember.h
//
// [EOF]
//
