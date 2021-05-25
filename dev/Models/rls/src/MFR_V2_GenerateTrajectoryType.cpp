//
// File: MFR_V2_GenerateTrajectoryType.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//

// Include Files
#include "MFR_V2_GenerateTrajectoryType.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_data.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_Cycle_initialize.h"
#include "MFR_V2_GenerateMFRType.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions

//
// Targets
// air-fighter        0
// frontline bomber   1
// heavy bomber       2
// Arguments    : const emxArray_real_T *TG_ID
//                const emxArray_real_T *TG_R0X
//                const emxArray_real_T *TG_R0Y
//                const emxArray_real_T *TG_R0Z
//                const emxArray_real_T *TG_VX
//                const emxArray_real_T *TG_VY
//                const emxArray_real_T *TG_VZ
//                const emxArray_real_T *TG_Type
//                struct0_T *TG
// Return Type  : void
//
void MFR_V2_GenerateTrajectoryType(const emxArray_real_T *TG_ID, const
  emxArray_real_T *TG_R0X, const emxArray_real_T *TG_R0Y, const emxArray_real_T *
  TG_R0Z, const emxArray_real_T *TG_VX, const emxArray_real_T *TG_VY, const
  emxArray_real_T *TG_VZ, const emxArray_real_T *TG_Type, struct0_T *TG)
{
  emxArray_real_T *r;
  int nx;
  int k;
  double b_r;
  static const signed char RCS[4] = { 5, 9, 17, 50 };

  if (isInitialized_MFR_V2_Cycle == false) {
    MFR_V2_Cycle_initialize();
  }

  emxInit_real_T(&r, 1);

  // transport aircraft 3
  nx = r->size[0];
  r->size[0] = TG_Type->size[0];
  emxEnsureCapacity_real_T(r, nx);
  nx = TG_Type->size[0];
  for (k = 0; k < nx; k++) {
    if (rtIsNaN(TG_Type->data[k]) || rtIsInf(TG_Type->data[k])) {
      b_r = rtNaN;
    } else if (TG_Type->data[k] == 0.0) {
      b_r = 0.0;
    } else {
      b_r = fmod(TG_Type->data[k], 4.0);
      if (b_r == 0.0) {
        b_r = 0.0;
      } else {
        if (TG_Type->data[k] < 0.0) {
          b_r += 4.0;
        }
      }
    }

    r->data[k] = b_r;
  }

  nx = TG->ID->size[0];
  TG->ID->size[0] = TG_ID->size[0];
  emxEnsureCapacity_real_T(TG->ID, nx);
  k = TG_ID->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->ID->data[nx] = TG_ID->data[nx];
  }

  nx = TG->R0->size[0] * TG->R0->size[1];
  TG->R0->size[0] = TG_R0X->size[0];
  TG->R0->size[1] = 3;
  emxEnsureCapacity_real_T(TG->R0, nx);
  k = TG_R0X->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->R0->data[nx] = TG_R0X->data[nx];
  }

  k = TG_R0Y->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->R0->data[nx + TG->R0->size[0]] = TG_R0Y->data[nx];
  }

  k = TG_R0Z->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->R0->data[nx + TG->R0->size[0] * 2] = TG_R0Z->data[nx];
  }

  nx = TG->V->size[0] * TG->V->size[1];
  TG->V->size[0] = TG_VX->size[0];
  TG->V->size[1] = 3;
  emxEnsureCapacity_real_T(TG->V, nx);
  k = TG_VX->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->V->data[nx] = TG_VX->data[nx];
  }

  k = TG_VY->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->V->data[nx + TG->V->size[0]] = TG_VY->data[nx];
  }

  k = TG_VZ->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->V->data[nx + TG->V->size[0] * 2] = TG_VZ->data[nx];
  }

  nx = TG->RCS->size[0];
  TG->RCS->size[0] = r->size[0];
  emxEnsureCapacity_real_T(TG->RCS, nx);
  k = r->size[0];
  for (nx = 0; nx < k; nx++) {
    TG->RCS->data[nx] = RCS[static_cast<int>((r->data[nx] + 1.0)) - 1];
  }

  emxFree_real_T(&r);

  //      coder.varsize('TG.ID');
  //      coder.varsize('TG.R0');
  //      coder.varsize('TG.V');
  //      coder.varsize('TG.RCS');
}

//
// File trailer for MFR_V2_GenerateTrajectoryType.cpp
//
// [EOF]
//
