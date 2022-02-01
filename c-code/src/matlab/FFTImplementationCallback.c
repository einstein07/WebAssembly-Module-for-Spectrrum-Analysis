/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFTImplementationCallback.c
 *
 * Code generation for function 'FFTImplementationCallback'
 *
 */

/* Include files */
#include "FFTImplementationCallback.h"
#include "getFreqRep_emxutil.h"
#include "getFreqRep_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void c_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int n1_unsigned,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

static void d_FFTImplementationCallback_doH(
    const double x_data[], int x_size, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv);

static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int n1_unsigned,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

/* Function Definitions */
static void c_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int n1_unsigned,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y)
{
  const creal_T *x_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_temp_re_tmp;
  int i;
  int iDelta2;
  int iheight;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  boolean_T tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  iy = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iy);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    iy = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, iy);
    y_data = y->data;
    for (iy = 0; iy < n1_unsigned; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }
  }
  iDelta2 = x->size[0];
  if (iDelta2 > n1_unsigned) {
    iDelta2 = n1_unsigned;
  }
  iheight = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    y_data[iy] = x_data[i];
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y_data[iy] = x_data[iDelta2 - 1];
  if (n1_unsigned > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      temp_re = y_data[i].re;
      twid_re = y_data[i].im;
      y_data[i + 1].re = temp_re - temp_re_tmp;
      y_data[i + 1].im = twid_re - temp_im;
      y_data[i].re = temp_re + temp_re_tmp;
      y_data[i].im = twid_re + temp_im;
    }
  }
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y_data[b_temp_re_tmp].re;
      temp_im = y_data[b_temp_re_tmp].im;
      y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y_data[b_temp_re_tmp].im;
        temp_im = y_data[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      ju++;
    }
    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

