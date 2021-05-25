//
// File: normalize.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//

// Include Files
#include "normalize.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"
#include <math.h>

// Function Definitions

//
// Arguments    : const emxArray_real_T *a
//                emxArray_real_T *n
// Return Type  : void
//
void b_normalize(const emxArray_real_T *a, emxArray_real_T *n)
{
  emxArray_real_T *fillA;
  int i;
  int stride;
  emxArray_boolean_T *r;
  int end;
  int bcoef;
  emxArray_int32_T *r1;
  emxArray_real_T *y;
  unsigned int szy_idx_0;
  double scale;
  double absxk;
  double t;
  double yv;
  int k;
  emxInit_real_T(&fillA, 2);
  i = fillA->size[0] * fillA->size[1];
  fillA->size[0] = a->size[0];
  fillA->size[1] = 3;
  emxEnsureCapacity_real_T(fillA, i);
  stride = a->size[0] * a->size[1];
  for (i = 0; i < stride; i++) {
    fillA->data[i] = a->data[i];
  }

  emxInit_boolean_T(&r, 2);
  i = r->size[0] * r->size[1];
  r->size[0] = a->size[0];
  r->size[1] = 3;
  emxEnsureCapacity_boolean_T(r, i);
  stride = a->size[0] * a->size[1];
  for (i = 0; i < stride; i++) {
    r->data[i] = rtIsNaN(a->data[i]);
  }

  end = r->size[0] * 3 - 1;
  stride = 0;
  for (bcoef = 0; bcoef <= end; bcoef++) {
    if (r->data[bcoef]) {
      stride++;
    }
  }

  emxInit_int32_T(&r1, 1);
  i = r1->size[0];
  r1->size[0] = stride;
  emxEnsureCapacity_int32_T(r1, i);
  stride = 0;
  for (bcoef = 0; bcoef <= end; bcoef++) {
    if (r->data[bcoef]) {
      r1->data[stride] = bcoef + 1;
      stride++;
    }
  }

  emxFree_boolean_T(&r);
  stride = r1->size[0];
  for (i = 0; i < stride; i++) {
    fillA->data[r1->data[i] - 1] = 0.0;
  }

  emxFree_int32_T(&r1);
  emxInit_real_T(&y, 1);
  szy_idx_0 = static_cast<unsigned int>(fillA->size[0]);
  i = y->size[0];
  y->size[0] = static_cast<int>(szy_idx_0);
  emxEnsureCapacity_real_T(y, i);
  stride = static_cast<int>(szy_idx_0);
  for (i = 0; i < stride; i++) {
    y->data[i] = 0.0;
  }

  stride = fillA->size[0];
  for (bcoef = 0; bcoef < stride; bcoef++) {
    scale = 3.3121686421112381E-170;
    absxk = fabs(fillA->data[bcoef]);
    if (absxk > 3.3121686421112381E-170) {
      yv = 1.0;
      scale = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      yv = t * t;
    }

    absxk = fabs(fillA->data[bcoef + stride]);
    if (absxk > scale) {
      t = scale / absxk;
      yv = yv * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      yv += t * t;
    }

    absxk = fabs(fillA->data[bcoef + (stride << 1)]);
    if (absxk > scale) {
      t = scale / absxk;
      yv = yv * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      yv += t * t;
    }

    y->data[bcoef] = scale * sqrt(yv);
  }

  emxFree_real_T(&fillA);
  i = n->size[0] * n->size[1];
  stride = y->size[0];
  bcoef = a->size[0];
  if (stride < bcoef) {
    bcoef = stride;
  }

  if (y->size[0] == 1) {
    n->size[0] = a->size[0];
  } else if (a->size[0] == 1) {
    n->size[0] = y->size[0];
  } else if (a->size[0] == y->size[0]) {
    n->size[0] = a->size[0];
  } else {
    n->size[0] = bcoef;
  }

  n->size[1] = 3;
  emxEnsureCapacity_real_T(n, i);
  stride = y->size[0];
  bcoef = a->size[0];
  if (stride < bcoef) {
    bcoef = stride;
  }

  if (y->size[0] == 1) {
    bcoef = a->size[0];
  } else if (a->size[0] == 1) {
    bcoef = y->size[0];
  } else {
    if (a->size[0] == y->size[0]) {
      bcoef = a->size[0];
    }
  }

  if (bcoef != 0) {
    stride = (a->size[0] != 1);
    bcoef = (y->size[0] != 1);
    for (end = 0; end < 3; end++) {
      i = n->size[0] - 1;
      for (k = 0; k <= i; k++) {
        n->data[k + n->size[0] * end] = a->data[stride * k + a->size[0] * end] /
          y->data[bcoef * k];
      }
    }
  }

  emxFree_real_T(&y);
}

//
// Arguments    : const double a[3]
//                double n[3]
// Return Type  : void
//
void normalize(const double a[3], double n[3])
{
  int trueCount;
  double fillA[3];
  boolean_T unnamed_idx_2;
  boolean_T unnamed_idx_0;
  boolean_T unnamed_idx_1;
  int partialTrueCount;
  signed char tmp_data[3];
  double scale;
  double absxk;
  double t;
  double b;
  trueCount = 0;
  fillA[0] = a[0];
  unnamed_idx_2 = rtIsNaN(a[0]);
  unnamed_idx_0 = unnamed_idx_2;
  if (unnamed_idx_2) {
    trueCount = 1;
  }

  fillA[1] = a[1];
  unnamed_idx_2 = rtIsNaN(a[1]);
  unnamed_idx_1 = unnamed_idx_2;
  if (unnamed_idx_2) {
    trueCount++;
  }

  fillA[2] = a[2];
  unnamed_idx_2 = rtIsNaN(a[2]);
  if (unnamed_idx_2) {
    trueCount++;
  }

  partialTrueCount = 0;
  if (unnamed_idx_0) {
    tmp_data[0] = 1;
    partialTrueCount = 1;
  }

  if (unnamed_idx_1) {
    tmp_data[partialTrueCount] = 2;
    partialTrueCount++;
  }

  if (unnamed_idx_2) {
    tmp_data[partialTrueCount] = 3;
  }

  for (partialTrueCount = 0; partialTrueCount < trueCount; partialTrueCount++) {
    fillA[tmp_data[partialTrueCount] - 1] = 0.0;
  }

  scale = 3.3121686421112381E-170;
  absxk = fabs(fillA[0]);
  if (absxk > 3.3121686421112381E-170) {
    b = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    b = t * t;
  }

  absxk = fabs(fillA[1]);
  if (absxk > scale) {
    t = scale / absxk;
    b = b * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    b += t * t;
  }

  absxk = fabs(fillA[2]);
  if (absxk > scale) {
    t = scale / absxk;
    b = b * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    b += t * t;
  }

  b = scale * sqrt(b);
  n[0] = a[0] / b;
  n[1] = a[1] / b;
  n[2] = a[2] / b;
}

//
// File trailer for normalize.cpp
//
// [EOF]
//
