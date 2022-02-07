/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: getFreqRep.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 27-Jan-2022 13:57:12
 */

/* Include Files */
#include "getFreqRep.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <emscripten/emscripten.h>


/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double y;
  a = fabs(u0);
  y = fabs(u1);
  if (a < y) {
    a /= y;
    y *= sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * sqrt(y * y + 1.0);
  } else if (!rtIsNaN(y)) {
    y = a * 1.4142135623730951;
  }
  return y;
}

/*
 * codegen
 * GETFREQREP Computes the fft of a given signal.
 *    [Y] = GETFREQREP(X) computes the fast fourier transform of a real
 *    signal. X is an M-by-1 vector. Y is an M-by-1 vector that contains the
 *    results of the fft operation on X.
 *
 * Arguments    : const double x[2048]
 *                double y[2048]
 * Return Type  : void
 */
EMSCRIPTEN_KEEPALIVE double *getFreqRep(const double x[2048], double y[2048])
{
  creal_T b_y[2048];
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
  c_FFTImplementationCallback_doH(x, b_y);
  for (dim = 0; dim < 2; dim++) {
    ic = dim - 1;
    if (dim + 1 <= 1) {
      a = 2048;
    } else {
      a = 1;
    }
    if (a > 1) {
      vlend2 = a / 2;
      vstride = 1;
      for (k = 0; k <= ic; k++) {
        vstride <<= 11;
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
            xtmp_re = b_y[ic].re;
            xtmp_im = b_y[ic].im;
            a += ib;
            b_y[ic] = b_y[a];
            b_y[a].re = xtmp_re;
            b_y[a].im = xtmp_im;
          }
        }
      } else {
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          i1++;
          ib = i1 + midoffset;
          xtmp_re = b_y[ib].re;
          xtmp_im = b_y[ib].im;
          for (k = 0; k < vlend2; k++) {
            ic = ib + vstride;
            a = (i1 + k * vstride) - 1;
            b_y[ib] = b_y[a];
            b_y[a] = b_y[ic];
            ib = ic;
          }
          b_y[ib].re = xtmp_re;
          b_y[ib].im = xtmp_im;
        }
      }
    }
  }
  for (k = 0; k < 2048; k++) {
    y[k] = rt_hypotd_snf(b_y[k].re, b_y[k].im);
  }
  return y;
}

/*
 * File trailer for getFreqRep.c
 *
 * [EOF]
 */
