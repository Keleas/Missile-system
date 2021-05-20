//
// File: linspace.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//

// Include Files
#include "linspace.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions

//
// Arguments    : double d1
//                double d2
//                double n1
//                emxArray_real_T *y
// Return Type  : void
//
void linspace(double d1, double d2, double n1, emxArray_real_T *y)
{
  int y_tmp;
  int i;
  int k;
  double delta1;
  double delta2;
  if (n1 < 0.0) {
    n1 = 0.0;
  }

  y_tmp = y->size[0] * y->size[1];
  y->size[0] = 1;
  i = static_cast<int>(floor(n1));
  y->size[1] = i;
  emxEnsureCapacity_real_T(y, y_tmp);
  if (i >= 1) {
    y_tmp = i - 1;
    y->data[y_tmp] = d2;
    if (y->size[1] >= 2) {
      y->data[0] = d1;
      if (y->size[1] >= 3) {
        if ((d1 == -d2) && (i > 2)) {
          for (k = 2; k <= y_tmp; k++) {
            y->data[k - 1] = d2 * (static_cast<double>((((k << 1) - i) - 1)) / (
              static_cast<double>(i) - 1.0));
          }

          if ((i & 1) == 1) {
            y->data[i >> 1] = 0.0;
          }
        } else if (((d1 < 0.0) != (d2 < 0.0)) && ((fabs(d1) >
                     8.9884656743115785E+307) || (fabs(d2) >
                     8.9884656743115785E+307))) {
          delta1 = d1 / (static_cast<double>(y->size[1]) - 1.0);
          delta2 = d2 / (static_cast<double>(y->size[1]) - 1.0);
          y_tmp = y->size[1];
          for (k = 0; k <= y_tmp - 3; k++) {
            y->data[k + 1] = (d1 + delta2 * (static_cast<double>(k) + 1.0)) -
              delta1 * (static_cast<double>(k) + 1.0);
          }
        } else {
          delta1 = (d2 - d1) / (static_cast<double>(y->size[1]) - 1.0);
          y_tmp = y->size[1];
          for (k = 0; k <= y_tmp - 3; k++) {
            y->data[k + 1] = d1 + (static_cast<double>(k) + 1.0) * delta1;
          }
        }
      }
    }
  }
}

//
// File trailer for linspace.cpp
//
// [EOF]
//
