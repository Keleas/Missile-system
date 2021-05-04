/*
 * Correlation_terminate.cpp
 *
 * Code generation for function 'Correlation_terminate'
 *
 */

/* Include files */
#include "Correlation_terminate.h"
#include "Correlation.h"
#include "Correlation_data.h"
#include "_coder_Correlation_mex.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void Correlation_atexit()
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void Correlation_terminate()
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (Correlation_terminate.cpp) */
