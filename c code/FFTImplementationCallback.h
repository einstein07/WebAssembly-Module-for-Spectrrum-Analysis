/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTImplementationCallback.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 14-Jan-2022 12:29:41
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include Files */
#include "getFreqRep_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y);

void c_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv);

void c_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for FFTImplementationCallback.h
 *
 * [EOF]
 */
