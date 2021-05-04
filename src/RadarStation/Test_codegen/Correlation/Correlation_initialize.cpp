/*
 * Correlation_initialize.cpp
 *
 * Code generation for function 'Correlation_initialize'
 *
 */

/* Include files */
#include "Correlation_initialize.h"
#include "Correlation.h"
#include "Correlation_data.h"
#include "_coder_Correlation_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void Correlation_initialize()
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mex_InitInfAndNan();
  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/* End of code generation (Correlation_initialize.cpp) */
