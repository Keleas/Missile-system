//
// File: find.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//

// Include Files
#include "find.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const emxArray_boolean_T *x
//                emxArray_int32_T *i
// Return Type  : void
//
void eml_find(const emxArray_boolean_T *x, emxArray_int32_T *i)
{
  int nx;
  int idx;
  int ii;
  boolean_T exitg1;
  nx = x->size[0];
  idx = 0;
  ii = i->size[0];
  i->size[0] = x->size[0];
  emxEnsureCapacity_int32_T(i, ii);
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x->data[ii]) {
      idx++;
      i->data[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (x->size[0] == 1) {
    if (idx == 0) {
      i->size[0] = 0;
    }
  } else {
    ii = i->size[0];
    if (1 > idx) {
      i->size[0] = 0;
    } else {
      i->size[0] = idx;
    }

    emxEnsureCapacity_int32_T(i, ii);
  }
}

//
// File trailer for find.cpp
//
// [EOF]
//
