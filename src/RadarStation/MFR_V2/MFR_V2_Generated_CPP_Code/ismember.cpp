//
// File: ismember.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//

// Include Files
#include "ismember.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_emxutil.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "issorted.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include <math.h>

// Function Declarations
static int b_bsearchni(int k, const emxArray_real_T *x, const emxArray_real_T *s);
static int bsearchni(int k, const emxArray_real_T *x, const emxArray_real_T *s);

// Function Definitions

//
// Arguments    : int k
//                const emxArray_real_T *x
//                const emxArray_real_T *s
// Return Type  : int
//
static int b_bsearchni(int k, const emxArray_real_T *x, const emxArray_real_T *s)
{
  int idx;
  double b_x;
  int ihi;
  int ilo;
  boolean_T exitg1;
  int imid;
  boolean_T p;
  b_x = x->data[k - 1];
  ihi = s->size[0] * s->size[1];
  idx = 0;
  ilo = 1;
  exitg1 = false;
  while ((!exitg1) && (ihi >= ilo)) {
    imid = ((ilo >> 1) + (ihi >> 1)) - 1;
    if (((ilo & 1) == 1) && ((ihi & 1) == 1)) {
      imid++;
    }

    if (b_x == s->data[imid]) {
      idx = imid + 1;
      exitg1 = true;
    } else {
      if (rtIsNaN(s->data[imid])) {
        p = !rtIsNaN(b_x);
      } else {
        p = ((!rtIsNaN(b_x)) && (b_x < s->data[imid]));
      }

      if (p) {
        ihi = imid;
      } else {
        ilo = imid + 2;
      }
    }
  }

  if (idx > 0) {
    idx--;
    while ((idx > 0) && (b_x == s->data[idx - 1])) {
      idx--;
    }

    idx++;
  }

  return idx;
}

//
// Arguments    : int k
//                const emxArray_real_T *x
//                const emxArray_real_T *s
// Return Type  : int
//
static int bsearchni(int k, const emxArray_real_T *x, const emxArray_real_T *s)
{
  int idx;
  double b_x;
  int ihi;
  int ilo;
  boolean_T exitg1;
  int imid;
  boolean_T p;
  b_x = x->data[k - 1];
  ihi = s->size[0];
  idx = 0;
  ilo = 1;
  exitg1 = false;
  while ((!exitg1) && (ihi >= ilo)) {
    imid = ((ilo >> 1) + (ihi >> 1)) - 1;
    if (((ilo & 1) == 1) && ((ihi & 1) == 1)) {
      imid++;
    }

    if (b_x == s->data[imid]) {
      idx = imid + 1;
      exitg1 = true;
    } else {
      if (rtIsNaN(s->data[imid])) {
        p = !rtIsNaN(b_x);
      } else {
        p = ((!rtIsNaN(b_x)) && (b_x < s->data[imid]));
      }

      if (p) {
        ihi = imid;
      } else {
        ilo = imid + 2;
      }
    }
  }

  if (idx > 0) {
    idx--;
    while ((idx > 0) && (b_x == s->data[idx - 1])) {
      idx--;
    }

    idx++;
  }

  return idx;
}

