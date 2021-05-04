/*
 * xcorr.h
 *
 * Code generation for function 'xcorr'
 *
 */

#pragma once

/* Include files */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mex.h"
#include "emlrt.h"
#include "rtwtypes.h"
#include "Correlation_types.h"

/* Function Declarations */
void b_xcorr(const creal_T x[801], const real_T varargin_1[801], creal_T c[1601]);
void xcorr(const creal_T x[801], const real_T varargin_1[801], creal_T c[1601],
           real_T lags[1601]);

/* End of code generation (xcorr.h) */
