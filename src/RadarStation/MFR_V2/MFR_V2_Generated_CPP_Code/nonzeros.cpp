//
// File: nonzeros.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//

// Include Files
#include "nonzeros.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *s
//                emxArray_real_T *v
// Return Type  : void
//
void nonzeros(const emxArray_real_T *s, emxArray_real_T *v)
{
  int n;
  int i;
  int b_i;
  int k;
  n = s->size[0];
  i = 0;
  b_i = s->size[0];
  for (k = 0; k < b_i; k++) {
    if (s->data[k] != 0.0) {
      i++;
    }
  }

  b_i = v->size[0];
  v->size[0] = i;
  emxEnsureCapacity_real_T(v, b_i);
  i = -1;
  for (k = 0; k < n; k++) {
    if (s->data[k] != 0.0) {
      i++;
      v->data[i] = s->data[k];
    }
  }
}

//
// File trailer for nonzeros.cpp
//
// [EOF]
//
