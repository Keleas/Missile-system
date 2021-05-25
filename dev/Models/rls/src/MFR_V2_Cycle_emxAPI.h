//
// File: MFR_V2_Cycle_emxAPI.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//
#ifndef MFR_V2_CYCLE_EMXAPI_H
#define MFR_V2_CYCLE_EMXAPI_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "MFR_V2_Cycle_types.h"

// Function Declarations
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, const int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxDestroy_struct0_T(struct0_T emxArray);
extern void emxDestroy_struct1_T(struct1_T emxArray);
extern void emxDestroy_struct2_T(struct2_T emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_struct0_T(struct0_T *pStruct);
extern void emxInit_struct1_T(struct1_T *pStruct);
extern void emxInit_struct2_T(struct2_T *pStruct);

#endif

//
// File trailer for MFR_V2_Cycle_emxAPI.h
//
// [EOF]
//
