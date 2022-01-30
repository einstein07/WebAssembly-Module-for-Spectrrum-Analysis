/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fft.c
 *
 * Code generation for function 'fft'
 *
 */

/* Include files */
#include "fft.h"
#include "FFTImplementationCallback.h"
#include <math.h>

/* Function Definitions */
void fft(const short x[100000], creal_T y[100000])
{
  static double costab[131073];
  static double sintab[131073];
  static double sintabinv[131073];
  static double b_x[100000];
  static double costab1q[65537];
  double b_sintabinv_tmp;
  double sintabinv_tmp;
  int k;
  costab1q[0] = 1.0;
  for (k = 0; k < 32768; k++) {
    costab1q[k + 1] = cos(2.3968449810713143E-5 * ((double)k + 1.0));
  }
  for (k = 0; k < 32767; k++) {
    costab1q[k + 32769] =
        sin(2.3968449810713143E-5 * (65536.0 - ((double)k + 32769.0)));
  }
  costab1q[65536] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 65536; k++) {
    sintabinv_tmp = costab1q[65535 - k];
    sintabinv[k + 1] = sintabinv_tmp;
    b_sintabinv_tmp = costab1q[k + 1];
    sintabinv[k + 65537] = b_sintabinv_tmp;
    costab[k + 1] = b_sintabinv_tmp;
    sintab[k + 1] = -sintabinv_tmp;
    costab[k + 65537] = -sintabinv_tmp;
    sintab[k + 65537] = -b_sintabinv_tmp;
  }
  for (k = 0; k < 100000; k++) {
    b_x[k] = x[k];
  }
  c_FFTImplementationCallback_dob(b_x, costab, sintab, sintabinv, y);
}

/* End of code generation (fft.c) */
