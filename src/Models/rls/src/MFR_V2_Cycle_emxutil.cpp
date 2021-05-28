//
// File: MFR_V2_Cycle_emxutil.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//

// Include Files
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>


// Function Definitions

//
// Arguments    : emxArray_boolean_T *emxArray
//                int oldNumel
// Return Type  : void
//
void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int oldNumel)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = calloc(static_cast<unsigned int>(i), sizeof(boolean_T));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(boolean_T) * oldNumel);
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = (boolean_T *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : emxArray_int32_T *emxArray
//                int oldNumel
// Return Type  : void
//
void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = calloc(static_cast<unsigned int>(i), sizeof(int));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(int) * oldNumel);
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = (int *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : emxArray_real_T *emxArray
//                int oldNumel
// Return Type  : void
//
void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i *= 2;
      }
    }

    newData = calloc(static_cast<unsigned int>(i), sizeof(double));
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, sizeof(double) * oldNumel);
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = (double *)newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : struct0_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct0_T(struct0_T *pStruct)
{
  emxFree_real_T(&pStruct->ID);
  emxFree_real_T(&pStruct->R0);
  emxFree_real_T(&pStruct->V);
  emxFree_real_T(&pStruct->RCS);
}

//
// Arguments    : struct1_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct1_T(struct1_T *pStruct)
{
  emxFree_real_T(&pStruct->elev);
  emxFree_real_T(&pStruct->asim);
  emxFree_real_T(&pStruct->ed);
  emxFree_real_T(&pStruct->ee);
  emxFree_real_T(&pStruct->ea);
  emxFree_real_T(&pStruct->tgID);
  emxFree_real_T(&pStruct->tgIDprev);
}

//
// Arguments    : struct2_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct2_T(struct2_T *pStruct)
{
  emxFree_real_T(&pStruct->IDLost);
  emxFree_real_T(&pStruct->IDNew);
  emxFree_real_T(&pStruct->IDTracked);
  emxFree_real_T(&pStruct->RTrackedX);
  emxFree_real_T(&pStruct->RTrackedY);
  emxFree_real_T(&pStruct->RTrackedZ);
  emxFree_real_T(&pStruct->VTrackedX);
  emxFree_real_T(&pStruct->VTrackedY);
  emxFree_real_T(&pStruct->VTrackedZ);
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
// Return Type  : void
//
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_boolean_T *)NULL) {
    if (((*pEmxArray)->data != (boolean_T *)NULL) && (*pEmxArray)->canFreeData)
    {
      free((*pEmxArray)->data);
    }

    free((*pEmxArray)->size);
    free(*pEmxArray);
    *pEmxArray = (emxArray_boolean_T *)NULL;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
// Return Type  : void
//
void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int *)NULL) && (*pEmxArray)->canFreeData) {
      free((*pEmxArray)->data);
    }

    free((*pEmxArray)->size);
    free(*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
// Return Type  : void
//
void emxFree_real_T(emxArray_real_T** pEmxArray)
{
    if (*pEmxArray != (emxArray_real_T*)NULL) {
        if (((*pEmxArray)->data != (double*)NULL) && (*pEmxArray)->canFreeData) {
            std::free((*pEmxArray)->data);
        }

        std::free((*pEmxArray)->size);
        std::free(*pEmxArray);
        *pEmxArray = (emxArray_real_T*)NULL;
    }
}

//
// Arguments    : struct0_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct0_T(struct0_T *pStruct)
{
  emxInit_real_T(&pStruct->ID, 1);
  emxInit_real_T(&pStruct->R0, 2);
  emxInit_real_T(&pStruct->V, 2);
  emxInit_real_T(&pStruct->RCS, 1);
}

//
// Arguments    : struct1_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct1_T(struct1_T *pStruct)
{
  emxInit_real_T(&pStruct->elev, 2);
  emxInit_real_T(&pStruct->asim, 2);
  emxInit_real_T(&pStruct->ed, 2);
  emxInit_real_T(&pStruct->ee, 2);
  emxInit_real_T(&pStruct->ea, 2);
  emxInit_real_T(&pStruct->tgID, 2);
  emxInit_real_T(&pStruct->tgIDprev, 2);
}

//
// Arguments    : struct2_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct2_T(struct2_T *pStruct)
{
  emxInit_real_T(&pStruct->IDLost, 1);
  emxInit_real_T(&pStruct->IDNew, 1);
  emxInit_real_T(&pStruct->IDTracked, 1);
  emxInit_real_T(&pStruct->RTrackedX, 1);
  emxInit_real_T(&pStruct->RTrackedY, 1);
  emxInit_real_T(&pStruct->RTrackedZ, 1);
  emxInit_real_T(&pStruct->VTrackedX, 1);
  emxInit_real_T(&pStruct->VTrackedY, 1);
  emxInit_real_T(&pStruct->VTrackedZ, 1);
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions)
{
  emxArray_boolean_T *emxArray;
  int i;
  *pEmxArray = (emxArray_boolean_T *)malloc(sizeof(emxArray_boolean_T));
  emxArray = *pEmxArray;
  emxArray->data = (boolean_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc(sizeof(int) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// File trailer for MFR_V2_Cycle_emxutil.cpp
//
// [EOF]
//
