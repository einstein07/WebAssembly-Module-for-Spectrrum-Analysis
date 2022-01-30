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
#include "FFTImplementationCallback.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void getFreqRep(const short x_data[], const int x_size[1], creal_T y_data[],
                int y_size[1], creal_T y_shifted_data[], int y_shifted_size[1])
{
  static creal_T b_y_data[4000];
  double costab_data[2001];
  double sintab_data[2001];
  double sintabinv_data[2001];
  double costab1q_data[1001];
  double b_x_data[1000];
  double temp_im;
  double temp_re;
  int costab_size[2];
  int dim;
  int i1;
  int ib;
  int j;
  int k;
  int midoffset;
  int pmax;
  int pmin;
  int pow2p;
  int vlend2;
  int vstride;
  boolean_T exitg1;
  boolean_T useRadix2;
  /* codegen */
  /* GETFREQREP Computes the fft of a given signal. */
  /*    [Y] = GETFREQREP(X) computes the fast fourier transform of a real  */
  /*    signal. X is an M-by-1 vector. Y is an M-by-1 vector that contains the
   */
  /*    results of the fft operation on X. */
  pmax = x_size[0];
  for (pmin = 0; pmin < pmax; pmin++) {
    b_x_data[pmin] = x_data[pmin];
  }
  if (x_size[0] == 0) {
    y_size[0] = 0;
  } else {
    useRadix2 = ((x_size[0] & (x_size[0] - 1)) == 0);
    i1 = 1;
    if (useRadix2) {
      pmax = x_size[0];
    } else {
      ib = (x_size[0] + x_size[0]) - 1;
      pmax = 31;
      if (ib <= 1) {
        pmax = 0;
      } else {
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == ib) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > ib) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      i1 = 1 << pmax;
      pmax = i1;
    }
    temp_re = 6.2831853071795862 / (double)pmax;
    ib = pmax / 2 / 2;
    pow2p = ib + 1;
    costab1q_data[0] = 1.0;
    pmax = ib / 2 - 1;
    for (k = 0; k <= pmax; k++) {
      costab1q_data[k + 1] = cos(temp_re * ((double)k + 1.0));
    }
    pmin = pmax + 2;
    pmax = ib - 1;
    for (k = pmin; k <= pmax; k++) {
      costab1q_data[k] = sin(temp_re * (double)(ib - k));
    }
    costab1q_data[ib] = 0.0;
    if (!useRadix2) {
      pmin = ib << 1;
      costab_size[0] = 1;
      costab_size[1] = (short)(pmin + 1);
      costab_data[0] = 1.0;
      sintab_data[0] = 0.0;
      for (k = 0; k < ib; k++) {
        sintabinv_data[k + 1] = costab1q_data[(ib - k) - 1];
      }
      for (k = pow2p; k <= pmin; k++) {
        sintabinv_data[k] = costab1q_data[k - ib];
      }
      for (k = 0; k < ib; k++) {
        costab_data[k + 1] = costab1q_data[k + 1];
        sintab_data[k + 1] = -costab1q_data[(ib - k) - 1];
      }
      for (k = pow2p; k <= pmin; k++) {
        costab_data[k] = -costab1q_data[pmin - k];
        sintab_data[k] = -costab1q_data[k - ib];
      }
    } else {
      pmin = ib << 1;
      costab_size[0] = 1;
      costab_size[1] = (short)(pmin + 1);
      costab_data[0] = 1.0;
      sintab_data[0] = 0.0;
      for (k = 0; k < ib; k++) {
        costab_data[k + 1] = costab1q_data[k + 1];
        sintab_data[k + 1] = -costab1q_data[(ib - k) - 1];
      }
      for (k = pow2p; k <= pmin; k++) {
        costab_data[k] = -costab1q_data[pmin - k];
        sintab_data[k] = -costab1q_data[k - ib];
      }
    }
    if (useRadix2) {
      y_size[0] = (short)x_size[0];
      if (x_size[0] != 1) {
        c_FFTImplementationCallback_doH(b_x_data, x_size[0], y_data, &y_size[0],
                                        x_size[0], costab_data, costab_size,
                                        sintab_data);
      } else {
        y_data[0].re = b_x_data[0];
        y_data[0].im = 0.0;
        b_y_data[0] = y_data[0];
        y_size[0] = 1;
        y_data[0] = b_y_data[0];
      }
    } else {
      c_FFTImplementationCallback_dob(b_x_data, x_size[0], i1, x_size[0],
                                      costab_data, costab_size, sintab_data,
                                      sintabinv_data, y_data, &y_size[0]);
    }
  }
  y_shifted_size[0] = y_size[0];
  pmax = y_size[0];
  if (0 <= pmax - 1) {
    memcpy(&y_shifted_data[0], &y_data[0], pmax * sizeof(creal_T));
  }
  for (dim = 0; dim < 2; dim++) {
    pmax = dim - 1;
    if (dim + 1 <= 1) {
      pmin = y_shifted_size[0];
    } else {
      pmin = 1;
    }
    if (pmin > 1) {
      vlend2 = pmin / 2;
      vstride = 1;
      for (k = 0; k <= pmax; k++) {
        vstride *= y_shifted_size[0];
      }
      midoffset = vlend2 * vstride - 1;
      if (vlend2 << 1 == pmin) {
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          i1++;
          ib = i1 + midoffset;
          for (k = 0; k < vlend2; k++) {
            pmax = k * vstride;
            pow2p = (i1 + pmax) - 1;
            temp_re = y_shifted_data[pow2p].re;
            temp_im = y_shifted_data[pow2p].im;
            pmin = ib + pmax;
            y_shifted_data[pow2p] = y_shifted_data[pmin];
            y_shifted_data[pmin].re = temp_re;
            y_shifted_data[pmin].im = temp_im;
          }
        }
      } else {
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          i1++;
          ib = i1 + midoffset;
          temp_re = y_shifted_data[ib].re;
          temp_im = y_shifted_data[ib].im;
          for (k = 0; k < vlend2; k++) {
            pmax = ib + vstride;
            pmin = (i1 + k * vstride) - 1;
            y_shifted_data[ib] = y_shifted_data[pmin];
            y_shifted_data[pmin] = y_shifted_data[pmax];
            ib = pmax;
          }
          y_shifted_data[ib].re = temp_re;
          y_shifted_data[ib].im = temp_im;
        }
      }
    }
  }
}

/* End of code generation (getFreqRep.c) */
