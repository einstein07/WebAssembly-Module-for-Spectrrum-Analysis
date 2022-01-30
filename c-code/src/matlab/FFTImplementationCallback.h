/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFTImplementationCallback.h
 *
 * Code generation for function 'FFTImplementationCallback'
 *
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_FFTImplementationCallback_doH(const double x_data[], int x_size,
                                     creal_T y_data[], const int *y_size,
                                     int unsigned_nRows,
                                     const double costab_data[],
                                     const int costab_size[2],
                                     const double sintab_data[]);

void c_FFTImplementationCallback_dob(const double x_data[], int x_size,
                                     int n2blue, int nfft,
                                     const double costab_data[],
                                     const int costab_size[2],
                                     const double sintab_data[],
                                     const double sintabinv_data[],
                                     creal_T y_data[], int *y_size);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (FFTImplementationCallback.h) */
