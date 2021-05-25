//
// File: MFR_V2_GenerateMFRType.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//

// Include Files
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_data.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_Cycle_initialize.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "inv.h"
#include "linspace.h"
#include "normalize.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <iostream>

// Function Definitions

//
// = 0.0300
//  = 100000
//  = 8.2443e+03
//  = 6.6713e-04
//  = 5.0000e-05
//  = 20
//  = 0.0213
//  = 0.0152
//  = 0.1000
//  = 0.1000
//  = 0
//  =0.5236
//  = 297
//  = 35
//  = 400000
//  = 1.7617e-15
//  = 3.1056e+04
//  = 1.2146e+07
//  = 6
//  = 64
//  = 64
// Arguments    : const double Loc[3]
//                double n[3]
//                double lambda
//                double Dmax
//                double Dmin
//                double Tscan
//                double Timp
//                double V_res
//                double asim_res
//                double elev_res
//                double asim_res_trace_cf
//                double elev_res_trace_cf
//                double elev1
//                double elev2
//                double Nasim
//                double Nelev
//                double Bandwidth
//                double Noise
//                double Gain
//                double P_peak
//                double Tr
//                double Ntraj
//                double Nmissiles
//                struct1_T *MFR
// Return Type  : void
//
void MFR_V2_GenerateMFRType(const double Loc[3], double n[3], double lambda,
  double Dmax, double Dmin, double Tscan, double Timp, double V_res, double
  asim_res, double elev_res, double asim_res_trace_cf, double elev_res_trace_cf,
  double elev1, double elev2, double Nasim, double Nelev, double Bandwidth,
  double Noise, double Gain, double P_peak, double Tr, double Ntraj, double
  Nmissiles, struct1_T *MFR)
{
  double e[3];
  double b_e[3];
  double delta1;
  double t0_elev2;
  double t0_p_idx_0;
  double t0_p_idx_1;
  double t0_p_idx_2;
  double c_e[9];
  double dv[9];
  int i;
  emxArray_real_T *elev;
  emxArray_real_T *asim;
  int ibtile;
  int i1;
  emxArray_real_T *b;
  int k;
  int nrows;
  int coffset;
  emxArray_real_T *x;
  int aoffset;
  int b_n;
  int i2;
  int tmp_tmp;
  int vstride;
  int b_i;
  emxArray_real_T *b_x;
  emxArray_real_T *c_x;
  emxArray_real_T *d_x;
  emxArray_real_T *result;
  boolean_T empty_non_axis_sizes;
  signed char input_sizes_idx_1;
  signed char b_input_sizes_idx_1;
  signed char sizes_idx_1;
  emxArray_real_T *y;
  emxArray_real_T *A;
  emxArray_real_T *C;
  if (isInitialized_MFR_V2_Cycle == false) {
    MFR_V2_Cycle_initialize();
  }

  e[0] = n[0];
  e[1] = n[1];
  e[2] = n[2];
  normalize(e, n);
  e[1] = 0.0;
  e[2] = 0.0;
  if (!(n[1] != 0.0)) {
    e[0] = n[2];
    e[2] = -n[0];
  } else {
    e[0] = n[1];
    e[1] = -n[0];
  }

  b_e[0] = e[0];
  b_e[1] = e[1];
  b_e[2] = e[2];
  normalize(b_e, e);

  //  %amount of asimuth points
  //   %amount of angle of elevation points
  //  %Number of traceable trajectories
  //  Radar location
  //  Later use for scanning parametres:
  if ((elev1 > elev2) || (rtIsNaN(elev1) && (!rtIsNaN(elev2)))) {
    delta1 = elev2;
  } else {
    delta1 = elev1;
  }

  if ((elev1 < elev2) || (rtIsNaN(elev1) && (!rtIsNaN(elev2)))) {
    t0_elev2 = elev2;
  } else {
    t0_elev2 = elev1;
  }

  t0_p_idx_0 = n[1] * e[2] - n[2] * e[1];
  t0_p_idx_1 = n[2] * e[0] - n[0] * e[2];
  t0_p_idx_2 = n[0] * e[1] - n[1] * e[0];
  MFR->lambda = lambda;
  MFR->Dmax = Dmax;
  MFR->Dmin = Dmin;
  MFR->Tscan = Tscan;
  MFR->Timp = Timp;
  MFR->V_res = V_res;
  MFR->asim_res = asim_res;
  MFR->elev_res = elev_res;
  MFR->asim_res_trace_cf = asim_res_trace_cf;
  MFR->elev_res_trace_cf = elev_res_trace_cf;
  MFR->elev1 = delta1;
  MFR->elev2 = t0_elev2;
  MFR->Nasim = Nasim;
  MFR->Nelev = Nelev;
  MFR->Bandwidth = Bandwidth;
  MFR->Noise = Noise;
  MFR->Gain = Gain;
  MFR->P_peak = P_peak;
  MFR->Tr = Tr;
  MFR->Ntraj = Ntraj;
  MFR->Nmissiles = Nmissiles;

  // save('MFR.mat','MFR');
  // disp(MFR);
  // Calculation of coord transition matrix LOCXYZ->GLOBXYZ
  MFR->n[0] = n[0];
  MFR->e[0] = e[0];
  MFR->p[0] = t0_p_idx_0;
  MFR->Loc[0] = Loc[0];
  c_e[0] = e[0];
  c_e[3] = t0_p_idx_0;
  c_e[6] = n[0];
  MFR->n[1] = n[1];
  MFR->e[1] = e[1];
  MFR->p[1] = t0_p_idx_1;
  MFR->Loc[1] = Loc[1];
  c_e[1] = e[1];
  c_e[4] = t0_p_idx_1;
  c_e[7] = n[1];
  MFR->n[2] = n[2];
  MFR->e[2] = e[2];
  MFR->p[2] = t0_p_idx_2;
  MFR->Loc[2] = Loc[2];
  c_e[2] = e[2];
  c_e[5] = t0_p_idx_2;
  c_e[8] = n[2];
  inv(c_e, dv);
  for (i = 0; i < 3; i++) {
    MFR->A[3 * i] = dv[i];
    MFR->A[3 * i + 1] = dv[i + 3];
    MFR->A[3 * i + 2] = dv[i + 6];
  }

  emxInit_real_T(&elev, 1);
  emxInit_real_T(&asim, 2);

  // Asimuth and elevation angles
  linspace(delta1 + elev_res / 2.0, t0_elev2 - elev_res / 2.0, Nelev, asim);
  i = elev->size[0];
  elev->size[0] = asim->size[1];
  emxEnsureCapacity_real_T(elev, i);
  ibtile = asim->size[1];
  for (i = 0; i < ibtile; i++) {
    elev->data[i] = asim->data[i];
  }

  delta1 = Nasim + 1.0;
  if (Nasim + 1.0 < 0.0) {
    delta1 = 0.0;
  }

  i = asim->size[0] * asim->size[1];
  asim->size[0] = 1;
  i1 = static_cast<int>(floor(delta1));
  asim->size[1] = i1;
  emxEnsureCapacity_real_T(asim, i);
  if (i1 >= 1) {
    asim->data[i1 - 1] = 6.2831853071795862;
    if (asim->size[1] >= 2) {
      asim->data[0] = 0.0;
      if (asim->size[1] >= 3) {
        delta1 = 6.2831853071795862 / (static_cast<double>(asim->size[1]) - 1.0);
        i = asim->size[1];
        for (k = 0; k <= i - 3; k++) {
          asim->data[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
        }
      }
    }
  }

  emxInit_real_T(&b, 2);
  if (1 > asim->size[1] - 1) {
    i = 0;
  } else {
    i = asim->size[1] - 1;
  }

  i1 = asim->size[0] * asim->size[1];
  asim->size[1] = i;
  emxEnsureCapacity_real_T(asim, i1);
  i1 = b->size[0] * b->size[1];
  b->size[0] = elev->size[0];
  b->size[1] = i;
  emxEnsureCapacity_real_T(b, i1);
  nrows = elev->size[0];
  for (coffset = 0; coffset < i; coffset++) {
    ibtile = coffset * nrows;
    for (k = 0; k < nrows; k++) {
      b->data[ibtile + k] = elev->data[k];
    }
  }
  //MFR->elev = elev;
  //std::cout << "target_id: " << elev->size[1] << std::endl;
  i1 = MFR->elev->size[0] * MFR->elev->size[1];
  MFR->elev->size[0] = b->size[0];
  MFR->elev->size[1] = b->size[1];
  //std::cout << "target_id: " << b->size[1] << std::endl;

  emxEnsureCapacity_real_T(MFR->elev, i1);
  ibtile = b->size[0] * b->size[1];
  for (i1 = 0; i1 < ibtile; i1++) {
    MFR->elev->data[i1] = b->data[i1];
  }

  // MFR - scanning pattern
  i1 = static_cast<int>((static_cast<double>(i) / 2.0));
  emxInit_real_T(&x, 1);
  for (aoffset = 0; aoffset < i1; aoffset++) {
    b_n = (aoffset << 1) + 1;
    ibtile = MFR->elev->size[0];
    i2 = x->size[0];
    x->size[0] = MFR->elev->size[0];
    emxEnsureCapacity_real_T(x, i2);
    for (i2 = 0; i2 < ibtile; i2++) {
      x->data[i2] = MFR->elev->data[i2 + MFR->elev->size[0] * b_n];
    }

    nrows = 2;
    if (MFR->elev->size[0] != 1) {
      nrows = 1;
    }

    if (MFR->elev->size[0] != 0) {
      if (nrows <= 1) {
        i2 = MFR->elev->size[0];
      } else {
        i2 = 1;
      }

      if (i2 > 1) {
        vstride = 1;
        for (k = 0; k <= nrows - 2; k++) {
          vstride *= MFR->elev->size[0];
        }

        if (nrows <= 1) {
          i2 = MFR->elev->size[0] - 1;
        } else {
          i2 = 0;
        }

        nrows = (i2 + 1) >> 1;
        ibtile = vstride - 1;
        for (b_i = 0; b_i <= ibtile; b_i++) {
          for (k = 0; k < nrows; k++) {
            tmp_tmp = b_i + k * vstride;
            delta1 = x->data[tmp_tmp];
            coffset = b_i + (i2 - k) * vstride;
            x->data[tmp_tmp] = x->data[coffset];
            x->data[coffset] = delta1;
          }
        }
      }
    }

    ibtile = x->size[0];
    for (i2 = 0; i2 < ibtile; i2++) {
      MFR->elev->data[i2 + MFR->elev->size[0] * b_n] = x->data[i2];
    }
  }

  i1 = b->size[0] * b->size[1];
  b->size[0] = elev->size[0];
  b->size[1] = i;
  emxEnsureCapacity_real_T(b, i1);
  nrows = elev->size[0];
  for (coffset = 0; coffset < i; coffset++) {
    ibtile = coffset * nrows;
    for (tmp_tmp = 0; tmp_tmp < nrows; tmp_tmp++) {
      b->data[ibtile + tmp_tmp] = asim->data[coffset];
    }
  }

  emxFree_real_T(&asim);
  i = elev->size[0];
  elev->size[0] = MFR->elev->size[0] * MFR->elev->size[1];
  emxEnsureCapacity_real_T(elev, i);
  ibtile = MFR->elev->size[0] * MFR->elev->size[1];
  for (i = 0; i < ibtile; i++) {
    elev->data[i] = MFR->elev->data[i];
  }

  nrows = MFR->elev->size[0] * MFR->elev->size[1];
  i = MFR->elev->size[0] * MFR->elev->size[1];
  MFR->elev->size[0] = nrows;
  MFR->elev->size[1] = 1;
  emxEnsureCapacity_real_T(MFR->elev, i);
  i = x->size[0];
  x->size[0] = b->size[0] * b->size[1];
  emxEnsureCapacity_real_T(x, i);
  ibtile = b->size[0] * b->size[1];
  for (i = 0; i < ibtile; i++) {
    x->data[i] = b->data[i];
  }

  i = MFR->asim->size[0] * MFR->asim->size[1];
  MFR->asim->size[0] = b->size[0] * b->size[1];
  MFR->asim->size[1] = 1;
  emxEnsureCapacity_real_T(MFR->asim, i);
  ibtile = b->size[0] * b->size[1];
  for (i = 0; i < ibtile; i++) {
    MFR->asim->data[i] = b->data[i];
  }

  emxFree_real_T(&b);
  emxInit_real_T(&b_x, 2);
  i = b_x->size[0] * b_x->size[1];
  b_x->size[0] = elev->size[0];
  b_x->size[1] = 1;
  emxEnsureCapacity_real_T(b_x, i);
  ibtile = elev->size[0];
  for (i = 0; i < ibtile; i++) {
    b_x->data[i] = elev->data[i];
  }

  nrows = MFR->elev->size[0];
  for (k = 0; k < nrows; k++) {
    b_x->data[k] = cos(b_x->data[k]);
  }

  emxInit_real_T(&c_x, 2);
  i = c_x->size[0] * c_x->size[1];
  c_x->size[0] = x->size[0];
  c_x->size[1] = 1;
  emxEnsureCapacity_real_T(c_x, i);
  ibtile = x->size[0];
  for (i = 0; i < ibtile; i++) {
    c_x->data[i] = x->data[i];
  }

  nrows = MFR->asim->size[0];
  for (k = 0; k < nrows; k++) {
    c_x->data[k] = cos(c_x->data[k]);
  }

  emxInit_real_T(&d_x, 2);
  i = d_x->size[0] * d_x->size[1];
  d_x->size[0] = x->size[0];
  d_x->size[1] = 1;
  emxEnsureCapacity_real_T(d_x, i);
  ibtile = x->size[0];
  for (i = 0; i < ibtile; i++) {
    d_x->data[i] = x->data[i];
  }

  nrows = MFR->asim->size[0];
  for (k = 0; k < nrows; k++) {
    d_x->data[k] = sin(d_x->data[k]);
  }

  emxInit_real_T(&result, 2);
  i = c_x->size[0] * c_x->size[1];
  c_x->size[0] = b_x->size[0];
  c_x->size[1] = 1;
  emxEnsureCapacity_real_T(c_x, i);
  ibtile = b_x->size[0] * b_x->size[1] - 1;
  for (i = 0; i <= ibtile; i++) {
    c_x->data[i] *= b_x->data[i];
  }

  i = b_x->size[0] * b_x->size[1];
  i1 = b_x->size[0] * b_x->size[1];
  b_x->size[1] = 1;
  emxEnsureCapacity_real_T(b_x, i1);
  ibtile = i - 1;
  for (i = 0; i <= ibtile; i++) {
    b_x->data[i] *= d_x->data[i];
  }

  i = d_x->size[0] * d_x->size[1];
  d_x->size[0] = elev->size[0];
  d_x->size[1] = 1;
  emxEnsureCapacity_real_T(d_x, i);
  ibtile = elev->size[0];
  for (i = 0; i < ibtile; i++) {
    d_x->data[i] = elev->data[i];
  }

  nrows = MFR->elev->size[0];
  for (k = 0; k < nrows; k++) {
    d_x->data[k] = sin(d_x->data[k]);
  }

  if (c_x->size[0] != 0) {
    nrows = c_x->size[0];
  } else if (b_x->size[0] != 0) {
    nrows = b_x->size[0];
  } else if (d_x->size[0] != 0) {
    nrows = d_x->size[0];
  } else {
    nrows = 0;
  }

  empty_non_axis_sizes = (nrows == 0);
  if (empty_non_axis_sizes || (c_x->size[0] != 0)) {
    input_sizes_idx_1 = 1;
  } else {
    input_sizes_idx_1 = 0;
  }

  if (empty_non_axis_sizes || (b_x->size[0] != 0)) {
    b_input_sizes_idx_1 = 1;
  } else {
    b_input_sizes_idx_1 = 0;
  }

  if (empty_non_axis_sizes || (d_x->size[0] != 0)) {
    sizes_idx_1 = 1;
  } else {
    sizes_idx_1 = 0;
  }

  i = result->size[0] * result->size[1];
  result->size[0] = nrows;
  i1 = input_sizes_idx_1 + b_input_sizes_idx_1;
  result->size[1] = i1 + sizes_idx_1;
  emxEnsureCapacity_real_T(result, i);
  ibtile = input_sizes_idx_1;
  for (i = 0; i < ibtile; i++) {
    for (i2 = 0; i2 < nrows; i2++) {
      result->data[i2] = c_x->data[i2];
    }
  }

  emxFree_real_T(&c_x);
  ibtile = b_input_sizes_idx_1;
  for (i = 0; i < ibtile; i++) {
    for (i2 = 0; i2 < nrows; i2++) {
      result->data[i2 + result->size[0] * input_sizes_idx_1] = b_x->data[i2];
    }
  }

  emxFree_real_T(&b_x);
  ibtile = sizes_idx_1;
  for (i = 0; i < ibtile; i++) {
    for (i2 = 0; i2 < nrows; i2++) {
      result->data[i2 + result->size[0] * i1] = d_x->data[i2];
    }
  }

  emxFree_real_T(&d_x);
  emxInit_real_T(&y, 2);
  if (result->size[1] == 1) {
    i = y->size[0] * y->size[1];
    y->size[0] = result->size[0];
    y->size[1] = 3;
    emxEnsureCapacity_real_T(y, i);
    ibtile = result->size[0];
    for (i = 0; i < ibtile; i++) {
      nrows = result->size[1];
      for (i1 = 0; i1 < 3; i1++) {
        y->data[i + y->size[0] * i1] = 0.0;
        for (i2 = 0; i2 < nrows; i2++) {
          y->data[i + y->size[0] * i1] += result->data[i + result->size[0] * i2]
            * MFR->A[i2 + 3 * i1];
        }
      }
    }
  } else {
    nrows = result->size[0];
    ibtile = result->size[1];
    i = y->size[0] * y->size[1];
    y->size[0] = result->size[0];
    y->size[1] = 3;
    emxEnsureCapacity_real_T(y, i);
    for (tmp_tmp = 0; tmp_tmp < 3; tmp_tmp++) {
      coffset = tmp_tmp * nrows;
      vstride = tmp_tmp * ibtile;
      for (b_i = 0; b_i < nrows; b_i++) {
        y->data[coffset + b_i] = 0.0;
      }

      for (k = 0; k < ibtile; k++) {
        aoffset = k * nrows;
        delta1 = MFR->A[vstride + k];
        for (b_i = 0; b_i < nrows; b_i++) {
          i = coffset + b_i;
          y->data[i] += delta1 * result->data[aoffset + b_i];
        }
      }
    }
  }

  emxFree_real_T(&result);
  i = MFR->ed->size[0] * MFR->ed->size[1];
  MFR->ed->size[0] = y->size[0];
  MFR->ed->size[1] = 3;
  emxEnsureCapacity_real_T(MFR->ed, i);
  ibtile = y->size[0] * y->size[1];
  for (i = 0; i < ibtile; i++) {
    MFR->ed->data[i] = y->data[i];
  }

  i = elev->size[0];
  elev->size[0] = y->size[0];
  emxEnsureCapacity_real_T(elev, i);
  nrows = y->size[0];
  for (k = 0; k < nrows; k++) {
    delta1 = y->data[k];
    elev->data[k] = delta1 * delta1;
  }

  i = x->size[0];
  x->size[0] = y->size[0];
  emxEnsureCapacity_real_T(x, i);
  nrows = y->size[0];
  for (k = 0; k < nrows; k++) {
    delta1 = y->data[k + y->size[0]];
    x->data[k] = delta1 * delta1;
  }

  emxInit_real_T(&A, 2);
  ibtile = y->size[0];
  nrows = y->size[0];
  i = A->size[0] * A->size[1];
  A->size[0] = y->size[0];
  A->size[1] = 3;
  emxEnsureCapacity_real_T(A, i);
  for (i = 0; i < ibtile; i++) {
    A->data[i] = y->data[i];
  }

  for (i = 0; i < nrows; i++) {
    A->data[i + A->size[0]] = y->data[i + y->size[0]];
  }

  ibtile = elev->size[0];
  for (i = 0; i < ibtile; i++) {
    A->data[i + A->size[0] * 2] = -(elev->data[i] + x->data[i]) / y->data[i +
      y->size[0] * 2];
  }

  emxFree_real_T(&x);
  emxFree_real_T(&elev);
  emxInit_real_T(&C, 2);
  nrows = A->size[0];
  i = C->size[0] * C->size[1];
  C->size[0] = A->size[0];
  C->size[1] = 3;
  emxEnsureCapacity_real_T(C, i);
  for (tmp_tmp = 0; tmp_tmp < 3; tmp_tmp++) {
    coffset = tmp_tmp * nrows;
    vstride = tmp_tmp * 3;
    for (b_i = 0; b_i < nrows; b_i++) {
      C->data[coffset + b_i] = 0.0;
    }

    for (k = 0; k < 3; k++) {
      aoffset = k * nrows;
      delta1 = MFR->A[vstride + k];
      for (b_i = 0; b_i < nrows; b_i++) {
        i = coffset + b_i;
        C->data[i] += delta1 * A->data[aoffset + b_i];
      }
    }
  }

  b_normalize(C, A);
  i = MFR->ee->size[0] * MFR->ee->size[1];
  MFR->ee->size[0] = A->size[0];
  MFR->ee->size[1] = 3;
  emxEnsureCapacity_real_T(MFR->ee, i);
  ibtile = A->size[0] * A->size[1];
  emxFree_real_T(&C);
  for (i = 0; i < ibtile; i++) {
    MFR->ee->data[i] = A->data[i];
  }

  i = A->size[0] * A->size[1];
  A->size[0] = y->size[0];
  A->size[1] = 3;
  emxEnsureCapacity_real_T(A, i);
  if (y->size[0] != 0) {
    nrows = y->size[0];
    coffset = y->size[0] * 3;
    for (ibtile = 1; coffset < 0 ? ibtile >= 1 : ibtile <= 1; ibtile += coffset)
    {
      for (tmp_tmp = 1; tmp_tmp <= nrows; tmp_tmp++) {
        vstride = (tmp_tmp + nrows) - 1;
        aoffset = vstride + nrows;
        A->data[tmp_tmp - 1] = y->data[vstride] * MFR->ee->data[aoffset] -
          y->data[aoffset] * MFR->ee->data[vstride];
        A->data[vstride] = y->data[aoffset] * MFR->ee->data[tmp_tmp - 1] -
          y->data[tmp_tmp - 1] * MFR->ee->data[aoffset];
        A->data[aoffset] = y->data[tmp_tmp - 1] * MFR->ee->data[vstride] -
          y->data[vstride] * MFR->ee->data[tmp_tmp - 1];
      }
    }
  }

  emxFree_real_T(&y);
  i = MFR->ea->size[0] * MFR->ea->size[1];
  MFR->ea->size[0] = A->size[0];
  MFR->ea->size[1] = 3;
  emxEnsureCapacity_real_T(MFR->ea, i);
  ibtile = A->size[0] * A->size[1];
  for (i = 0; i < ibtile; i++) {
    MFR->ea->data[i] = A->data[i];
  }

  emxFree_real_T(&A);

  // Scan start
  MFR->tsc = 0.0;

  // Current scan time deviation
  MFR->pos = 1.0;

  // Current scan vector number (correlates with .tsc)
  nrows = MFR->asim->size[0];
  if (nrows <= 1) {
    nrows = 1;
  }

  if (MFR->asim->size[0] == 0) {
    MFR->posN = 0.0;
  } else {
    MFR->posN = nrows;
  }

  // number of positions
  // Scan parametres
  MFR->tge = tan(elev_res / 2.0);
  MFR->tga = tan(asim_res / 2.0);
  delta1 = Gain * lambda;
  MFR->Pc = P_peak * Timp * (delta1 * delta1) / 1984.4017075391882 / Noise;

  // Scan output
  ibtile = static_cast<int>(Ntraj);
  i = MFR->tgID->size[0] * MFR->tgID->size[1];
  MFR->tgID->size[0] = ibtile;
  MFR->tgID->size[1] = 1;
  emxEnsureCapacity_real_T(MFR->tgID, i);
  for (i = 0; i < ibtile; i++) {
    MFR->tgID->data[i] = 0.0;
  }

  MFR->tgIDprev->size[0] = 0;
  MFR->tgIDprev->size[1] = 0;
}

//
// File trailer for MFR_V2_GenerateMFRType.cpp
//
// [EOF]
//