static void d_FFTImplementationCallback_doH(
    const double x_data[], int x_size, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv)
{
  static double costab1q_data[4097];
  static double hsintab_data[4097];
  emxArray_creal_T *b_y;
  emxArray_creal_T *fy;
  emxArray_creal_T *r;
  emxArray_real_T b_costab1q_data;
  emxArray_real_T b_hcostabinv_data;
  emxArray_real_T b_hsintab_data;
  emxArray_real_T b_hsintabinv_data;
  emxArray_real_T *b_costab;
  emxArray_real_T *b_sintab;
  creal_T reconVar1_data[2048];
  creal_T reconVar2_data[2048];
  creal_T ytmp_data[2048];
  const creal_T *wwc_data;
  creal_T *c_y_data;
  creal_T *fy_data;
  creal_T *r1;
  creal_T *y_data;
  cuint8_T b_y_data[4096];
  double hcostabinv_data[4097];
  double hsintabinv_data[4097];
  const double *costab_data;
  const double *costabinv_data;
  const double *sintab_data;
  const double *sintabinv_data;
  double b_temp_re_tmp;
  double b_ytmp_re_tmp;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  double ytmp_re_tmp;
  double z_tmp;
  double *b_costab_data;
  double *b_sintab_data;
  int wrapIndex_data[2048];
  int costab1q_size[2];
  int hcostabinv_size[2];
  int hsintab_size[2];
  int hsintabinv_size[2];
  int hnRows;
  int i;
  int iDelta2;
  int ihi;
  int istart;
  int j;
  int ju;
  int k;
  int nRowsD2;
  int nd2;
  int temp_re_tmp;
  boolean_T tst;
  sintabinv_data = sintabinv->data;
  costabinv_data = costabinv->data;
  sintab_data = sintab->data;
  costab_data = costab->data;
  wwc_data = wwc->data;
  y_data = y->data;
  hnRows = nRows / 2;
  if ((hnRows > nrowsx) && (0 <= hnRows - 1)) {
    memset(&b_y_data[0], 0, hnRows * sizeof(cuint8_T));
  }
  for (ihi = 0; ihi < hnRows; ihi++) {
    ytmp_data[ihi].re = 0.0;
    ytmp_data[ihi].im = b_y_data[ihi].im;
  }
  if ((x_size & 1) == 0) {
    tst = true;
    ju = x_size;
  } else if (x_size >= nRows) {
    tst = true;
    ju = nRows;
  } else {
    tst = false;
    ju = x_size - 1;
  }
  if (ju > nRows) {
    ju = nRows;
  }
  nd2 = nRows << 1;
  temp_im = 6.2831853071795862 / (double)nd2;
  j = nd2 / 2 / 2;
  costab1q_size[0] = 1;
  costab1q_size[1] = j + 1;
  costab1q_data[0] = 1.0;
  nd2 = j / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(temp_im * ((double)k + 1.0));
  }
  ihi = nd2 + 2;
  nd2 = j - 1;
  for (k = ihi; k <= nd2; k++) {
    costab1q_data[k] = sin(temp_im * (double)(j - k));
  }
  emxInit_real_T(&b_costab);
  emxInit_real_T(&b_sintab);
  costab1q_data[j] = 0.0;
  j = costab1q_size[1] - 1;
  nd2 = (costab1q_size[1] - 1) << 1;
  ihi = b_costab->size[0] * b_costab->size[1];
  b_costab->size[0] = 1;
  b_costab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(b_costab, ihi);
  b_costab_data = b_costab->data;
  ihi = b_sintab->size[0] * b_sintab->size[1];
  b_sintab->size[0] = 1;
  b_sintab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(b_sintab, ihi);
  b_sintab_data = b_sintab->data;
  b_costab_data[0] = 1.0;
  b_sintab_data[0] = 0.0;
  for (k = 0; k < j; k++) {
    b_costab_data[k + 1] = costab1q_data[k + 1];
    b_sintab_data[k + 1] = -costab1q_data[(j - k) - 1];
  }
  ihi = costab1q_size[1];
  for (k = ihi; k <= nd2; k++) {
    b_costab_data[k] = -costab1q_data[nd2 - k];
    b_sintab_data[k] = -costab1q_data[k - j];
  }
  nd2 = costab->size[1] / 2;
  costab1q_size[0] = 1;
  costab1q_size[1] = nd2;
  hsintab_size[0] = 1;
  hsintab_size[1] = nd2;
  hcostabinv_size[0] = 1;
  hcostabinv_size[1] = nd2;
  hsintabinv_size[0] = 1;
  hsintabinv_size[1] = nd2;
  for (i = 0; i < nd2; i++) {
    iDelta2 = ((i + 1) << 1) - 2;
    costab1q_data[i] = costab_data[iDelta2];
    hsintab_data[i] = sintab_data[iDelta2];
    hcostabinv_data[i] = costabinv_data[iDelta2];
    hsintabinv_data[i] = sintabinv_data[iDelta2];
  }
  for (i = 0; i < hnRows; i++) {
    ihi = i << 1;
    reconVar1_data[i].re = b_sintab_data[ihi] + 1.0;
    reconVar1_data[i].im = -b_costab_data[ihi];
    reconVar2_data[i].re = 1.0 - b_sintab_data[ihi];
    reconVar2_data[i].im = b_costab_data[ihi];
    if (i + 1 != 1) {
      wrapIndex_data[i] = (hnRows - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  emxFree_real_T(&b_sintab);
  emxFree_real_T(&b_costab);
  z_tmp = (double)ju / 2.0;
  ihi = (int)((double)ju / 2.0);
  for (iDelta2 = 0; iDelta2 < ihi; iDelta2++) {
    temp_re_tmp = (hnRows + iDelta2) - 1;
    temp_re = wwc_data[temp_re_tmp].re;
    temp_im = wwc_data[temp_re_tmp].im;
    nd2 = iDelta2 << 1;
    twid_re = x_data[nd2];
    twid_im = x_data[nd2 + 1];
    ytmp_data[iDelta2].re = temp_re * twid_re + temp_im * twid_im;
    ytmp_data[iDelta2].im = temp_re * twid_im - temp_im * twid_re;
  }
  if (!tst) {
    temp_re_tmp = (hnRows + (int)z_tmp) - 1;
    temp_re = wwc_data[temp_re_tmp].re;
    temp_im = wwc_data[temp_re_tmp].im;
    twid_re = x_data[(int)z_tmp << 1];
    ytmp_data[(int)z_tmp].re = temp_re * twid_re + temp_im * 0.0;
    ytmp_data[(int)z_tmp].im = temp_re * 0.0 - temp_im * twid_re;
    if ((int)z_tmp + 2 <= hnRows) {
      ihi = (int)((double)ju / 2.0) + 2;
      if (ihi <= hnRows) {
        memset(&ytmp_data[ihi + -1], 0, ((hnRows - ihi) + 1) * sizeof(creal_T));
      }
    }
  } else if ((int)z_tmp + 1 <= hnRows) {
    ihi = (int)((double)ju / 2.0) + 1;
    if (ihi <= hnRows) {
      memset(&ytmp_data[ihi + -1], 0, ((hnRows - ihi) + 1) * sizeof(creal_T));
    }
  }
  emxInit_creal_T(&b_y);
  z_tmp = (double)nfft / 2.0;
  nd2 = (int)z_tmp;
  ihi = b_y->size[0];
  b_y->size[0] = (int)z_tmp;
  emxEnsureCapacity_creal_T(b_y, ihi);
  c_y_data = b_y->data;
  if ((int)z_tmp > hnRows) {
    ihi = b_y->size[0];
    b_y->size[0] = (int)z_tmp;
    emxEnsureCapacity_creal_T(b_y, ihi);
    c_y_data = b_y->data;
    for (ihi = 0; ihi < nd2; ihi++) {
      c_y_data[ihi].re = 0.0;
      c_y_data[ihi].im = 0.0;
    }
  }
  emxInit_creal_T(&fy);
  ihi = fy->size[0];
  fy->size[0] = b_y->size[0];
  emxEnsureCapacity_creal_T(fy, ihi);
  fy_data = fy->data;
  nd2 = b_y->size[0];
  for (ihi = 0; ihi < nd2; ihi++) {
    fy_data[ihi] = c_y_data[ihi];
  }
  iDelta2 = (int)z_tmp;
  if (hnRows <= iDelta2) {
    iDelta2 = hnRows;
  }
  istart = (int)z_tmp - 2;
  nRowsD2 = (int)z_tmp / 2;
  k = nRowsD2 / 2;
  nd2 = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    fy_data[nd2] = ytmp_data[i];
    j = (int)z_tmp;
    tst = true;
    while (tst) {
      j >>= 1;
      ju ^= j;
      tst = ((ju & j) == 0);
    }
    nd2 = ju;
  }
  fy_data[nd2] = ytmp_data[iDelta2 - 1];
  ihi = b_y->size[0];
  b_y->size[0] = fy->size[0];
  emxEnsureCapacity_creal_T(b_y, ihi);
  c_y_data = b_y->data;
  nd2 = fy->size[0];
  for (ihi = 0; ihi < nd2; ihi++) {
    c_y_data[ihi] = fy_data[ihi];
  }
  if ((int)z_tmp > 1) {
    for (i = 0; i <= istart; i += 2) {
      b_temp_re_tmp = c_y_data[i + 1].re;
      temp_im = c_y_data[i + 1].im;
      temp_re = c_y_data[i].re;
      twid_re = c_y_data[i].im;
      c_y_data[i + 1].re = temp_re - b_temp_re_tmp;
      c_y_data[i + 1].im = twid_re - temp_im;
      c_y_data[i].re = temp_re + b_temp_re_tmp;
      c_y_data[i].im = twid_re + temp_im;
    }
  }
  nd2 = 2;
  iDelta2 = 4;
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += iDelta2) {
      temp_re_tmp = i + nd2;
      temp_re = c_y_data[temp_re_tmp].re;
      temp_im = c_y_data[temp_re_tmp].im;
      c_y_data[temp_re_tmp].re = c_y_data[i].re - temp_re;
      c_y_data[temp_re_tmp].im = c_y_data[i].im - temp_im;
      c_y_data[i].re += temp_re;
      c_y_data[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab1q_data[j];
      twid_im = hsintab_data[j];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + nd2;
        b_temp_re_tmp = c_y_data[temp_re_tmp].im;
        temp_im = c_y_data[temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * b_temp_re_tmp;
        temp_im = twid_re * b_temp_re_tmp + twid_im * temp_im;
        c_y_data[temp_re_tmp].re = c_y_data[i].re - temp_re;
        c_y_data[temp_re_tmp].im = c_y_data[i].im - temp_im;
        c_y_data[i].re += temp_re;
        c_y_data[i].im += temp_im;
        i += iDelta2;
      }
      istart++;
    }
    k /= 2;
    nd2 = iDelta2;
    iDelta2 += iDelta2;
    ju -= nd2;
  }
  emxInit_creal_T(&r);
  b_costab1q_data.data = &costab1q_data[0];
  b_costab1q_data.size = &costab1q_size[0];
  b_costab1q_data.allocatedSize = 4097;
  b_costab1q_data.numDimensions = 2;
  b_costab1q_data.canFreeData = false;
  b_hsintab_data.data = &hsintab_data[0];
  b_hsintab_data.size = &hsintab_size[0];
  b_hsintab_data.allocatedSize = 4097;
  b_hsintab_data.numDimensions = 2;
  b_hsintab_data.canFreeData = false;
  c_FFTImplementationCallback_r2b(wwc, (int)z_tmp, &b_costab1q_data,
                                  &b_hsintab_data, r);
  r1 = r->data;
  ihi = fy->size[0];
  fy->size[0] = b_y->size[0];
  emxEnsureCapacity_creal_T(fy, ihi);
  fy_data = fy->data;
  nd2 = b_y->size[0];
  for (ihi = 0; ihi < nd2; ihi++) {
    temp_im = c_y_data[ihi].re;
    temp_re = r1[ihi].im;
    twid_re = c_y_data[ihi].im;
    twid_im = r1[ihi].re;
    fy_data[ihi].re = temp_im * twid_im - twid_re * temp_re;
    fy_data[ihi].im = temp_im * temp_re + twid_re * twid_im;
  }
  emxFree_creal_T(&b_y);
  b_hcostabinv_data.data = &hcostabinv_data[0];
  b_hcostabinv_data.size = &hcostabinv_size[0];
  b_hcostabinv_data.allocatedSize = 4097;
  b_hcostabinv_data.numDimensions = 2;
  b_hcostabinv_data.canFreeData = false;
  b_hsintabinv_data.data = &hsintabinv_data[0];
  b_hsintabinv_data.size = &hsintabinv_size[0];
  b_hsintabinv_data.allocatedSize = 4097;
  b_hsintabinv_data.numDimensions = 2;
  b_hsintabinv_data.canFreeData = false;
  d_FFTImplementationCallback_r2b(fy, (int)z_tmp, &b_hcostabinv_data,
                                  &b_hsintabinv_data, r);
  r1 = r->data;
  ihi = fy->size[0];
  fy->size[0] = r->size[0];
  emxEnsureCapacity_creal_T(fy, ihi);
  fy_data = fy->data;
  nd2 = r->size[0];
  for (ihi = 0; ihi < nd2; ihi++) {
    fy_data[ihi] = r1[ihi];
  }
  emxFree_creal_T(&r);
  ihi = wwc->size[0];
  for (k = hnRows; k <= ihi; k++) {
    temp_im = wwc_data[k - 1].re;
    temp_re = fy_data[k - 1].im;
    twid_re = wwc_data[k - 1].im;
    twid_im = fy_data[k - 1].re;
    nd2 = k - hnRows;
    ytmp_data[nd2].re = temp_im * twid_im + twid_re * temp_re;
    ytmp_data[nd2].im = temp_im * temp_re - twid_re * twid_im;
  }
  emxFree_creal_T(&fy);
  for (i = 0; i < hnRows; i++) {
    ihi = wrapIndex_data[i];
    temp_im = ytmp_data[i].re;
    temp_re = reconVar1_data[i].im;
    twid_re = ytmp_data[i].im;
    twid_im = reconVar1_data[i].re;
    b_temp_re_tmp = ytmp_data[ihi - 1].re;
    z_tmp = -ytmp_data[ihi - 1].im;
    ytmp_re_tmp = reconVar2_data[i].im;
    b_ytmp_re_tmp = reconVar2_data[i].re;
    y_data[i].re =
        0.5 * ((temp_im * twid_im - twid_re * temp_re) +
               (b_temp_re_tmp * b_ytmp_re_tmp - z_tmp * ytmp_re_tmp));
    y_data[i].im =
        0.5 * ((temp_im * temp_re + twid_re * twid_im) +
               (b_temp_re_tmp * ytmp_re_tmp + z_tmp * b_ytmp_re_tmp));
    ihi = hnRows + i;
    y_data[ihi].re = 0.5 * ((temp_im * b_ytmp_re_tmp - twid_re * ytmp_re_tmp) +
                            (b_temp_re_tmp * twid_im - z_tmp * temp_re));
    y_data[ihi].im = 0.5 * ((temp_im * ytmp_re_tmp + twid_re * b_ytmp_re_tmp) +
                            (b_temp_re_tmp * temp_re + z_tmp * twid_im));
  }
}

