//
// File: MFR_V2_Cycle_types.h
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 20-May-2021 18:03:49
//
#ifndef MFR_V2_CYCLE_TYPES_H
#define MFR_V2_CYCLE_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct struct0_T
{
  double lambda;
  double Dmax;
  double Dmin;
  double Tscan;
  double Timp;
  double V_res;
  double asim_res;
  double elev_res;
  double asim_res_trace_cf;
  double elev_res_trace_cf;
  double elev1;
  double elev2;
  double Nasim;
  double Nelev;
  double Bandwidth;
  double Noise;
  double Gain;
  double P_peak;
  double Tr;
  double Ntraj;
  double Nmissiles;
  double n[3];
  double e[3];
  double p[3];
  double Loc[3];
  double A[9];
  emxArray_real_T *elev;
  emxArray_real_T *asim;
  emxArray_real_T *ed;
  emxArray_real_T *ee;
  emxArray_real_T *ea;
  double tsc;
  double pos;
  double posN;
  double tge;
  double tga;
  double Pc;
  emxArray_real_T *tgID;
  emxArray_real_T *tgIDprev;
};

struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

struct struct1_T
{
  emxArray_real_T *ID;
  emxArray_real_T *R0;
  emxArray_real_T *V;
  emxArray_real_T *RCS;
};

struct struct2_T
{
  emxArray_real_T *IDLost;
  emxArray_real_T *IDNew;
  emxArray_real_T *IDTracked;
  emxArray_real_T *RTrackedX;
  emxArray_real_T *RTrackedY;
  emxArray_real_T *RTrackedZ;
  emxArray_real_T *VTrackedX;
  emxArray_real_T *VTrackedY;
  emxArray_real_T *VTrackedZ;
};

#endif

//
// File trailer for MFR_V2_Cycle_types.h
//
// [EOF]
//
