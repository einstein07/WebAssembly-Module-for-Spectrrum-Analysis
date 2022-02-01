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
#include "getFreqRep_data.h"
#include "getFreqRep_emxutil.h"
#include "getFreqRep_initialize.h"
#include "getFreqRep_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
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

void getFreqRep(const short x_data[], const int x_size[1], double mag_data[],
                int mag_size[1], double phase_data[], int phase_size[1])
{
  static double costab1q_data[4097];
  static double b_x_data[4096];
  emxArray_creal_T *b_y;
  emxArray_creal_T *y;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *b_y_data;
  creal_T *y_data;
  double temp_im;
  double temp_re;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
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
  if (!isInitialized_getFreqRep) {
    getFreqRep_initialize();
  }
  /* codegen */
  /* GETFREQREP Computes the fft of a given signal. */
  /*    [Y] = GETFREQREP(X) computes the fast fourier transform of a real  */
  /*    signal. X is an M-by-1 vector. Y is an M-by-1 vector that contains the
   */
  /*    results of the fft operation on X. */
  pmax = x_size[0];
  for (midoffset = 0; midoffset < pmax; midoffset++) {
    b_x_data[midoffset] = x_data[midoffset];
  }
  emxInit_creal_T(&y);
  y_data = y->data;
  if (x_size[0] == 0) {
    y->size[0] = 0;
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
    midoffset = pmax + 2;
    pmax = ib - 1;
    for (k = midoffset; k <= pmax; k++) {
      costab1q_data[k] = sin(temp_re * (double)(ib - k));
    }
    costab1q_data[ib] = 0.0;
    emxInit_real_T(&costab);
    emxInit_real_T(&sintab);
    emxInit_real_T(&sintabinv);
    if (!useRadix2) {
      pmin = ib << 1;
      midoffset = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = (short)(pmin + 1);
      emxEnsureCapacity_real_T(costab, midoffset);
      costab_data = costab->data;
      midoffset = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = (short)(pmin + 1);
      emxEnsureCapacity_real_T(sintab, midoffset);
      sintab_data = sintab->data;
      costab_data[0] = 1.0;
      sintab_data[0] = 0.0;
      midoffset = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = (short)(pmin + 1);
      emxEnsureCapacity_real_T(sintabinv, midoffset);
      sintabinv_data = sintabinv->data;
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
      midoffset = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = (short)(pmin + 1);
      emxEnsureCapacity_real_T(costab, midoffset);
      costab_data = costab->data;
      midoffset = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = (short)(pmin + 1);
      emxEnsureCapacity_real_T(sintab, midoffset);
      sintab_data = sintab->data;
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
      sintabinv->size[0] = 1;
      sintabinv->size[1] = 0;
    }
    if (useRadix2) {
      midoffset = y->size[0];
      y->size[0] = (short)x_size[0];
      emxEnsureCapacity_creal_T(y, midoffset);
      y_data = y->data;
      if (x_size[0] != 1) {
        c_FFTImplementationCallback_doH(b_x_data, x_size[0], y, x_size[0],
                                        costab, sintab);
        y_data = y->data;
      } else {
        emxInit_creal_T(&b_y);
        y_data[0].re = b_x_data[0];
        y_data[0].im = 0.0;
        midoffset = b_y->size[0];
        b_y->size[0] = 1;
        emxEnsureCapacity_creal_T(b_y, midoffset);
        b_y_data = b_y->data;
        b_y_data[0] = y_data[0];
        midoffset = y->size[0];
        y->size[0] = b_y->size[0];
        emxEnsureCapacity_creal_T(y, midoffset);
        y_data = y->data;
        pmax = b_y->size[0];
        for (midoffset = 0; midoffset < pmax; midoffset++) {
          y_data[midoffset] = b_y_data[midoffset];
        }
        emxFree_creal_T(&b_y);
      }
    } else {
      c_FFTImplementationCallback_dob(b_x_data, x_size[0], i1, x_size[0],
                                      costab, sintab, sintabinv, y);
      y_data = y->data;
    }
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
  for (dim = 0; dim < 2; dim++) {
    pmax = dim - 1;
    if (dim + 1 <= 1) {
      pmin = y->size[0];
    } else {
      pmin = 1;
    }
    if (pmin > 1) {
      vlend2 = pmin / 2;
      vstride = 1;
      for (k = 0; k <= pmax; k++) {
        vstride *= y->size[0];
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
            temp_re = y_data[pow2p].re;
            temp_im = y_data[pow2p].im;
            pmin = ib + pmax;
            y_data[pow2p] = y_data[pmin];
            y_data[pmin].re = temp_re;
            y_data[pmin].im = temp_im;
          }
        }
      } else {
        i1 = 0;
        for (j = 0; j < vstride; j++) {
          i1++;
          ib = i1 + midoffset;
          temp_re = y_data[ib].re;
          temp_im = y_data[ib].im;
          for (k = 0; k < vlend2; k++) {
            pmax = ib + vstride;
            pmin = (i1 + k * vstride) - 1;
            y_data[ib] = y_data[pmin];
            y_data[pmin] = y_data[pmax];
            ib = pmax;
          }
          y_data[ib].re = temp_re;
          y_data[ib].im = temp_im;
        }
      }
    }
  }
  pmax = y->size[0];
  mag_size[0] = y->size[0];
  for (k = 0; k < pmax; k++) {
    mag_data[k] = rt_hypotd_snf(y_data[k].re, y_data[k].im);
  }
  phase_size[0] = y->size[0];
  pmax = y->size[0];
  emxFree_creal_T(&y);
  if (0 <= pmax - 1) {
    memset(&phase_data[0], 0, pmax * sizeof(double));
  }
}

/* End of code generation (getFreqRep.c) */
