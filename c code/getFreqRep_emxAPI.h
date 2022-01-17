/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: getFreqRep_emxAPI.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 14-Jan-2022 12:29:41
 */

#ifndef GETFREQREP_EMXAPI_H
#define GETFREQREP_EMXAPI_H

/* Include Files */
#include "getFreqRep_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern emxArray_creal_T *emxCreateND_creal_T(int numDimensions,
                                             const int *size);

extern emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size);

extern emxArray_creal_T *
emxCreateWrapperND_creal_T(creal_T *data, int numDimensions, const int *size);

extern emxArray_real_T *
emxCreateWrapperND_real_T(double *data, int numDimensions, const int *size);

extern emxArray_creal_T *emxCreateWrapper_creal_T(creal_T *data, int rows,
                                                  int cols);

extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows,
                                                int cols);

extern emxArray_creal_T *emxCreate_creal_T(int rows, int cols);

extern emxArray_real_T *emxCreate_real_T(int rows, int cols);

extern void emxDestroyArray_creal_T(emxArray_creal_T *emxArray);

extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

extern void emxInitArray_creal_T(emxArray_creal_T **pEmxArray,
                                 int numDimensions);

extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for getFreqRep_emxAPI.h
 *
 * [EOF]
 */
