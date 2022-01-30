/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * getFreqRep.c
 *
 * Code generation for function 'getFreqRep'
 *
 */

/* Include files */
#include "getFreqRep.h"
#include "fft.h"
#include <string.h>

/* Function Definitions */
void getFreqRep(const short x[100000], creal_T y[100000],
                creal_T y_shifted[100000])
{
  double xtmp_im;
  double xtmp_re;
  int a;
  int dim;
  int i;
  int i1;
  int i2;
  int ib;
  int k;
  int npages;
  int vlend2;
  int xtmp_re_tmp;
  int y_shifted_tmp;
  /* codegen */
  /* GETFREQREP Computes the fft of a given signal. */
  /*    [Y] = GETFREQREP(X) computes the fast fourier transform of a real  */
  /*    signal. X is an M-by-1 vector. Y is an M-by-1 vector that contains the
   */
  /*    results of the fft operation on X. */
  fft(x, y);
  memcpy(&y_shifted[0], &y[0], 100000U * sizeof(creal_T));
  for (dim = 0; dim < 2; dim++) {
    a = 99999 * dim + 1;
    if (a > 1) {
      vlend2 = a / 2;
      npages = 1;
      i2 = dim + 2;
      for (k = i2; k < 3; k++) {
        npages *= 100000;
      }
      if (vlend2 << 1 == a) {
        i2 = 0;
        for (i = 0; i < npages; i++) {
          i1 = i2;
          i2 = (i2 + a) - 1;
          i1++;
          i2++;
          ib = (i1 + vlend2) - 1;
          for (k = 0; k < vlend2; k++) {
            xtmp_re_tmp = (i1 + k) - 1;
            xtmp_re = y_shifted[xtmp_re_tmp].re;
            xtmp_im = y_shifted[xtmp_re_tmp].im;
            y_shifted_tmp = ib + k;
            y_shifted[xtmp_re_tmp] = y_shifted[y_shifted_tmp];
            y_shifted[y_shifted_tmp].re = xtmp_re;
            y_shifted[ib + k].im = xtmp_im;
          }
        }
      } else {
        i2 = 0;
        for (i = 0; i < npages; i++) {
          i1 = i2;
          i2 = (i2 + a) - 1;
          i1++;
          i2++;
          ib = (i1 + vlend2) - 1;
          xtmp_re = y_shifted[ib].re;
          xtmp_im = y_shifted[ib].im;
          for (k = 0; k < vlend2; k++) {
            y_shifted_tmp = (i1 + k) - 1;
            y_shifted[ib] = y_shifted[y_shifted_tmp];
            y_shifted[y_shifted_tmp] = y_shifted[ib + 1];
            ib++;
          }
          y_shifted[ib].re = xtmp_re;
          y_shifted[ib].im = xtmp_im;
        }
      }
    }
  }
}

/* End of code generation (getFreqRep.c) */
