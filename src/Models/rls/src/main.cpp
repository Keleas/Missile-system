//
// File: main.cpp
//
// MATLAB Coder version            : 4.3
// C/C++ source code generated on  : 22-May-2021 19:13:59
//

//***********************************************************************
// This automatically generated example C++ main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************

// Include Files
#include "main.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_emxAPI.h"
#include "MFR_V2_Cycle_terminate.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"

// Function Declarations
static void argInit_1x3_real_T(double result[3]);
static void argInit_3x3_real_T(double result[9]);
static emxArray_real_T *argInit_Unboundedx1_real_T();
static emxArray_real_T *argInit_Unboundedx3_real_T();
static double argInit_real_T();
static struct0_T argInit_struct0_T();
static void argInit_struct1_T(struct1_T *result);
static emxArray_real_T *c_argInit_UnboundedxUnbounded_r();
static void main_MFR_V2_Cycle();
static void main_MFR_V2_GenerateMFRType();
static void main_MFR_V2_GenerateTrajectoryType();

// Function Definitions

//
// Arguments    : double result[3]
// Return Type  : void
//
static void argInit_1x3_real_T(double result[3])
{
  double result_tmp_tmp;

  // Loop over the array to initialize each element.
  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result_tmp_tmp = argInit_real_T();
  result[0] = result_tmp_tmp;

  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result[1] = result_tmp_tmp;

  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result[2] = result_tmp_tmp;
}

//
// Arguments    : double result[9]
// Return Type  : void
//
static void argInit_3x3_real_T(double result[9])
{
  int idx0;
  double result_tmp_tmp;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 3; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_tmp_tmp = argInit_real_T();
    result[idx0] = result_tmp_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 3] = result_tmp_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 6] = result_tmp_tmp;
  }
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_Unboundedx1_real_T()
{
  emxArray_real_T *result;
  static const int iv[1] = { 2 };

  int idx0;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreateND_real_T(1, iv);

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[idx0] = argInit_real_T();
  }

  return result;
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *argInit_Unboundedx3_real_T()
{
  emxArray_real_T *result;
  int idx0;
  double result_tmp_tmp;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreate_real_T(2, 3);

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_tmp_tmp = argInit_real_T();
    result->data[idx0] = result_tmp_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[idx0 + result->size[0]] = result_tmp_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result->data[idx0 + result->size[0] * 2] = result_tmp_tmp;
  }

  return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : void
// Return Type  : struct0_T
//
static struct0_T argInit_struct0_T()
{
  struct0_T result;

  // Set the value of each structure field.
  // Change this value to the value that the application requires.
  result.ID = argInit_Unboundedx1_real_T();
  result.R0 = argInit_Unboundedx3_real_T();
  result.V = argInit_Unboundedx3_real_T();
  result.RCS = argInit_Unboundedx1_real_T();
  return result;
}

