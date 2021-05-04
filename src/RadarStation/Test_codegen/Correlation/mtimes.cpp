/*
 * mtimes.cpp
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include "mtimes.h"
#include "Correlation.h"
#include "blas.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
real_T mtimes(const real_T A[801], const real_T B[801])
{
  real_T y[801];
  ptrdiff_t n_t;
  ptrdiff_t incx_t;
  ptrdiff_t incy_t;
  memcpy(&y[0], &B[0], 801U * sizeof(real_T));
  n_t = (ptrdiff_t)801;
  incx_t = (ptrdiff_t)1;
  incy_t = (ptrdiff_t)1;
  return ddot(&n_t, (real_T *)&A[0], &incx_t, &y[0], &incy_t);
}

/* End of code generation (mtimes.cpp) */
