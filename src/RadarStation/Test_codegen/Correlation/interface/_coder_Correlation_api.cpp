/*
 * _coder_Correlation_api.cpp
 *
 * Code generation for function '_coder_Correlation_api'
 *
 */

/* Include files */
#include "_coder_Correlation_api.h"
#include "Correlation.h"
#include "Correlation_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void Correlation_api(CorrelationStackData *SD, int32_T)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Invoke the target function */
  Correlation(SD, &st);
}

/* End of code generation (_coder_Correlation_api.cpp) */