static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int n1_unsigned,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y)
{
  const creal_T *x_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_temp_re_tmp;
  int i;
  int iDelta2;
  int iheight;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  boolean_T tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  iDelta2 = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iDelta2);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    iDelta2 = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, iDelta2);
    y_data = y->data;
    for (iDelta2 = 0; iDelta2 < n1_unsigned; iDelta2++) {
      y_data[iDelta2].re = 0.0;
      y_data[iDelta2].im = 0.0;
    }
  }
  iDelta2 = x->size[0];
  if (iDelta2 > n1_unsigned) {
    iDelta2 = n1_unsigned;
  }
  iheight = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    y_data[iy] = x_data[i];
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y_data[iy] = x_data[iDelta2 - 1];
  if (n1_unsigned > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re_tmp = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      temp_re = y_data[i].re;
      twid_re = y_data[i].im;
      y_data[i + 1].re = temp_re - temp_re_tmp;
      y_data[i + 1].im = twid_re - temp_im;
      y_data[i].re = temp_re + temp_re_tmp;
      y_data[i].im = twid_re + temp_im;
    }
  }
  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y_data[b_temp_re_tmp].re;
      temp_im = y_data[b_temp_re_tmp].im;
      y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = ju;
      ihi = ju + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y_data[b_temp_re_tmp].im;
        temp_im = y_data[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
        y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      ju++;
    }
    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
  if (y->size[0] > 1) {
    temp_im = 1.0 / (double)y->size[0];
    iy = y->size[0];
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y_data[iDelta2].re *= temp_im;
      y_data[iDelta2].im *= temp_im;
    }
  }
}