//
// Arguments    : const emxArray_real_T *a
//                const emxArray_real_T *s
//                emxArray_boolean_T *tf
//                emxArray_int32_T *loc
// Return Type  : void
//
void b_local_ismember(const emxArray_real_T *a, const emxArray_real_T *s,
                      emxArray_boolean_T *tf, emxArray_int32_T *loc)
{
  int na;
  int ns;
  int pmax;
  int pmin;
  emxArray_real_T *ss;
  emxArray_int32_T *ssidx;
  boolean_T guard1 = false;
  boolean_T exitg1;
  int p;
  int pow2p;
  emxArray_real_T b_s;
  int c_s[1];
  double absx;
  int exponent;
  int k;
  int n;
  na = a->size[0];
  ns = s->size[0] * s->size[1];
  pmax = tf->size[0];
  tf->size[0] = a->size[0];
  emxEnsureCapacity_boolean_T(tf, pmax);
  pmin = a->size[0];
  for (pmax = 0; pmax < pmin; pmax++) {
    tf->data[pmax] = false;
  }

  pmax = loc->size[0];
  loc->size[0] = a->size[0];
  emxEnsureCapacity_int32_T(loc, pmax);
  pmin = a->size[0];
  for (pmax = 0; pmax < pmin; pmax++) {
    loc->data[pmax] = 0;
  }

  emxInit_real_T(&ss, 1);
  emxInit_int32_T(&ssidx, 1);
  guard1 = false;
  if (ns <= 4) {
    guard1 = true;
  } else {
    pmax = 31;
    pmin = 0;
    exitg1 = false;
    while ((!exitg1) && (pmax - pmin > 1)) {
      p = (pmin + pmax) >> 1;
      pow2p = 1 << p;
      if (pow2p == ns) {
        pmax = p;
        exitg1 = true;
      } else if (pow2p > ns) {
        pmax = p;
      } else {
        pmin = p;
      }
    }

    if (a->size[0] <= pmax + 4) {
      guard1 = true;
    } else {
      pmax = s->size[0] * s->size[1];
      b_s = *s;
      c_s[0] = pmax;
      b_s.size = &c_s[0];
      b_s.numDimensions = 1;
      if (!issorted(&b_s)) {
        pmax = ss->size[0];
        ss->size[0] = s->size[0] * s->size[1];
        emxEnsureCapacity_real_T(ss, pmax);
        pmin = s->size[0] * s->size[1];
        for (pmax = 0; pmax < pmin; pmax++) {
          ss->data[pmax] = s->data[pmax];
        }

        sort(ss, ssidx);
        pmax = a->size[0] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(n)

        for (k = 0; k <= pmax; k++) {
          n = bsearchni(k + 1, a, ss);
          if (n > 0) {
            tf->data[k] = true;
            loc->data[k] = ssidx->data[n - 1];
          }
        }
      } else {
        pmax = a->size[0] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(n)

        for (k = 0; k <= pmax; k++) {
          n = b_bsearchni(k + 1, a, s);
          if (n > 0) {
            tf->data[k] = true;
            loc->data[k] = n;
          }
        }
      }
    }
  }

  if (guard1) {
    for (pmax = 0; pmax < na; pmax++) {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmin <= ns - 1)) {
        absx = fabs(s->data[pmin] / 2.0);
        if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
          if (absx <= 2.2250738585072014E-308) {
            absx = 4.94065645841247E-324;
          } else {
            frexp(absx, &exponent);
            absx = ldexp(1.0, exponent - 53);
          }
        } else {
          absx = rtNaN;
        }

        if ((fabs(s->data[pmin] - a->data[pmax]) < absx) || (rtIsInf(a->
              data[pmax]) && rtIsInf(s->data[pmin]) && ((a->data[pmax] > 0.0) ==
              (s->data[pmin] > 0.0)))) {
          tf->data[pmax] = true;
          loc->data[pmax] = pmin + 1;
          exitg1 = true;
        } else {
          pmin++;
        }
      }
    }
  }

  emxFree_int32_T(&ssidx);
  emxFree_real_T(&ss);
}

//
// Arguments    : const emxArray_real_T *a
//                const emxArray_real_T *s
//                emxArray_boolean_T *tf
// Return Type  : void
//
void c_local_ismember(const emxArray_real_T *a, const emxArray_real_T *s,
                      emxArray_boolean_T *tf)
{
  int na;
  int ns;
  int pmax;
  int pmin;
  emxArray_real_T *ss;
  emxArray_int32_T *b_ss;
  boolean_T guard1 = false;
  boolean_T exitg1;
  int p;
  int pow2p;
  emxArray_real_T b_s;
  int c_s[1];
  double absx;
  int exponent;
  int k;
  int n;
  na = a->size[0];
  ns = s->size[0] * s->size[1];
  pmax = tf->size[0];
  tf->size[0] = a->size[0];
  emxEnsureCapacity_boolean_T(tf, pmax);
  pmin = a->size[0];
  for (pmax = 0; pmax < pmin; pmax++) {
    tf->data[pmax] = false;
  }

  emxInit_real_T(&ss, 1);
  emxInit_int32_T(&b_ss, 1);
  guard1 = false;
  if (ns <= 4) {
    guard1 = true;
  } else {
    pmax = 31;
    pmin = 0;
    exitg1 = false;
    while ((!exitg1) && (pmax - pmin > 1)) {
      p = (pmin + pmax) >> 1;
      pow2p = 1 << p;
      if (pow2p == ns) {
        pmax = p;
        exitg1 = true;
      } else if (pow2p > ns) {
        pmax = p;
      } else {
        pmin = p;
      }
    }

    if (a->size[0] <= pmax + 4) {
      guard1 = true;
    } else {
      pmax = s->size[0] * s->size[1];
      b_s = *s;
      c_s[0] = pmax;
      b_s.size = &c_s[0];
      b_s.numDimensions = 1;
      if (!issorted(&b_s)) {
        pmax = ss->size[0];
        ss->size[0] = s->size[0] * s->size[1];
        emxEnsureCapacity_real_T(ss, pmax);
        pmin = s->size[0] * s->size[1];
        for (pmax = 0; pmax < pmin; pmax++) {
          ss->data[pmax] = s->data[pmax];
        }

        sort(ss, b_ss);
        pmax = a->size[0] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(n)

        for (k = 0; k <= pmax; k++) {
          n = bsearchni(k + 1, a, ss);
          if (n > 0) {
            tf->data[k] = true;
          }
        }
      } else {
        pmax = a->size[0] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(n)

        for (k = 0; k <= pmax; k++) {
          n = b_bsearchni(k + 1, a, s);
          if (n > 0) {
            tf->data[k] = true;
          }
        }
      }
    }
  }

  if (guard1) {
    for (pmax = 0; pmax < na; pmax++) {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmin <= ns - 1)) {
        absx = fabs(s->data[pmin] / 2.0);
        if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
          if (absx <= 2.2250738585072014E-308) {
            absx = 4.94065645841247E-324;
          } else {
            frexp(absx, &exponent);
            absx = ldexp(1.0, exponent - 53);
          }
        } else {
          absx = rtNaN;
        }

        if ((fabs(s->data[pmin] - a->data[pmax]) < absx) || (rtIsInf(a->
              data[pmax]) && rtIsInf(s->data[pmin]) && ((a->data[pmax] > 0.0) ==
              (s->data[pmin] > 0.0)))) {
          tf->data[pmax] = true;
          exitg1 = true;
        } else {
          pmin++;
        }
      }
    }
  }

  emxFree_int32_T(&b_ss);
  emxFree_real_T(&ss);
}

