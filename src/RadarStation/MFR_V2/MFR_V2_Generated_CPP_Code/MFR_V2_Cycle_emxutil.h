//
// File: MFR_V2_Cycle_emxutil.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//
#ifndef MFR_V2_CYCLE_EMXUTIL_H
#define MFR_V2_CYCLE_EMXUTIL_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "MFR_V2_Cycle_types.h"

// Function Declarations
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFreeStruct_struct0_T(struct0_T *pStruct);
extern void emxFreeStruct_struct1_T(struct1_T *pStruct);
extern void emxFreeStruct_struct2_T(struct2_T *pStruct);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInitStruct_struct0_T(struct0_T *pStruct);
extern void emxInitStruct_struct1_T(struct1_T *pStruct);
extern void emxInitStruct_struct2_T(struct2_T *pStruct);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

//
// File trailer for MFR_V2_Cycle_emxutil.h
//
// [EOF]
//