void c_FFTImplementationCallback_doH(const double x_data[], int x_size,
                                     emxArray_creal_T *y, int unsigned_nRows,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab)
{
  emxArray_creal_T *b_y;
  creal_T reconVar1_data[2048];
  creal_T reconVar2_data[2048];
  creal_T *b_y_data;
  creal_T *y_data;
  double hcostab_data[4097];
  double hsintab_data[4097];
  const double *costab_data;
  const double *sintab_data;
  double b_y_re_tmp;
  double c_y_re_tmp;
  double d_y_re_tmp;
  double temp2_im;
  double temp2_im_tmp;
  double temp2_re;
  double temp_im;
  double temp_im_tmp;
  double temp_re;
  double temp_re_tmp;
  double y_re_tmp;
  double z_tmp;
  int bitrevIndex_data[2048];
  int wrapIndex_data[2048];
  int b_j1;
  int hszCostab;
  int i;
  int ihi;
  int istart;
  int iy;
  int ju;
  int k;
  int nRows;
  int nRowsD2;
  boolean_T tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  y_data = y->data;
  nRows = unsigned_nRows / 2;
  istart = y->size[0];
  if (istart > nRows) {
    istart = nRows;
  }
  ihi = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  hszCostab = costab->size[1] / 2;
  for (i = 0; i < hszCostab; i++) {
    iy = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[iy];
    hsintab_data[i] = sintab_data[iy];
  }
  for (i = 0; i < nRows; i++) {
    temp_re = sintab_data[i];
    temp2_re = costab_data[i];
    reconVar1_data[i].re = temp_re + 1.0;
    reconVar1_data[i].im = -temp2_re;
    reconVar2_data[i].re = 1.0 - temp_re;
    reconVar2_data[i].im = temp2_re;
    if (i + 1 != 1) {
      wrapIndex_data[i] = (nRows - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  z_tmp = (double)unsigned_nRows / 2.0;
  ju = 0;
  iy = 1;
  hszCostab = (int)z_tmp;
  if (0 <= hszCostab - 1) {
    memset(&bitrevIndex_data[0], 0, hszCostab * sizeof(int));
  }
  for (b_j1 = 0; b_j1 <= istart - 2; b_j1++) {
    bitrevIndex_data[b_j1] = iy;
    hszCostab = (int)z_tmp;
    tst = true;
    while (tst) {
      hszCostab >>= 1;
      ju ^= hszCostab;
      tst = ((ju & hszCostab) == 0);
    }
    iy = ju + 1;
  }
  bitrevIndex_data[istart - 1] = iy;
  if ((x_size & 1) == 0) {
    tst = true;
    istart = x_size;
  } else if (x_size >= unsigned_nRows) {
    tst = true;
    istart = unsigned_nRows;
  } else {
    tst = false;
    istart = x_size - 1;
  }
  if (istart <= unsigned_nRows) {
    hszCostab = istart;
  } else {
    hszCostab = unsigned_nRows;
  }
  temp_re = (double)hszCostab / 2.0;
  if (istart > unsigned_nRows) {
    istart = unsigned_nRows;
  }
  ju = (int)((double)istart / 2.0);
  for (i = 0; i < ju; i++) {
    iy = i << 1;
    hszCostab = bitrevIndex_data[i];
    y_data[hszCostab - 1].re = x_data[iy];
    y_data[hszCostab - 1].im = x_data[iy + 1];
  }
  if (!tst) {
    ju = bitrevIndex_data[(int)temp_re] - 1;
    y_data[ju].re = x_data[(int)temp_re << 1];
    y_data[ju].im = 0.0;
  }
  emxInit_creal_T(&b_y);
  ju = b_y->size[0];
  b_y->size[0] = y->size[0];
  emxEnsureCapacity_creal_T(b_y, ju);
  b_y_data = b_y->data;
  hszCostab = y->size[0];
  for (ju = 0; ju < hszCostab; ju++) {
    b_y_data[ju] = y_data[ju];
  }
  if (nRows > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp_re_tmp = b_y_data[i + 1].re;
      temp_im_tmp = b_y_data[i + 1].im;
      temp_im = b_y_data[i].re;
      temp_re = b_y_data[i].im;
      b_y_data[i + 1].re = temp_im - temp_re_tmp;
      b_y_data[i + 1].im = temp_re - temp_im_tmp;
      b_y_data[i].re = temp_im + temp_re_tmp;
      b_y_data[i].im = temp_re + temp_im_tmp;
    }
  }
  hszCostab = 2;
  iy = 4;
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += iy) {
      b_j1 = i + hszCostab;
      temp_re = b_y_data[b_j1].re;
      temp_im = b_y_data[b_j1].im;
      b_y_data[b_j1].re = b_y_data[i].re - temp_re;
      b_y_data[b_j1].im = b_y_data[i].im - temp_im;
      b_y_data[i].re += temp_re;
      b_y_data[i].im += temp_im;
    }
    istart = 1;
    for (nRows = k; nRows < nRowsD2; nRows += k) {
      temp2_re = hcostab_data[nRows];
      temp2_im = hsintab_data[nRows];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        b_j1 = i + hszCostab;
        temp_re_tmp = b_y_data[b_j1].im;
        y_re_tmp = b_y_data[b_j1].re;
        temp_re = temp2_re * y_re_tmp - temp2_im * temp_re_tmp;
        temp_im = temp2_re * temp_re_tmp + temp2_im * y_re_tmp;
        b_y_data[b_j1].re = b_y_data[i].re - temp_re;
        b_y_data[b_j1].im = b_y_data[i].im - temp_im;
        b_y_data[i].re += temp_re;
        b_y_data[i].im += temp_im;
        i += iy;
      }
      istart++;
    }
    k /= 2;
    hszCostab = iy;
    iy += iy;
    ju -= hszCostab;
  }
  ju = y->size[0];
  y->size[0] = b_y->size[0];
  emxEnsureCapacity_creal_T(y, ju);
  y_data = y->data;
  hszCostab = b_y->size[0];
  for (ju = 0; ju < hszCostab; ju++) {
    y_data[ju] = b_y_data[ju];
  }
  hszCostab = (int)z_tmp / 2;
  y_data[0].re = 0.5 * ((b_y_data[0].re * reconVar1_data[0].re -
                         b_y_data[0].im * reconVar1_data[0].im) +
                        (b_y_data[0].re * reconVar2_data[0].re -
                         -b_y_data[0].im * reconVar2_data[0].im));
  y_data[0].im = 0.5 * ((b_y_data[0].re * reconVar1_data[0].im +
                         b_y_data[0].im * reconVar1_data[0].re) +
                        (b_y_data[0].re * reconVar2_data[0].im +
                         -b_y_data[0].im * reconVar2_data[0].re));
  y_data[(int)z_tmp].re = 0.5 * ((b_y_data[0].re * reconVar2_data[0].re -
                                  b_y_data[0].im * reconVar2_data[0].im) +
                                 (b_y_data[0].re * reconVar1_data[0].re -
                                  -b_y_data[0].im * reconVar1_data[0].im));
  y_data[(int)z_tmp].im = 0.5 * ((b_y_data[0].re * reconVar2_data[0].im +
                                  b_y_data[0].im * reconVar2_data[0].re) +
                                 (b_y_data[0].re * reconVar1_data[0].im +
                                  -b_y_data[0].im * reconVar1_data[0].re));
  emxFree_creal_T(&b_y);
  for (i = 2; i <= hszCostab; i++) {
    temp_re_tmp = y_data[i - 1].re;
    temp_im_tmp = y_data[i - 1].im;
    ju = wrapIndex_data[i - 1];
    temp2_im = y_data[ju - 1].re;
    temp2_im_tmp = y_data[ju - 1].im;
    y_re_tmp = reconVar1_data[i - 1].im;
    b_y_re_tmp = reconVar1_data[i - 1].re;
    c_y_re_tmp = reconVar2_data[i - 1].im;
    d_y_re_tmp = reconVar2_data[i - 1].re;
    y_data[i - 1].re =
        0.5 * ((temp_re_tmp * b_y_re_tmp - temp_im_tmp * y_re_tmp) +
               (temp2_im * d_y_re_tmp - -temp2_im_tmp * c_y_re_tmp));
    y_data[i - 1].im =
        0.5 * ((temp_re_tmp * y_re_tmp + temp_im_tmp * b_y_re_tmp) +
               (temp2_im * c_y_re_tmp + -temp2_im_tmp * d_y_re_tmp));
    iy = ((int)z_tmp + i) - 1;
    y_data[iy].re =
        0.5 * ((temp_re_tmp * d_y_re_tmp - temp_im_tmp * c_y_re_tmp) +
               (temp2_im * b_y_re_tmp - -temp2_im_tmp * y_re_tmp));
    y_data[iy].im =
        0.5 * ((temp_re_tmp * c_y_re_tmp + temp_im_tmp * d_y_re_tmp) +
               (temp2_im * y_re_tmp + -temp2_im_tmp * b_y_re_tmp));
    temp_im = reconVar1_data[ju - 1].im;
    temp_re = reconVar1_data[ju - 1].re;
    y_re_tmp = reconVar2_data[ju - 1].im;
    temp2_re = reconVar2_data[ju - 1].re;
    y_data[ju - 1].re =
        0.5 * ((temp2_im * temp_re - temp2_im_tmp * temp_im) +
               (temp_re_tmp * temp2_re - -temp_im_tmp * y_re_tmp));
    y_data[ju - 1].im =
        0.5 * ((temp2_im * temp_im + temp2_im_tmp * temp_re) +
               (temp_re_tmp * y_re_tmp + -temp_im_tmp * temp2_re));
    ju = (ju + (int)z_tmp) - 1;
    y_data[ju].re = 0.5 * ((temp2_im * temp2_re - temp2_im_tmp * y_re_tmp) +
                           (temp_re_tmp * temp_re - -temp_im_tmp * temp_im));
    y_data[ju].im = 0.5 * ((temp2_im * y_re_tmp + temp2_im_tmp * temp2_re) +
                           (temp_re_tmp * temp_im + -temp_im_tmp * temp_re));
  }
  if (hszCostab != 0) {
    temp_re_tmp = y_data[hszCostab].re;
    temp_im_tmp = y_data[hszCostab].im;
    y_re_tmp = reconVar1_data[hszCostab].im;
    b_y_re_tmp = reconVar1_data[hszCostab].re;
    c_y_re_tmp = reconVar2_data[hszCostab].im;
    d_y_re_tmp = reconVar2_data[hszCostab].re;
    temp_re = temp_re_tmp * d_y_re_tmp;
    temp2_re = temp_re_tmp * b_y_re_tmp;
    y_data[hszCostab].re = 0.5 * ((temp2_re - temp_im_tmp * y_re_tmp) +
                                  (temp_re - -temp_im_tmp * c_y_re_tmp));
    temp2_im = temp_re_tmp * c_y_re_tmp;
    temp_im = temp_re_tmp * y_re_tmp;
    y_data[hszCostab].im = 0.5 * ((temp_im + temp_im_tmp * b_y_re_tmp) +
                                  (temp2_im + -temp_im_tmp * d_y_re_tmp));
    ju = (int)z_tmp + hszCostab;
    y_data[ju].re = 0.5 * ((temp_re - temp_im_tmp * c_y_re_tmp) +
                           (temp2_re - -temp_im_tmp * y_re_tmp));
    y_data[ju].im = 0.5 * ((temp2_im + temp_im_tmp * d_y_re_tmp) +
                           (temp_im + -temp_im_tmp * b_y_re_tmp));
  }
}