//
// Arguments    : const emxArray_real_T *a
//                const emxArray_real_T *s
//                emxArray_boolean_T *tf
//                emxArray_int32_T *loc
// Return Type  : void
//
void local_ismember(const emxArray_real_T *a, const emxArray_real_T *s,
                    emxArray_boolean_T *tf, emxArray_int32_T *loc)
{
  int na;
  int ns;
  int pmax;
  int pmin;
  emxArray_real_T *ss;
  emxArray_int32_T *ssidx;
  boolean_T guard1 = false;
  boolean_T exitg1;
  int p;
  int pow2p;
  int k;
  double absx;
  int exponent;
  int n;
  na = a->size[0];
  ns = s->size[0];
  pmax = tf->size[0];
  tf->size[0] = a->size[0];
  emxEnsureCapacity_boolean_T(tf, pmax);
  pmin = a->size[0];
  for (pmax = 0; pmax < pmin; pmax++) {
    tf->data[pmax] = false;
  }

  pmax = loc->size[0];
  loc->size[0] = a->size[0];
  emxEnsureCapacity_int32_T(loc, pmax);
  pmin = a->size[0];
  for (pmax = 0; pmax < pmin; pmax++) {
    loc->data[pmax] = 0;
  }

  emxInit_real_T(&ss, 1);
  emxInit_int32_T(&ssidx, 1);
  guard1 = false;
  if (s->size[0] <= 4) {
    guard1 = true;
  } else {
    pmax = 31;
    pmin = 0;
    exitg1 = false;
    while ((!exitg1) && (pmax - pmin > 1)) {
      p = (pmin + pmax) >> 1;
      pow2p = 1 << p;
      if (pow2p == ns) {
        pmax = p;
        exitg1 = true;
      } else if (pow2p > ns) {
        pmax = p;
      } else {
        pmin = p;
      }
    }

    if (a->size[0] <= pmax + 4) {
      guard1 = true;
    } else if (!issorted(s)) {
      pmax = ss->size[0];
      ss->size[0] = s->size[0];
      emxEnsureCapacity_real_T(ss, pmax);
      pmin = s->size[0];
      for (pmax = 0; pmax < pmin; pmax++) {
        ss->data[pmax] = s->data[pmax];
      }

      sort(ss, ssidx);
      pmax = a->size[0] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(n)

      for (k = 0; k <= pmax; k++) {
        n = bsearchni(k + 1, a, ss);
        if (n > 0) {
          tf->data[k] = true;
          loc->data[k] = ssidx->data[n - 1];
        }
      }
    } else {
      pmax = a->size[0] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(n)

      for (k = 0; k <= pmax; k++) {
        n = bsearchni(k + 1, a, s);
        if (n > 0) {
          tf->data[k] = true;
          loc->data[k] = n;
        }
      }
    }
  }

  if (guard1) {
    for (pmax = 0; pmax < na; pmax++) {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmin <= ns - 1)) {
        absx = fabs(s->data[pmin] / 2.0);
        if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
          if (absx <= 2.2250738585072014E-308) {
            absx = 4.94065645841247E-324;
          } else {
            frexp(absx, &exponent);
            absx = ldexp(1.0, exponent - 53);
          }
        } else {
          absx = rtNaN;
        }

        if ((fabs(s->data[pmin] - a->data[pmax]) < absx) || (rtIsInf(a->
              data[pmax]) && rtIsInf(s->data[pmin]) && ((a->data[pmax] > 0.0) ==
              (s->data[pmin] > 0.0)))) {
          tf->data[pmax] = true;
          loc->data[pmax] = pmin + 1;
          exitg1 = true;
        } else {
          pmin++;
        }
      }
    }
  }

  emxFree_int32_T(&ssidx);
  emxFree_real_T(&ss);
}

//
// File trailer for ismember.cpp
//
// [EOF]
//
