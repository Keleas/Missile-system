//
// File: MFR_V2_GenerateTrajectoryType.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//

// Include Files
#include "MFR_V2_GenerateTrajectoryType.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_data.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_Cycle_initialize.h"
#include "MFR_V2_GenerateMFRType.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Targets
// Arguments    : const emxArray_real_T *TG_ID
//                const emxArray_real_T *TG_R0X
//                const emxArray_real_T *TG_R0Y
//                const emxArray_real_T *TG_R0Z
//                const emxArray_real_T *TG_VX
//                const emxArray_real_T *TG_VY
//                const emxArray_real_T *TG_VZ
//                const emxArray_real_T *TG_RCS
//                struct1_T *TG
// Return Type  : void
//
void MFR_V2_GenerateTrajectoryType(const emxArray_real_T *TG_ID, const
  emxArray_real_T *TG_R0X, const emxArray_real_T *TG_R0Y, const emxArray_real_T *
  TG_R0Z, const emxArray_real_T *TG_VX, const emxArray_real_T *TG_VY, const
  emxArray_real_T *TG_VZ, const emxArray_real_T *TG_RCS, struct1_T *TG)
{
  int i;
  int loop_ub;
  if (isInitialized_MFR_V2_Cycle == false) {
    MFR_V2_Cycle_initialize();
  }

  i = TG->ID->size[0];
  TG->ID->size[0] = TG_ID->size[0];
  emxEnsureCapacity_real_T(TG->ID, i);
  loop_ub = TG_ID->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->ID->data[i] = TG_ID->data[i];
  }

  i = TG->R0->size[0] * TG->R0->size[1];
  TG->R0->size[0] = TG_R0X->size[0];
  TG->R0->size[1] = 3;
  emxEnsureCapacity_real_T(TG->R0, i);
  loop_ub = TG_R0X->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->R0->data[i] = TG_R0X->data[i];
  }

  loop_ub = TG_R0Y->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->R0->data[i + TG->R0->size[0]] = TG_R0Y->data[i];
  }

  loop_ub = TG_R0Z->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->R0->data[i + TG->R0->size[0] * 2] = TG_R0Z->data[i];
  }

  i = TG->V->size[0] * TG->V->size[1];
  TG->V->size[0] = TG_VX->size[0];
  TG->V->size[1] = 3;
  emxEnsureCapacity_real_T(TG->V, i);
  loop_ub = TG_VX->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->V->data[i] = TG_VX->data[i];
  }

  loop_ub = TG_VY->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->V->data[i + TG->V->size[0]] = TG_VY->data[i];
  }

  loop_ub = TG_VZ->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->V->data[i + TG->V->size[0] * 2] = TG_VZ->data[i];
  }

  i = TG->RCS->size[0];
  TG->RCS->size[0] = TG_RCS->size[0];
  emxEnsureCapacity_real_T(TG->RCS, i);
  loop_ub = TG_RCS->size[0];
  for (i = 0; i < loop_ub; i++) {
    TG->RCS->data[i] = TG_RCS->data[i];
  }

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