void c_FFTImplementationCallback_dob(const double x_data[], int x_size,
                                     int n2blue, int nfft,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *wwc;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *wwc_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double b_nt_re_tmp;
  double nt_im;
  double nt_re;
  double twid_im;
  double twid_re;
  int i;
  int ihi;
  int j;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int nRowsD2;
  int nt_re_tmp;
  int rt;
  boolean_T tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  emxInit_creal_T(&wwc);
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    j = nfft / 2;
    nInt2m1 = (j + j) - 1;
    ihi = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, ihi);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[j - 1].re = 1.0;
    wwc_data[j - 1].im = 0.0;
    nInt2 = j << 1;
    for (k = 0; k <= j - 2; k++) {
      minNrowsNx = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= minNrowsNx) {
        rt += minNrowsNx - nInt2;
      } else {
        rt += minNrowsNx;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)j;
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = cos(nt_im);
        nt_im = sin(nt_im);
      }
      ihi = (j - k) - 2;
      wwc_data[ihi].re = nt_re;
      wwc_data[ihi].im = -nt_im;
    }
    ihi = nInt2m1 - 1;
    for (k = ihi; k >= j; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    ihi = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, ihi);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nfft - 1].re = 1.0;
    wwc_data[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    for (k = 0; k <= nfft - 2; k++) {
      minNrowsNx = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= minNrowsNx) {
        rt += minNrowsNx - nInt2;
      } else {
        rt += minNrowsNx;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = cos(nt_im);
        nt_im = sin(nt_im);
      }
      ihi = (nfft - k) - 2;
      wwc_data[ihi].re = nt_re;
      wwc_data[ihi].im = -nt_im;
    }
    ihi = nInt2m1 - 1;
    for (k = ihi; k >= nfft; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  }
  ihi = y->size[0];
  y->size[0] = nfft;
  emxEnsureCapacity_creal_T(y, ihi);
  y_data = y->data;
  if (nfft > x_size) {
    ihi = y->size[0];
    y->size[0] = nfft;
    emxEnsureCapacity_creal_T(y, ihi);
    y_data = y->data;
    for (ihi = 0; ihi < nfft; ihi++) {
      y_data[ihi].re = 0.0;
      y_data[ihi].im = 0.0;
    }
  }
  emxInit_creal_T(&fy);
  emxInit_creal_T(&fv);
  if ((n2blue != 1) && ((nfft & 1) == 0)) {
    d_FFTImplementationCallback_doH(x_data, x_size, y, x_size, nfft, n2blue,
                                    wwc, costab, sintab, costab, sintabinv);
  } else {
    if (nfft <= x_size) {
      minNrowsNx = nfft;
    } else {
      minNrowsNx = x_size;
    }
    for (k = 0; k < minNrowsNx; k++) {
      nt_re_tmp = (nfft + k) - 1;
      y_data[k].re = wwc_data[nt_re_tmp].re * x_data[k];
      y_data[k].im = wwc_data[nt_re_tmp].im * -x_data[k];
    }
    ihi = minNrowsNx + 1;
    for (k = ihi; k <= nfft; k++) {
      y_data[k - 1].re = 0.0;
      y_data[k - 1].im = 0.0;
    }
    ihi = fy->size[0];
    fy->size[0] = n2blue;
    emxEnsureCapacity_creal_T(fy, ihi);
    fy_data = fy->data;
    if (n2blue > y->size[0]) {
      ihi = fy->size[0];
      fy->size[0] = n2blue;
      emxEnsureCapacity_creal_T(fy, ihi);
      fy_data = fy->data;
      for (ihi = 0; ihi < n2blue; ihi++) {
        fy_data[ihi].re = 0.0;
        fy_data[ihi].im = 0.0;
      }
    }
    nInt2m1 = y->size[0];
    if (nInt2m1 > n2blue) {
      nInt2m1 = n2blue;
    }
    rt = n2blue - 2;
    nRowsD2 = n2blue / 2;
    k = nRowsD2 / 2;
    minNrowsNx = 0;
    nInt2 = 0;
    for (i = 0; i <= nInt2m1 - 2; i++) {
      fy_data[minNrowsNx] = y_data[i];
      minNrowsNx = n2blue;
      tst = true;
      while (tst) {
        minNrowsNx >>= 1;
        nInt2 ^= minNrowsNx;
        tst = ((nInt2 & minNrowsNx) == 0);
      }
      minNrowsNx = nInt2;
    }
    fy_data[minNrowsNx] = y_data[nInt2m1 - 1];
    if (n2blue > 1) {
      for (i = 0; i <= rt; i += 2) {
        b_nt_re_tmp = fy_data[i + 1].re;
        nt_im = fy_data[i + 1].im;
        twid_im = fy_data[i].re;
        nt_re = fy_data[i].im;
        fy_data[i + 1].re = twid_im - b_nt_re_tmp;
        fy_data[i + 1].im = nt_re - nt_im;
        fy_data[i].re = twid_im + b_nt_re_tmp;
        fy_data[i].im = nt_re + nt_im;
      }
    }
    minNrowsNx = 2;
    nInt2m1 = 4;
    rt = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (i = 0; i < rt; i += nInt2m1) {
        nt_re_tmp = i + minNrowsNx;
        nt_re = fy_data[nt_re_tmp].re;
        nt_im = fy_data[nt_re_tmp].im;
        fy_data[nt_re_tmp].re = fy_data[i].re - nt_re;
        fy_data[nt_re_tmp].im = fy_data[i].im - nt_im;
        fy_data[i].re += nt_re;
        fy_data[i].im += nt_im;
      }
      nInt2 = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab_data[j];
        twid_im = sintab_data[j];
        i = nInt2;
        ihi = nInt2 + rt;
        while (i < ihi) {
          nt_re_tmp = i + minNrowsNx;
          b_nt_re_tmp = fy_data[nt_re_tmp].im;
          nt_im = fy_data[nt_re_tmp].re;
          nt_re = twid_re * nt_im - twid_im * b_nt_re_tmp;
          nt_im = twid_re * b_nt_re_tmp + twid_im * nt_im;
          fy_data[nt_re_tmp].re = fy_data[i].re - nt_re;
          fy_data[nt_re_tmp].im = fy_data[i].im - nt_im;
          fy_data[i].re += nt_re;
          fy_data[i].im += nt_im;
          i += nInt2m1;
        }
        nInt2++;
      }
      k /= 2;
      minNrowsNx = nInt2m1;
      nInt2m1 += nInt2m1;
      rt -= minNrowsNx;
    }
    c_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
    fv_data = fv->data;
    minNrowsNx = fy->size[0];
    for (ihi = 0; ihi < minNrowsNx; ihi++) {
      twid_im = fy_data[ihi].re;
      nt_im = fv_data[ihi].im;
      nt_re = fy_data[ihi].im;
      twid_re = fv_data[ihi].re;
      fy_data[ihi].re = twid_im * twid_re - nt_re * nt_im;
      fy_data[ihi].im = twid_im * nt_im + nt_re * twid_re;
    }
    d_FFTImplementationCallback_r2b(fy, n2blue, costab, sintabinv, fv);
    fv_data = fv->data;
    ihi = wwc->size[0];
    for (k = nfft; k <= ihi; k++) {
      nt_im = wwc_data[k - 1].re;
      nt_re = fv_data[k - 1].im;
      twid_re = wwc_data[k - 1].im;
      twid_im = fv_data[k - 1].re;
      minNrowsNx = k - nfft;
      y_data[minNrowsNx].re = nt_im * twid_im + twid_re * nt_re;
      y_data[minNrowsNx].im = nt_im * nt_re - twid_re * twid_im;
    }
  }
  emxFree_creal_T(&fv);
  emxFree_creal_T(&fy);
  emxFree_creal_T(&wwc);
}

/* End of code generation (FFTImplementationCallback.c) */
