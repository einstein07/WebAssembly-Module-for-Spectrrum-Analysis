/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: getFreqRep.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 14-Jan-2022 12:29:41
 */

/* Include Files */
#include "getFreqRep.h"
#include "fft.h"
#include "getFreqRep_emxutil.h"
#include "getFreqRep_types.h"

/* Function Definitions */
/*
 * codegen
 * GETFREQREP Computes the fft of a given signal.
 *    [Y] = GETFREQREP(X) computes the fast fourier transform of a real
 *    signal. X is an M-by-1 vector. Y is an M-by-1 vector that contains the
 *    results of the fft operation on X.
 *
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 *                emxArray_creal_T *y_shifted
 * Return Type  : void
 */
void getFreqRep(const emxArray_real_T *x, emxArray_creal_T *y,
                emxArray_creal_T *y_shifted)
{
  creal_T *y_data;
  creal_T *y_shifted_data;
  double xtmp_im;
  double xtmp_re;
  int a;
  int dim;
  int i1;
  int ib;
  int ic;
  int j;
  int k;
  int midoffset;
  int vlend2;
  int vstride;
  fft(x, y);
  y_data = y->data;
  a = y_shifted->size[0];
  y_shifted->size[0] = y->size[0];
  emxEnsureCapacity_creal_T(y_shifted, a);
  y_shifted_data = y_shifted->data;
  ic = y->size[0];
  for (a = 0; a < ic; a++) {
    y_shifted_data[a] = y_data[a];
  }
  for (dim = 0; dim < 2; dim++) {
    ic = dim - 1;
    if (dim + 1 <= 1) {
      a = y_shifted->size[0];
    } else {
      a = 1;
    }
    if (a > 1) {
      vlend2 = a / 2;
      vstride = 1;
      for (k = 0; k <= ic; k++) {
        vstride *= y_shifted->size[0];
      }
      midoffset = vlend2 * vstride - 1;
      if (vlend2 << 1 == a) {
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          i1++;
          ib = i1 + midoffset;
          for (k = 0; k < vlend2; k++) {
            a = k * vstride;
            ic = (i1 + a) - 1;
            xtmp_re = y_shifted_data[ic].re;
            xtmp_im = y_shifted_data[ic].im;
            a += ib;
            y_shifted_data[ic] = y_shifted_data[a];
            y_shifted_data[a].re = xtmp_re;
            y_shifted_data[a].im = xtmp_im;
          }
        }
      } else {
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          i1++;
          ib = i1 + midoffset;
          xtmp_re = y_shifted_data[ib].re;
          xtmp_im = y_shifted_data[ib].im;
          for (k = 0; k < vlend2; k++) {
            ic = ib + vstride;
            a = (i1 + k * vstride) - 1;
            y_shifted_data[ib] = y_shifted_data[a];
            y_shifted_data[a] = y_shifted_data[ic];
            ib = ic;
          }
          y_shifted_data[ib].re = xtmp_re;
          y_shifted_data[ib].im = xtmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for getFreqRep.c
 *
 * [EOF]
 */
