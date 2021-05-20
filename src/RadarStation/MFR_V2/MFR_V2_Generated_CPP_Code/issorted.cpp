//
// File: issorted.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//

// Include Files
#include "issorted.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
// Return Type  : boolean_T
//
boolean_T issorted(const emxArray_real_T *x)
{
  boolean_T y;
  int dim;
  int n;
  int k;
  boolean_T exitg1;
  int b_n;
  boolean_T exitg2;
  int subs[2];
  double d;
  y = true;
  dim = 2;
  if (x->size[0] != 1) {
    dim = 1;
  }

  if (x->size[0] != 0) {
    if (dim <= 1) {
      n = x->size[0];
    } else {
      n = 1;
    }

    if (n != 1) {
      if (dim == 2) {
        n = -1;
      } else {
        n = 0;
      }

      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k <= n)) {
        if (dim == 1) {
          b_n = x->size[0] - 1;
        } else {
          b_n = x->size[0];
        }

        k = 0;
        exitg2 = false;
        while ((!exitg2) && (k <= b_n - 1)) {
          subs[0] = k + 1;
          subs[1] = 1;
          subs[dim - 1]++;
          d = x->data[subs[0] - 1];
          if ((!(x->data[k] <= d)) && (!rtIsNaN(d))) {
            y = false;
          }

          if (!y) {
            exitg2 = true;
          } else {
            k++;
          }
        }

        if (!y) {
          exitg1 = true;
        } else {
          k = 1;
        }
      }
    }
  }

  return y;
}

//
// File trailer for issorted.cpp
//
// [EOF]
//
