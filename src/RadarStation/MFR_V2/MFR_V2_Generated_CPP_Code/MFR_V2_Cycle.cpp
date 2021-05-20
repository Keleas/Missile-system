//
// File: MFR_V2_Cycle.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//

// Include Files
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_data.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_Cycle_initialize.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "colon.h"
#include "find.h"
#include "ismember.h"
#include "mod.h"
#include "nonzeros.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions

//
// T for output purposes
// OUT=[];
// Arguments    : const struct1_T *TG
//                struct0_T *MFR
//                double dT
//                struct2_T *MSG
// Return Type  : void
//
void MFR_V2_Cycle(const struct1_T *TG, struct0_T *MFR, double dT, struct2_T *MSG)
{
  emxArray_real_T *Rsc;
  int i;
  int ibmat;
  emxArray_real_T *dRsc;
  emxArray_real_T *b;
  int ntilerows;
  int nx;
  int itilerow;
  emxArray_real_T *ts;
  emxArray_real_T *y;
  int i1;
  double DistTarget;
  emxArray_real_T *pos;
  unsigned int sz_idx_0;
  emxArray_real_T *b_MFR;
  int n;
  double scale;
  double absxk;
  double t;
  emxArray_real_T *TrackedID;
  emxArray_real_T *Nrm;
  emxArray_boolean_T *TrackedIDcheck;
  emxArray_int32_T *iloc;
  double a;
  emxArray_real_T *TrackedIDnext;
  boolean_T Lia;
  boolean_T exitg1;
  int exponent;
  emxArray_real_T *TrackedIDlost;
  int b_exponent;
  emxArray_boolean_T *tf;
  emxArray_int32_T *b_iloc;
  emxArray_int32_T *c_iloc;
  if (isInitialized_MFR_V2_Cycle == false) {
    MFR_V2_Cycle_initialize();
  }

  emxInit_real_T(&Rsc, 2);
  i = Rsc->size[0] * Rsc->size[1];
  Rsc->size[0] = TG->R0->size[0];
  Rsc->size[1] = 3;
  emxEnsureCapacity_real_T(Rsc, i);
  ibmat = TG->R0->size[0] * TG->R0->size[1];
  for (i = 0; i < ibmat; i++) {
    Rsc->data[i] = TG->R0->data[i] + TG->V->data[i] * MFR->tsc;
  }

  emxInit_real_T(&dRsc, 2);

  // Target coordinates at scan
  i = dRsc->size[0] * dRsc->size[1];
  dRsc->size[0] = TG->V->size[0];
  dRsc->size[1] = 3;
  emxEnsureCapacity_real_T(dRsc, i);
  ibmat = TG->V->size[0] * TG->V->size[1];
  for (i = 0; i < ibmat; i++) {
    dRsc->data[i] = TG->V->data[i] * MFR->Tscan;
  }

  emxInit_real_T(&b, 2);

  // Target movement during single scan
  // Transition to XYZ coord with MFR at center
  i = b->size[0] * b->size[1];
  b->size[0] = Rsc->size[0];
  b->size[1] = 3;
  emxEnsureCapacity_real_T(b, i);
  ntilerows = Rsc->size[0];
  for (nx = 0; nx < 3; nx++) {
    ibmat = nx * ntilerows;
    for (itilerow = 0; itilerow < ntilerows; itilerow++) {
      b->data[ibmat + itilerow] = MFR->Loc[nx];
    }
  }

  ibmat = Rsc->size[0] * Rsc->size[1];
  i = Rsc->size[0] * Rsc->size[1];
  Rsc->size[1] = 3;
  emxEnsureCapacity_real_T(Rsc, i);
  for (i = 0; i < ibmat; i++) {
    Rsc->data[i] -= b->data[i];
  }

  // Transition to XYZ coord with MFR at center
  emxInit_real_T(&ts, 2);
  if (rtIsNaN(MFR->tsc) || rtIsNaN(MFR->Tscan) || rtIsNaN(dT)) {
    i = ts->size[0] * ts->size[1];
    ts->size[0] = 1;
    ts->size[1] = 1;
    emxEnsureCapacity_real_T(ts, i);
    ts->data[0] = rtNaN;
  } else if ((MFR->Tscan == 0.0) || ((MFR->tsc < dT) && (MFR->Tscan < 0.0)) ||
             ((dT < MFR->tsc) && (MFR->Tscan > 0.0))) {
    ts->size[0] = 1;
    ts->size[1] = 0;
  } else if ((rtIsInf(MFR->tsc) || rtIsInf(dT)) && (rtIsInf(MFR->Tscan) ||
              (MFR->tsc == dT))) {
    i = ts->size[0] * ts->size[1];
    ts->size[0] = 1;
    ts->size[1] = 1;
    emxEnsureCapacity_real_T(ts, i);
    ts->data[0] = rtNaN;
  } else if (rtIsInf(MFR->Tscan)) {
    i = ts->size[0] * ts->size[1];
    ts->size[0] = 1;
    ts->size[1] = 1;
    emxEnsureCapacity_real_T(ts, i);
    ts->data[0] = MFR->tsc;
  } else if ((floor(MFR->tsc) == MFR->tsc) && (floor(MFR->Tscan) == MFR->Tscan))
  {
    i = ts->size[0] * ts->size[1];
    ts->size[0] = 1;
    ibmat = static_cast<int>(floor((dT - MFR->tsc) / MFR->Tscan));
    ts->size[1] = ibmat + 1;
    emxEnsureCapacity_real_T(ts, i);
    for (i = 0; i <= ibmat; i++) {
      ts->data[i] = MFR->tsc + MFR->Tscan * static_cast<double>(i);
    }
  } else {
    eml_float_colon(MFR->tsc, MFR->Tscan, dT, ts);
  }

  // Scanning time vector
  // Number of time steps
  emxInit_real_T(&y, 2);
  if (ts->size[1] - 1 < 0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = static_cast<int>((static_cast<double>(ts->size[1]) - 1.0)) + 1;
    emxEnsureCapacity_real_T(y, i);
    ibmat = static_cast<int>((static_cast<double>(ts->size[1]) - 1.0));
    for (i = 0; i <= ibmat; i++) {
      y->data[i] = i;
    }
  }

  i = y->size[0] * y->size[1];
  i1 = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, i1);
  DistTarget = MFR->pos - 1.0;
  ibmat = i - 1;
  for (i = 0; i <= ibmat; i++) {
    y->data[i] += DistTarget;
  }

  emxInit_real_T(&pos, 2);
  i = pos->size[0] * pos->size[1];
  pos->size[0] = 1;
  pos->size[1] = y->size[1];
  emxEnsureCapacity_real_T(pos, i);
  nx = y->size[1];
  for (ibmat = 0; ibmat < nx; ibmat++) {
    pos->data[ibmat] = b_mod(y->data[ibmat], MFR->posN);
  }

  i = pos->size[0] * pos->size[1];
  i1 = pos->size[0] * pos->size[1];
  pos->size[0] = 1;
  emxEnsureCapacity_real_T(pos, i1);
  ibmat = i - 1;
  for (i = 0; i <= ibmat; i++) {
    pos->data[i]++;
  }

  // Scan positions
  sz_idx_0 = static_cast<unsigned int>(TG->R0->size[0]);
  i = pos->size[1];
  emxInit_real_T(&b_MFR, 1);
  for (itilerow = 0; itilerow < i; itilerow++) {
    i1 = static_cast<int>(sz_idx_0);
    for (n = 0; n < i1; n++) {
      scale = 3.3121686421112381E-170;
      absxk = fabs(Rsc->data[n]);
      if (absxk > 3.3121686421112381E-170) {
        DistTarget = 1.0;
        scale = absxk;
      } else {
        t = absxk / 3.3121686421112381E-170;
        DistTarget = t * t;
      }

      absxk = fabs(Rsc->data[n + Rsc->size[0]]);
      if (absxk > scale) {
        t = scale / absxk;
        DistTarget = DistTarget * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        DistTarget += t * t;
      }

      absxk = fabs(Rsc->data[n + Rsc->size[0] * 2]);
      if (absxk > scale) {
        t = scale / absxk;
        DistTarget = DistTarget * t * t + 1.0;
        scale = absxk;
      } else {
        t = absxk / scale;
        DistTarget += t * t;
      }

      DistTarget = scale * sqrt(DistTarget);

      // Distance to target
      if ((MFR->Dmin < DistTarget) && (DistTarget < MFR->Dmax)) {
        // Distance check
        ibmat = MFR->ed->size[1];
        nx = static_cast<int>(pos->data[itilerow]);
        ntilerows = b_MFR->size[0];
        b_MFR->size[0] = ibmat;
        emxEnsureCapacity_real_T(b_MFR, ntilerows);
        for (ntilerows = 0; ntilerows < ibmat; ntilerows++) {
          b_MFR->data[ntilerows] = MFR->ed->data[(nx + MFR->ed->size[0] *
            ntilerows) - 1];
        }

        t = (Rsc->data[n] * b_MFR->data[0] + Rsc->data[n + Rsc->size[0]] *
             b_MFR->data[1]) + Rsc->data[n + Rsc->size[0] * 2] * b_MFR->data[2];

        // Length of projection R_p
        ibmat = MFR->ed->size[1];
        ntilerows = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = ibmat;
        emxEnsureCapacity_real_T(y, ntilerows);
        for (ntilerows = 0; ntilerows < ibmat; ntilerows++) {
          y->data[ntilerows] = MFR->ed->data[(nx + MFR->ed->size[0] * ntilerows)
            - 1] * t;
        }

        DistTarget = Rsc->data[n] - y->data[0];
        scale = Rsc->data[n + Rsc->size[0]] - y->data[1];
        absxk = Rsc->data[n + Rsc->size[0] * 2] - y->data[2];
        ibmat = MFR->ee->size[1];
        ntilerows = b_MFR->size[0];
        b_MFR->size[0] = ibmat;
        emxEnsureCapacity_real_T(b_MFR, ntilerows);
        for (ntilerows = 0; ntilerows < ibmat; ntilerows++) {
          b_MFR->data[ntilerows] = MFR->ee->data[(nx + MFR->ee->size[0] *
            ntilerows) - 1];
        }

        a = ((DistTarget * b_MFR->data[0] + scale * b_MFR->data[1]) + absxk *
             b_MFR->data[2]) / (t * MFR->tge);
        ibmat = MFR->ea->size[1];
        ntilerows = b_MFR->size[0];
        b_MFR->size[0] = ibmat;
        emxEnsureCapacity_real_T(b_MFR, ntilerows);
        for (ntilerows = 0; ntilerows < ibmat; ntilerows++) {
          b_MFR->data[ntilerows] = MFR->ea->data[(nx + MFR->ea->size[0] *
            ntilerows) - 1];
        }

        DistTarget = ((DistTarget * b_MFR->data[0] + scale * b_MFR->data[1]) +
                      absxk * b_MFR->data[2]) / (t * MFR->tga);
        DistTarget = a * a + DistTarget * DistTarget;
        if (DistTarget <= 1.0) {
          // Enters scan cone
          // Affects signal power; <1
          // Received signal power divided by noise
          scale = Rsc->data[n];
          t = scale * scale;
          scale = Rsc->data[n + Rsc->size[0]];
          t += scale * scale;
          scale = Rsc->data[n + Rsc->size[0] * 2];
          t += scale * scale;
          if (MFR->Pc * (1.0 - 0.5 * DistTarget) * TG->RCS->data[n] / (t * t) >
              MFR->Tr) {
            // Detected
            a = TG->ID->data[n];
            nx = MFR->tgID->size[0] * MFR->tgID->size[1];
            Lia = false;
            ibmat = 0;
            exitg1 = false;
            while ((!exitg1) && (ibmat <= nx - 1)) {
              scale = MFR->tgID->data[ibmat];
              DistTarget = fabs(scale / 2.0);
              if ((!rtIsInf(DistTarget)) && (!rtIsNaN(DistTarget))) {
                if (DistTarget <= 2.2250738585072014E-308) {
                  DistTarget = 4.94065645841247E-324;
                } else {
                  frexp(DistTarget, &exponent);
                  DistTarget = ldexp(1.0, exponent - 53);
                }
              } else {
                DistTarget = rtNaN;
              }

              if ((fabs(MFR->tgID->data[ibmat] - a) < DistTarget) || (rtIsInf(a)
                   && rtIsInf(scale) && ((a > 0.0) == (MFR->tgID->data[ibmat] >
                     0.0)))) {
                Lia = true;
                exitg1 = true;
              } else {
                ibmat++;
              }
            }

            if (!Lia) {
              nx = MFR->tgID->size[0] * MFR->tgID->size[1];
              Lia = false;
              ntilerows = -1;
              ibmat = 0;
              exitg1 = false;
              while ((!exitg1) && (ibmat <= nx - 1)) {
                DistTarget = fabs(MFR->tgID->data[ibmat] / 2.0);
                if ((!rtIsInf(DistTarget)) && (!rtIsNaN(DistTarget))) {
                  if (DistTarget <= 2.2250738585072014E-308) {
                    DistTarget = 4.94065645841247E-324;
                  } else {
                    frexp(DistTarget, &b_exponent);
                    DistTarget = ldexp(1.0, b_exponent - 53);
                  }
                } else {
                  DistTarget = rtNaN;
                }

                if (fabs(MFR->tgID->data[ibmat]) < DistTarget) {
                  Lia = true;
                  ntilerows = ibmat;
                  exitg1 = true;
                } else {
                  ibmat++;
                }
              }

              if (Lia) {
                MFR->tgID->data[ntilerows] = TG->ID->data[n];
              }
            }

            // OUT = [OUT; Rsc(n,:) + MFR.Loc];
          }
        }
      }
    }

    ibmat = Rsc->size[0] * Rsc->size[1];
    i1 = Rsc->size[0] * Rsc->size[1];
    Rsc->size[1] = 3;
    emxEnsureCapacity_real_T(Rsc, i1);
    for (i1 = 0; i1 < ibmat; i1++) {
      Rsc->data[i1] += dRsc->data[i1];
    }
  }

  emxFree_real_T(&y);

  // Checking position of tracked targets at time T+dt
  n = MFR->tgID->size[0] * MFR->tgID->size[1];
  ntilerows = 0;
  i = MFR->tgID->size[0] * MFR->tgID->size[1];
  for (ibmat = 0; ibmat < i; ibmat++) {
    if (MFR->tgID->data[ibmat] != 0.0) {
      ntilerows++;
    }
  }

  emxInit_real_T(&TrackedID, 1);
  i = TrackedID->size[0];
  TrackedID->size[0] = ntilerows;
  emxEnsureCapacity_real_T(TrackedID, i);
  ntilerows = -1;
  for (ibmat = 0; ibmat < n; ibmat++) {
    if (MFR->tgID->data[ibmat] != 0.0) {
      ntilerows++;
      TrackedID->data[ntilerows] = MFR->tgID->data[ibmat];
    }
  }

  emxInit_real_T(&Nrm, 1);
  emxInit_boolean_T(&TrackedIDcheck, 1);
  emxInit_int32_T(&iloc, 1);
  local_ismember(TrackedID, TG->ID, TrackedIDcheck, iloc);
  i = Nrm->size[0];
  Nrm->size[0] = iloc->size[0];
  emxEnsureCapacity_real_T(Nrm, i);
  ibmat = iloc->size[0];
  for (i = 0; i < ibmat; i++) {
    Nrm->data[i] = iloc->data[i];
  }

  i = dRsc->size[0] * dRsc->size[1];
  dRsc->size[0] = Nrm->size[0];
  dRsc->size[1] = 3;
  emxEnsureCapacity_real_T(dRsc, i);
  ibmat = Nrm->size[0];
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < ibmat; i1++) {
      ntilerows = static_cast<int>(Nrm->data[i1]) - 1;
      dRsc->data[i1 + dRsc->size[0] * i] = TG->R0->data[ntilerows + TG->R0->
        size[0] * i] + TG->V->data[ntilerows + TG->V->size[0] * i] * dT;
    }
  }

  // Transition to XYZ coord with MFR at center
  i = b->size[0] * b->size[1];
  b->size[0] = dRsc->size[0];
  b->size[1] = 3;
  emxEnsureCapacity_real_T(b, i);
  ntilerows = dRsc->size[0];
  for (nx = 0; nx < 3; nx++) {
    ibmat = nx * ntilerows;
    for (itilerow = 0; itilerow < ntilerows; itilerow++) {
      b->data[ibmat + itilerow] = MFR->Loc[nx];
    }
  }

  ibmat = dRsc->size[0] * dRsc->size[1];
  i = b->size[0] * b->size[1];
  b->size[0] = dRsc->size[0];
  b->size[1] = 3;
  emxEnsureCapacity_real_T(b, i);
  for (i = 0; i < ibmat; i++) {
    b->data[i] = dRsc->data[i] - b->data[i];
  }

  sz_idx_0 = static_cast<unsigned int>(b->size[0]);
  i = Nrm->size[0];
  Nrm->size[0] = static_cast<int>(sz_idx_0);
  emxEnsureCapacity_real_T(Nrm, i);
  ibmat = static_cast<int>(sz_idx_0);
  for (i = 0; i < ibmat; i++) {
    Nrm->data[i] = 0.0;
  }

  ntilerows = b->size[0];
  for (nx = 0; nx < ntilerows; nx++) {
    scale = 3.3121686421112381E-170;
    absxk = fabs(b->data[nx]);
    if (absxk > 3.3121686421112381E-170) {
      DistTarget = 1.0;
      scale = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      DistTarget = t * t;
    }

    absxk = fabs(b->data[nx + ntilerows]);
    if (absxk > scale) {
      t = scale / absxk;
      DistTarget = DistTarget * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      DistTarget += t * t;
    }

    absxk = fabs(b->data[nx + (ntilerows << 1)]);
    if (absxk > scale) {
      t = scale / absxk;
      DistTarget = DistTarget * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      DistTarget += t * t;
    }

    Nrm->data[nx] = scale * sqrt(DistTarget);
  }

  emxFree_real_T(&b);

  // Distance to target
  i = TrackedIDcheck->size[0];
  TrackedIDcheck->size[0] = Nrm->size[0];
  emxEnsureCapacity_boolean_T(TrackedIDcheck, i);
  ibmat = Nrm->size[0];
  for (i = 0; i < ibmat; i++) {
    TrackedIDcheck->data[i] = ((MFR->Dmin < Nrm->data[i]) && (MFR->Dmax >
      Nrm->data[i]));
  }

  // Distance check
  i = b_MFR->size[0];
  b_MFR->size[0] = TrackedIDcheck->size[0];
  emxEnsureCapacity_real_T(b_MFR, i);
  ibmat = TrackedIDcheck->size[0];
  for (i = 0; i < ibmat; i++) {
    b_MFR->data[i] = static_cast<double>(TrackedIDcheck->data[i]) *
      TrackedID->data[i];
  }

  emxInit_real_T(&TrackedIDnext, 1);
  nonzeros(b_MFR, TrackedIDnext);

  // Trackable ID
  // Check for lost targets and their removal from the table MFR.tgID
  i = b_MFR->size[0];
  b_MFR->size[0] = TrackedIDcheck->size[0];
  emxEnsureCapacity_real_T(b_MFR, i);
  ibmat = TrackedIDcheck->size[0];
  for (i = 0; i < ibmat; i++) {
    b_MFR->data[i] = static_cast<double>(!TrackedIDcheck->data[i]) *
      TrackedID->data[i];
  }

  emxInit_real_T(&TrackedIDlost, 1);
  nonzeros(b_MFR, TrackedIDlost);

  // Lost targets
  b_local_ismember(TrackedIDlost, MFR->tgID, TrackedIDcheck, iloc);
  ibmat = iloc->size[0] - 1;
  for (i = 0; i <= ibmat; i++) {
    MFR->tgID->data[iloc->data[i] - 1] = 0.0;
  }

  // removal
  // Get tracked target's coordinates;
  local_ismember(TrackedIDnext, TrackedID, TrackedIDcheck, iloc);
  i = Nrm->size[0];
  Nrm->size[0] = iloc->size[0];
  emxEnsureCapacity_real_T(Nrm, i);
  ibmat = iloc->size[0];
  emxFree_real_T(&TrackedID);
  for (i = 0; i < ibmat; i++) {
    Nrm->data[i] = iloc->data[i];
  }

  i = Rsc->size[0] * Rsc->size[1];
  Rsc->size[0] = Nrm->size[0];
  Rsc->size[1] = 3;
  emxEnsureCapacity_real_T(Rsc, i);
  ibmat = Nrm->size[0];
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < ibmat; i1++) {
      Rsc->data[i1 + Rsc->size[0] * i] = dRsc->data[(static_cast<int>(Nrm->
        data[i1]) + dRsc->size[0] * i) - 1];
    }
  }

  i = dRsc->size[0] * dRsc->size[1];
  dRsc->size[0] = Rsc->size[0];
  dRsc->size[1] = 3;
  emxEnsureCapacity_real_T(dRsc, i);
  ibmat = Rsc->size[0] * Rsc->size[1];
  for (i = 0; i < ibmat; i++) {
    dRsc->data[i] = Rsc->data[i];
  }

  // Tracked coordinates
  i = Rsc->size[0] * Rsc->size[1];
  Rsc->size[0] = Nrm->size[0];
  Rsc->size[1] = 3;
  emxEnsureCapacity_real_T(Rsc, i);
  ibmat = Nrm->size[0];
  for (i = 0; i < 3; i++) {
    for (i1 = 0; i1 < ibmat; i1++) {
      Rsc->data[i1 + Rsc->size[0] * i] = TG->V->data[(static_cast<int>(Nrm->
        data[i1]) + TG->V->size[0] * i) - 1];
    }
  }

  emxInit_boolean_T(&tf, 1);

  // Tracked speed
  // [~,IDtoRow]=ismember(TrackedIDnew,MFR.tgID);
  // MFR.tgID = zeros(size(MFR.tgID));
  // MFR.tgID(IDtoRow) = TrackedIDnew;    %Table of tracked targets
  MFR->tsc = b_mod(ts->data[ts->size[1] - 1] + MFR->Tscan, dT);

  // Next scan time deviation
  MFR->pos = pos->data[pos->size[1] - 1] + 1.0;

  // Next cycle start
  // Check for new targets
  c_local_ismember(TrackedIDnext, MFR->tgIDprev, TrackedIDcheck);
  b_local_ismember(TrackedIDlost, MFR->tgIDprev, tf, iloc);
  ibmat = TrackedIDcheck->size[0];
  emxFree_boolean_T(&tf);
  emxFree_real_T(&TrackedIDlost);
  emxFree_real_T(&pos);
  emxFree_real_T(&ts);
  for (i = 0; i < ibmat; i++) {
    TrackedIDcheck->data[i] = !TrackedIDcheck->data[i];
  }

  emxInit_int32_T(&b_iloc, 1);
  eml_find(TrackedIDcheck, b_iloc);
  i = b_MFR->size[0];
  b_MFR->size[0] = b_iloc->size[0];
  emxEnsureCapacity_real_T(b_MFR, i);
  ibmat = b_iloc->size[0];
  for (i = 0; i < ibmat; i++) {
    b_MFR->data[i] = TrackedIDnext->data[b_iloc->data[i] - 1];
  }

  emxInit_int32_T(&c_iloc, 1);
  b_local_ismember(b_MFR, MFR->tgID, TrackedIDcheck, b_iloc);
  b_local_ismember(TrackedIDnext, MFR->tgID, TrackedIDcheck, c_iloc);

  // Tracked ID, R,V
  i = b_MFR->size[0];
  b_MFR->size[0] = iloc->size[0];
  emxEnsureCapacity_real_T(b_MFR, i);
  ibmat = iloc->size[0];
  emxFree_boolean_T(&TrackedIDcheck);
  for (i = 0; i < ibmat; i++) {
    b_MFR->data[i] = iloc->data[i];
  }

  emxFree_int32_T(&iloc);
  nonzeros(b_MFR, MSG->IDLost);
  i = b_MFR->size[0];
  b_MFR->size[0] = b_iloc->size[0];
  emxEnsureCapacity_real_T(b_MFR, i);
  ibmat = b_iloc->size[0];
  for (i = 0; i < ibmat; i++) {
    b_MFR->data[i] = b_iloc->data[i];
  }

  emxFree_int32_T(&b_iloc);
  nonzeros(b_MFR, MSG->IDNew);
  i = b_MFR->size[0];
  b_MFR->size[0] = c_iloc->size[0];
  emxEnsureCapacity_real_T(b_MFR, i);
  ibmat = c_iloc->size[0];
  for (i = 0; i < ibmat; i++) {
    b_MFR->data[i] = c_iloc->data[i];
  }

  emxFree_int32_T(&c_iloc);
  nonzeros(b_MFR, MSG->IDTracked);
  ibmat = dRsc->size[0];
  i = MSG->RTrackedX->size[0];
  MSG->RTrackedX->size[0] = dRsc->size[0];
  emxEnsureCapacity_real_T(MSG->RTrackedX, i);
  emxFree_real_T(&b_MFR);
  for (i = 0; i < ibmat; i++) {
    MSG->RTrackedX->data[i] = dRsc->data[i];
  }

  ibmat = dRsc->size[0];
  i = MSG->RTrackedY->size[0];
  MSG->RTrackedY->size[0] = dRsc->size[0];
  emxEnsureCapacity_real_T(MSG->RTrackedY, i);
  for (i = 0; i < ibmat; i++) {
    MSG->RTrackedY->data[i] = dRsc->data[i + dRsc->size[0]];
  }

  ibmat = dRsc->size[0];
  i = MSG->RTrackedZ->size[0];
  MSG->RTrackedZ->size[0] = dRsc->size[0];
  emxEnsureCapacity_real_T(MSG->RTrackedZ, i);
  for (i = 0; i < ibmat; i++) {
    MSG->RTrackedZ->data[i] = dRsc->data[i + dRsc->size[0] * 2];
  }

  emxFree_real_T(&dRsc);
  ibmat = Nrm->size[0];
  i = MSG->VTrackedX->size[0];
  MSG->VTrackedX->size[0] = Nrm->size[0];
  emxEnsureCapacity_real_T(MSG->VTrackedX, i);
  for (i = 0; i < ibmat; i++) {
    MSG->VTrackedX->data[i] = Rsc->data[i];
  }

  ibmat = Nrm->size[0];
  i = MSG->VTrackedY->size[0];
  MSG->VTrackedY->size[0] = Nrm->size[0];
  emxEnsureCapacity_real_T(MSG->VTrackedY, i);
  for (i = 0; i < ibmat; i++) {
    MSG->VTrackedY->data[i] = Rsc->data[i + Rsc->size[0]];
  }

  ibmat = Nrm->size[0];
  i = MSG->VTrackedZ->size[0];
  MSG->VTrackedZ->size[0] = Nrm->size[0];
  emxEnsureCapacity_real_T(MSG->VTrackedZ, i);
  emxFree_real_T(&Nrm);
  for (i = 0; i < ibmat; i++) {
    MSG->VTrackedZ->data[i] = Rsc->data[i + Rsc->size[0] * 2];
  }

  emxFree_real_T(&Rsc);
  i = MFR->tgIDprev->size[0] * MFR->tgIDprev->size[1];
  MFR->tgIDprev->size[0] = TrackedIDnext->size[0];
  MFR->tgIDprev->size[1] = 1;
  emxEnsureCapacity_real_T(MFR->tgIDprev, i);
  ibmat = TrackedIDnext->size[0];
  for (i = 0; i < ibmat; i++) {
    MFR->tgIDprev->data[i] = TrackedIDnext->data[i];
  }

  emxFree_real_T(&TrackedIDnext);

  // for the next cycle
  // Output to PBU
  //      disp(['!!!---Time T=' num2str(T)]);
  //      if ~isempty(TrackedIDlost)
  //          disp(['!-Targets ID=[' num2str(TrackedIDlost(:)') '] lost']);
  //      end
  //      if ~isempty(TrackedIDnew)
  //          disp(['!-New targets ID=[' num2str(TrackedIDnew(:)') '] detected']); 
  //      end
  //      for n=1:length(TrackedIDnext)
  //          disp(['Target ID:' num2str(TrackedIDnext(n)) '  Coordinates [' num2str(RscTracked(n,:)) ']']); 
  //      end
}

//
// File trailer for MFR_V2_Cycle.cpp
//
// [EOF]
//