//
// Arguments    : struct1_T *result
// Return Type  : void
//
static void argInit_struct1_T(struct1_T *result)
{
  double result_tmp_tmp_tmp_tmp;
  double result_tmp_tmp[3];

  // Set the value of each structure field.
  // Change this value to the value that the application requires.
  result_tmp_tmp_tmp_tmp = argInit_real_T();
  result->lambda = result_tmp_tmp_tmp_tmp;
  result->Dmax = result_tmp_tmp_tmp_tmp;
  result->Dmin = result_tmp_tmp_tmp_tmp;
  result->Tscan = result_tmp_tmp_tmp_tmp;
  result->Timp = result_tmp_tmp_tmp_tmp;
  result->V_res = argInit_real_T();
  result->asim_res = argInit_real_T();
  result->elev_res = argInit_real_T();
  result->asim_res_trace_cf = argInit_real_T();
  result->elev_res_trace_cf = argInit_real_T();
  result->elev1 = argInit_real_T();
  result->elev2 = argInit_real_T();
  result->Nasim = argInit_real_T();
  result->Nelev = argInit_real_T();
  result->Bandwidth = argInit_real_T();
  result->Noise = argInit_real_T();
  result->Gain = argInit_real_T();
  result->P_peak = argInit_real_T();
  result->Tr = argInit_real_T();
  result->Ntraj = argInit_real_T();
  result->Nmissiles = argInit_real_T();
  argInit_1x3_real_T(result_tmp_tmp);
  result->n[0] = result_tmp_tmp[0];
  result->e[0] = result_tmp_tmp[0];
  result->p[0] = result_tmp_tmp[0];
  result->n[1] = result_tmp_tmp[1];
  result->e[1] = result_tmp_tmp[1];
  result->p[1] = result_tmp_tmp[1];
  result->n[2] = result_tmp_tmp[2];
  result->e[2] = result_tmp_tmp[2];
  result->p[2] = result_tmp_tmp[2];
  argInit_1x3_real_T(result->Loc);
  argInit_3x3_real_T(result->A);
  result->elev = c_argInit_UnboundedxUnbounded_r();
  result->asim = c_argInit_UnboundedxUnbounded_r();
  result->ed = c_argInit_UnboundedxUnbounded_r();
  result->ee = c_argInit_UnboundedxUnbounded_r();
  result->ea = c_argInit_UnboundedxUnbounded_r();
  result->tsc = argInit_real_T();
  result->pos = argInit_real_T();
  result->posN = argInit_real_T();
  result->tge = argInit_real_T();
  result->tga = argInit_real_T();
  result->Pc = argInit_real_T();
  result->tgID = c_argInit_UnboundedxUnbounded_r();
  result->tgIDprev = c_argInit_UnboundedxUnbounded_r();
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *c_argInit_UnboundedxUnbounded_r()
{
  emxArray_real_T *result;
  int idx0;
  int idx1;

  // Set the size of the array.
  // Change this size to the value that the application requires.
  result = emxCreate_real_T(2, 2);

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
    for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result->data[idx0 + result->size[0] * idx1] = argInit_real_T();
    }
  }

  return result;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_MFR_V2_Cycle()
{
  struct2_T MSG;
  struct0_T TG;
  struct1_T MFR;
  emxInit_struct2_T(&MSG);

  // Initialize function 'MFR_V2_Cycle' input arguments.
  // Initialize function input argument 'TG'.
  TG = argInit_struct0_T();

  // Initialize function input argument 'MFR'.
  argInit_struct1_T(&MFR);

  // Call the entry-point 'MFR_V2_Cycle'.
  MFR_V2_Cycle(TG, &MFR, argInit_real_T(), &MSG);
  emxDestroy_struct2_T(MSG);
  emxDestroy_struct1_T(MFR);
  emxDestroy_struct0_T(TG);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_MFR_V2_GenerateMFRType()
{
  struct1_T MFR;
  double Loc_tmp[3];
  double n[3];
  double lambda_tmp_tmp_tmp;
  emxInit_struct1_T(&MFR);

  // Initialize function 'MFR_V2_GenerateMFRType' input arguments.
  // Initialize function input argument 'Loc'.
  argInit_1x3_real_T(Loc_tmp);

  // Initialize function input argument 'n'.
  n[0] = Loc_tmp[0];
  n[1] = Loc_tmp[1];
  n[2] = Loc_tmp[2];
  lambda_tmp_tmp_tmp = argInit_real_T();

  // Call the entry-point 'MFR_V2_GenerateMFRType'.
  MFR_V2_GenerateMFRType(Loc_tmp, n, lambda_tmp_tmp_tmp, lambda_tmp_tmp_tmp,
    lambda_tmp_tmp_tmp, lambda_tmp_tmp_tmp, argInit_real_T(), argInit_real_T(),
    argInit_real_T(), argInit_real_T(), argInit_real_T(), argInit_real_T(),
    argInit_real_T(), argInit_real_T(), argInit_real_T(), argInit_real_T(),
    argInit_real_T(), argInit_real_T(), argInit_real_T(), argInit_real_T(),
    argInit_real_T(), argInit_real_T(), argInit_real_T(), &MFR);
  emxDestroy_struct1_T(MFR);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_MFR_V2_GenerateTrajectoryType()
{
  struct0_T TG;
  emxArray_real_T *TG_ID;
  emxArray_real_T *TG_R0X;
  emxArray_real_T *TG_R0Y;
  emxArray_real_T *TG_R0Z;
  emxArray_real_T *TG_VX;
  emxArray_real_T *TG_VY;
  emxArray_real_T *TG_VZ;
  emxArray_real_T *TG_Type;
  emxInit_struct0_T(&TG);

  // Initialize function 'MFR_V2_GenerateTrajectoryType' input arguments.
  // Initialize function input argument 'TG_ID'.
  TG_ID = argInit_Unboundedx1_real_T();

  // Initialize function input argument 'TG_R0X'.
  TG_R0X = argInit_Unboundedx1_real_T();

  // Initialize function input argument 'TG_R0Y'.
  TG_R0Y = argInit_Unboundedx1_real_T();

  // Initialize function input argument 'TG_R0Z'.
  TG_R0Z = argInit_Unboundedx1_real_T();

  // Initialize function input argument 'TG_VX'.
  TG_VX = argInit_Unboundedx1_real_T();

  // Initialize function input argument 'TG_VY'.
  TG_VY = argInit_Unboundedx1_real_T();

  // Initialize function input argument 'TG_VZ'.
  TG_VZ = argInit_Unboundedx1_real_T();

  // Initialize function input argument 'TG_Type'.
  TG_Type = argInit_Unboundedx1_real_T();

  // Call the entry-point 'MFR_V2_GenerateTrajectoryType'.
  MFR_V2_GenerateTrajectoryType(TG_ID, TG_R0X, TG_R0Y, TG_R0Z, TG_VX, TG_VY,
    TG_VZ, TG_Type, &TG);
  emxDestroy_struct0_T(TG);
  emxDestroyArray_real_T(TG_Type);
  emxDestroyArray_real_T(TG_VZ);
  emxDestroyArray_real_T(TG_VY);
  emxDestroyArray_real_T(TG_VX);
  emxDestroyArray_real_T(TG_R0Z);
  emxDestroyArray_real_T(TG_R0Y);
  emxDestroyArray_real_T(TG_R0X);
  emxDestroyArray_real_T(TG_ID);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. 
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_MFR_V2_GenerateTrajectoryType();
  main_MFR_V2_GenerateMFRType();
  main_MFR_V2_Cycle();

  // Terminate the application.
  // You do not need to do this more than one time.
  MFR_V2_Cycle_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
