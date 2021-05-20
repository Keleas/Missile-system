//
// File: MFR_V2_GenerateMFRType.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//
#ifndef MFR_V2_GENERATEMFRTYPE_H
#define MFR_V2_GENERATEMFRTYPE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "MFR_V2_Cycle_types.h"

// Function Declarations
extern void MFR_V2_GenerateMFRType(const double Loc[3], double n[3], double
  lambda, double Dmax, double Dmin, double Tscan, double Timp, double V_res,
  double asim_res, double elev_res, double asim_res_trace_cf, double
  elev_res_trace_cf, double elev1, double elev2, double Nasim, double Nelev,
  double Bandwidth, double Noise, double Gain, double P_peak, double Tr, double
  Ntraj, double Nmissiles, struct0_T *MFR);

#endif

//
// File trailer for MFR_V2_GenerateMFRType.h
//
// [EOF]
//
