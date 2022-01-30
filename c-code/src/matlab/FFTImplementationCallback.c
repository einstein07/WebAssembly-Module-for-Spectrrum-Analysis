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
#include <math.h>
#include <string.h>

/* Function Declarations */
static void c_FFTImplementationCallback_r2b(const creal_T x_data[], int x_size,
                                            int n1_unsigned,
                                            const double costab_data[],
                                            const double sintab_data[],
                                            creal_T y_data[], int *y_size);

static void d_FFTImplementationCallback_doH(
    const double x_data[], int x_size, creal_T y_data[], int nrowsx, int nRows,
    int nfft, const creal_T wwc_data[], int wwc_size,
    const double costab_data[], const int costab_size[2],
    const double sintab_data[], const double costabinv_data[],
    const double sintabinv_data[]);

static void d_FFTImplementationCallback_r2b(const creal_T x_data[], int x_size,
                                            int n1_unsigned,
                                            const double costab_data[],
                                            const double sintab_data[],
                                            creal_T y_data[], int *y_size);

/* Function Definitions */
static void c_FFTImplementationCallback_r2b(const creal_T x_data[], int x_size,
                                            int n1_unsigned,
                                            const double costab_data[],
                                            const double sintab_data[],
                                            creal_T y_data[], int *y_size)
{
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
  *y_size = n1_unsigned;
  if ((n1_unsigned > x_size) && (0 <= n1_unsigned - 1)) {
    memset(&y_data[0], 0, n1_unsigned * sizeof(creal_T));
  }
  if (x_size <= n1_unsigned) {
    iDelta2 = x_size;
  } else {
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
    const double x_data[], int x_size, creal_T y_data[], int nrowsx, int nRows,
    int nfft, const creal_T wwc_data[], int wwc_size,
    const double costab_data[], const int costab_size[2],
    const double sintab_data[], const double costabinv_data[],
    const double sintabinv_data[])
{
  static creal_T c_y_data[4000];
  static creal_T tmp_data[4000];
  static creal_T fy_data[2000];
  creal_T reconVar1_data[500];
  creal_T reconVar2_data[500];
  creal_T ytmp_data[500];
  cuint8_T b_y_data[1000];
  double b_costab_data[2001];
  double b_sintab_data[2001];
  double costab1q_data[1001];
  double hcostabinv_data[1001];
  double hsintab_data[1001];
  double hsintabinv_data[1001];
  double b_temp_re_tmp;
  double b_ytmp_re_tmp;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  double ytmp_re_tmp;
  double z_tmp;
  int wrapIndex_data[500];
  int hnRows;
  int i;
  int iheight;
  int ihi;
  int ju;
  int k;
  int n;
  int n2;
  int nRowsD2;
  int nd2;
  int temp_re_tmp;
  int y_size;
  boolean_T tst;
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
  n = nd2 / 2 / 2;
  iheight = n + 1;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(temp_im * ((double)k + 1.0));
  }
  ihi = nd2 + 2;
  nd2 = n - 1;
  for (k = ihi; k <= nd2; k++) {
    costab1q_data[k] = sin(temp_im * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  n2 = n << 1;
  b_costab_data[0] = 1.0;
  b_sintab_data[0] = 0.0;
  for (k = 0; k < n; k++) {
    b_costab_data[k + 1] = costab1q_data[k + 1];
    b_sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
  }
  for (k = iheight; k <= n2; k++) {
    b_costab_data[k] = -costab1q_data[n2 - k];
    b_sintab_data[k] = -costab1q_data[k - n];
  }
  nd2 = costab_size[1] / 2;
  for (i = 0; i < nd2; i++) {
    n2 = ((i + 1) << 1) - 2;
    costab1q_data[i] = costab_data[n2];
    hsintab_data[i] = sintab_data[n2];
    hcostabinv_data[i] = costabinv_data[n2];
    hsintabinv_data[i] = sintabinv_data[n2];
  }
  for (i = 0; i < hnRows; i++) {
    ihi = i << 1;
    temp_im = b_sintab_data[ihi];
    reconVar1_data[i].re = temp_im + 1.0;
    temp_re = b_costab_data[ihi];
    reconVar1_data[i].im = -temp_re;
    reconVar2_data[i].re = 1.0 - temp_im;
    reconVar2_data[i].im = temp_re;
    if (i + 1 != 1) {
      wrapIndex_data[i] = (hnRows - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  z_tmp = (double)ju / 2.0;
  ihi = (int)((double)ju / 2.0);
  for (n2 = 0; n2 < ihi; n2++) {
    temp_re_tmp = (hnRows + n2) - 1;
    temp_re = wwc_data[temp_re_tmp].re;
    temp_im = wwc_data[temp_re_tmp].im;
    nd2 = n2 << 1;
    twid_re = x_data[nd2];
    twid_im = x_data[nd2 + 1];
    ytmp_data[n2].re = temp_re * twid_re + temp_im * twid_im;
    ytmp_data[n2].im = temp_re * twid_im - temp_im * twid_re;
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
  z_tmp = (double)nfft / 2.0;
  nd2 = (int)z_tmp;
  y_size = (int)z_tmp;
  if ((int)z_tmp > hnRows) {
    y_size = (int)z_tmp;
    if (0 <= nd2 - 1) {
      memset(&c_y_data[0], 0, nd2 * sizeof(creal_T));
    }
  }
  if (0 <= y_size - 1) {
    memcpy(&fy_data[0], &c_y_data[0], y_size * sizeof(creal_T));
  }
  n2 = (int)z_tmp;
  if (hnRows <= n2) {
    n2 = hnRows;
  }
  iheight = (int)z_tmp - 2;
  nRowsD2 = (int)z_tmp / 2;
  k = nRowsD2 / 2;
  nd2 = 0;
  ju = 0;
  for (i = 0; i <= n2 - 2; i++) {
    fy_data[nd2] = ytmp_data[i];
    n = (int)z_tmp;
    tst = true;
    while (tst) {
      n >>= 1;
      ju ^= n;
      tst = ((ju & n) == 0);
    }
    nd2 = ju;
  }
  fy_data[nd2] = ytmp_data[n2 - 1];
  if (0 <= y_size - 1) {
    memcpy(&c_y_data[0], &fy_data[0], y_size * sizeof(creal_T));
  }
  if ((int)z_tmp > 1) {
    for (i = 0; i <= iheight; i += 2) {
      b_temp_re_tmp = c_y_data[i + 1].re;
      temp_re = c_y_data[i + 1].im;
      temp_im = c_y_data[i].re;
      twid_re = c_y_data[i].im;
      c_y_data[i + 1].re = temp_im - b_temp_re_tmp;
      c_y_data[i + 1].im = twid_re - temp_re;
      c_y_data[i].re = temp_im + b_temp_re_tmp;
      c_y_data[i].im = twid_re + temp_re;
    }
  }
  nd2 = 2;
  n2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += n2) {
      temp_re_tmp = i + nd2;
      temp_re = c_y_data[temp_re_tmp].re;
      temp_im = c_y_data[temp_re_tmp].im;
      c_y_data[temp_re_tmp].re = c_y_data[i].re - temp_re;
      c_y_data[temp_re_tmp].im = c_y_data[i].im - temp_im;
      c_y_data[i].re += temp_re;
      c_y_data[i].im += temp_im;
    }
    ju = 1;
    for (n = k; n < nRowsD2; n += k) {
      twid_re = costab1q_data[n];
      twid_im = hsintab_data[n];
      i = ju;
      ihi = ju + iheight;
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
        i += n2;
      }
      ju++;
    }
    k /= 2;
    nd2 = n2;
    n2 += n2;
    iheight -= nd2;
  }
  c_FFTImplementationCallback_r2b(wwc_data, wwc_size, (int)((double)nfft / 2.0),
                                  costab1q_data, hsintab_data, tmp_data, &nd2);
  for (ihi = 0; ihi < y_size; ihi++) {
    temp_im = c_y_data[ihi].re;
    temp_re = tmp_data[ihi].im;
    twid_re = c_y_data[ihi].im;
    twid_im = tmp_data[ihi].re;
    fy_data[ihi].re = temp_im * twid_im - twid_re * temp_re;
    fy_data[ihi].im = temp_im * temp_re + twid_re * twid_im;
  }
  d_FFTImplementationCallback_r2b(fy_data, y_size, (int)z_tmp, hcostabinv_data,
                                  hsintabinv_data, tmp_data, &nd2);
  if (0 <= nd2 - 1) {
    memcpy(&fy_data[0], &tmp_data[0], nd2 * sizeof(creal_T));
  }
  for (k = hnRows; k <= wwc_size; k++) {
    temp_im = wwc_data[k - 1].re;
    temp_re = fy_data[k - 1].im;
    twid_re = wwc_data[k - 1].im;
    twid_im = fy_data[k - 1].re;
    ihi = k - hnRows;
    ytmp_data[ihi].re = temp_im * twid_im + twid_re * temp_re;
    ytmp_data[ihi].im = temp_im * temp_re - twid_re * twid_im;
  }
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

static void d_FFTImplementationCallback_r2b(const creal_T x_data[], int x_size,
                                            int n1_unsigned,
                                            const double costab_data[],
                                            const double sintab_data[],
                                            creal_T y_data[], int *y_size)
{
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
  *y_size = n1_unsigned;
  if ((n1_unsigned > x_size) && (0 <= n1_unsigned - 1)) {
    memset(&y_data[0], 0, n1_unsigned * sizeof(creal_T));
  }
  if (x_size <= n1_unsigned) {
    iDelta2 = x_size;
  } else {
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
  if (n1_unsigned > 1) {
    temp_im = 1.0 / (double)n1_unsigned;
    for (iy = 0; iy < n1_unsigned; iy++) {
      y_data[iy].re *= temp_im;
      y_data[iy].im *= temp_im;
    }
  }
}

void c_FFTImplementationCallback_doH(const double x_data[], int x_size,
                                     creal_T y_data[], const int *y_size,
                                     int unsigned_nRows,
                                     const double costab_data[],
                                     const int costab_size[2],
                                     const double sintab_data[])
{
  creal_T b_y_data[4000];
  creal_T reconVar1_data[500];
  creal_T reconVar2_data[500];
  double hcostab_data[1001];
  double hsintab_data[1001];
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
  int bitrevIndex_data[500];
  int wrapIndex_data[500];
  int hszCostab;
  int i;
  int istart;
  int iy;
  int j;
  int ju;
  int k;
  int nRows;
  int nRowsD2;
  int nRowsM2;
  boolean_T tst;
  nRows = unsigned_nRows / 2;
  j = *y_size;
  if (j > nRows) {
    j = nRows;
  }
  nRowsM2 = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  hszCostab = costab_size[1] / 2;
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
  for (istart = 0; istart <= j - 2; istart++) {
    bitrevIndex_data[istart] = iy;
    hszCostab = (int)z_tmp;
    tst = true;
    while (tst) {
      hszCostab >>= 1;
      ju ^= hszCostab;
      tst = ((ju & hszCostab) == 0);
    }
    iy = ju + 1;
  }
  bitrevIndex_data[j - 1] = iy;
  if ((x_size & 1) == 0) {
    tst = true;
    j = x_size;
  } else if (x_size >= unsigned_nRows) {
    tst = true;
    j = unsigned_nRows;
  } else {
    tst = false;
    j = x_size - 1;
  }
  if (j <= unsigned_nRows) {
    hszCostab = j;
  } else {
    hszCostab = unsigned_nRows;
  }
  temp_re = (double)hszCostab / 2.0;
  if (j > unsigned_nRows) {
    j = unsigned_nRows;
  }
  iy = (int)((double)j / 2.0);
  for (i = 0; i < iy; i++) {
    ju = i << 1;
    hszCostab = bitrevIndex_data[i];
    y_data[hszCostab - 1].re = x_data[ju];
    y_data[hszCostab - 1].im = x_data[ju + 1];
  }
  if (!tst) {
    iy = bitrevIndex_data[(int)temp_re] - 1;
    y_data[iy].re = x_data[(int)temp_re << 1];
    y_data[iy].im = 0.0;
  }
  hszCostab = *y_size;
  if (0 <= hszCostab - 1) {
    memcpy(&b_y_data[0], &y_data[0], hszCostab * sizeof(creal_T));
  }
  if (nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
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
      nRowsM2 = i + hszCostab;
      temp_re = b_y_data[nRowsM2].re;
      temp_im = b_y_data[nRowsM2].im;
      b_y_data[nRowsM2].re = b_y_data[i].re - temp_re;
      b_y_data[nRowsM2].im = b_y_data[i].im - temp_im;
      b_y_data[i].re += temp_re;
      b_y_data[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      temp2_re = hcostab_data[j];
      temp2_im = hsintab_data[j];
      i = istart;
      nRows = istart + ju;
      while (i < nRows) {
        nRowsM2 = i + hszCostab;
        temp_re_tmp = b_y_data[nRowsM2].im;
        y_re_tmp = b_y_data[nRowsM2].re;
        temp_re = temp2_re * y_re_tmp - temp2_im * temp_re_tmp;
        temp_im = temp2_re * temp_re_tmp + temp2_im * y_re_tmp;
        b_y_data[nRowsM2].re = b_y_data[i].re - temp_re;
        b_y_data[nRowsM2].im = b_y_data[i].im - temp_im;
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
  if (0 <= *y_size - 1) {
    memcpy(&y_data[0], &b_y_data[0], *y_size * sizeof(creal_T));
  }
  hszCostab = (int)z_tmp / 2;
  temp_re = b_y_data[0].re * reconVar2_data[0].re;
  temp2_re = b_y_data[0].re * reconVar1_data[0].re;
  y_data[0].re = 0.5 * ((temp2_re - b_y_data[0].im * reconVar1_data[0].im) +
                        (temp_re - -b_y_data[0].im * reconVar2_data[0].im));
  temp2_im = b_y_data[0].re * reconVar2_data[0].im;
  temp_im = b_y_data[0].re * reconVar1_data[0].im;
  y_data[0].im = 0.5 * ((temp_im + b_y_data[0].im * reconVar1_data[0].re) +
                        (temp2_im + -b_y_data[0].im * reconVar2_data[0].re));
  y_data[(int)z_tmp].re =
      0.5 * ((temp_re - b_y_data[0].im * reconVar2_data[0].im) +
             (temp2_re - -b_y_data[0].im * reconVar1_data[0].im));
  y_data[(int)z_tmp].im =
      0.5 * ((temp2_im + b_y_data[0].im * reconVar2_data[0].re) +
             (temp_im + -b_y_data[0].im * reconVar1_data[0].re));
  for (i = 2; i <= hszCostab; i++) {
    temp_re_tmp = y_data[i - 1].re;
    temp_im_tmp = y_data[i - 1].im;
    iy = wrapIndex_data[i - 1];
    temp2_im = y_data[iy - 1].re;
    temp2_im_tmp = y_data[iy - 1].im;
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
    ju = ((int)z_tmp + i) - 1;
    y_data[ju].re =
        0.5 * ((temp_re_tmp * d_y_re_tmp - temp_im_tmp * c_y_re_tmp) +
               (temp2_im * b_y_re_tmp - -temp2_im_tmp * y_re_tmp));
    y_data[ju].im =
        0.5 * ((temp_re_tmp * c_y_re_tmp + temp_im_tmp * d_y_re_tmp) +
               (temp2_im * y_re_tmp + -temp2_im_tmp * b_y_re_tmp));
    temp_im = reconVar1_data[iy - 1].im;
    temp_re = reconVar1_data[iy - 1].re;
    y_re_tmp = reconVar2_data[iy - 1].im;
    temp2_re = reconVar2_data[iy - 1].re;
    y_data[iy - 1].re =
        0.5 * ((temp2_im * temp_re - temp2_im_tmp * temp_im) +
               (temp_re_tmp * temp2_re - -temp_im_tmp * y_re_tmp));
    y_data[iy - 1].im =
        0.5 * ((temp2_im * temp_im + temp2_im_tmp * temp_re) +
               (temp_re_tmp * y_re_tmp + -temp_im_tmp * temp2_re));
    iy = (iy + (int)z_tmp) - 1;
    y_data[iy].re = 0.5 * ((temp2_im * temp2_re - temp2_im_tmp * y_re_tmp) +
                           (temp_re_tmp * temp_re - -temp_im_tmp * temp_im));
    y_data[iy].im = 0.5 * ((temp2_im * y_re_tmp + temp2_im_tmp * temp2_re) +
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
    iy = (int)z_tmp + hszCostab;
    y_data[iy].re = 0.5 * ((temp_re - temp_im_tmp * c_y_re_tmp) +
                           (temp2_re - -temp_im_tmp * y_re_tmp));
    y_data[iy].im = 0.5 * ((temp2_im + temp_im_tmp * d_y_re_tmp) +
                           (temp_im + -temp_im_tmp * b_y_re_tmp));
  }
}

void c_FFTImplementationCallback_dob(const double x_data[], int x_size,
                                     int n2blue, int nfft,
                                     const double costab_data[],
                                     const int costab_size[2],
                                     const double sintab_data[],
                                     const double sintabinv_data[],
                                     creal_T y_data[], int *y_size)
{
  static creal_T fv_data[4000];
  static creal_T fy_data[4000];
  static creal_T wwc_data[1999];
  double b_nt_re_tmp;
  double nt_im;
  double nt_re;
  double twid_im;
  double twid_re;
  int i;
  int ihi;
  int istart;
  int j;
  int ju;
  int k;
  int nInt2;
  int nInt2m1;
  int nRowsD2;
  int nt_re_tmp;
  int rt;
  boolean_T tst;
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    ju = nfft / 2;
    nInt2m1 = (ju + ju) - 1;
    rt = 0;
    wwc_data[ju - 1].re = 1.0;
    wwc_data[ju - 1].im = 0.0;
    nInt2 = ju << 1;
    for (k = 0; k <= ju - 2; k++) {
      istart = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= istart) {
        rt += istart - nInt2;
      } else {
        rt += istart;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)ju;
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = cos(nt_im);
        nt_im = sin(nt_im);
      }
      istart = (ju - k) - 2;
      wwc_data[istart].re = nt_re;
      wwc_data[istart].im = -nt_im;
    }
    istart = nInt2m1 - 1;
    for (k = istart; k >= ju; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    rt = 0;
    wwc_data[nfft - 1].re = 1.0;
    wwc_data[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    for (k = 0; k <= nfft - 2; k++) {
      istart = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= istart) {
        rt += istart - nInt2;
      } else {
        rt += istart;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = cos(nt_im);
        nt_im = sin(nt_im);
      }
      istart = (nfft - k) - 2;
      wwc_data[istart].re = nt_re;
      wwc_data[istart].im = -nt_im;
    }
    istart = nInt2m1 - 1;
    for (k = istart; k >= nfft; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  }
  *y_size = nfft;
  if ((nfft > x_size) && (0 <= nfft - 1)) {
    memset(&y_data[0], 0, nfft * sizeof(creal_T));
  }
  if ((n2blue != 1) && ((nfft & 1) == 0)) {
    d_FFTImplementationCallback_doH(
        x_data, x_size, y_data, x_size, nfft, n2blue, wwc_data, nInt2m1,
        costab_data, costab_size, sintab_data, costab_data, sintabinv_data);
  } else {
    if (nfft <= x_size) {
      rt = nfft;
    } else {
      rt = x_size;
    }
    for (k = 0; k < rt; k++) {
      nt_re_tmp = (nfft + k) - 1;
      y_data[k].re = wwc_data[nt_re_tmp].re * x_data[k];
      y_data[k].im = wwc_data[nt_re_tmp].im * -x_data[k];
    }
    istart = rt + 1;
    if (istart <= nfft) {
      memset(&y_data[istart + -1], 0, ((nfft - istart) + 1) * sizeof(creal_T));
    }
    if ((n2blue > nfft) && (0 <= n2blue - 1)) {
      memset(&fy_data[0], 0, n2blue * sizeof(creal_T));
    }
    if (nfft <= n2blue) {
      istart = nfft;
    } else {
      istart = n2blue;
    }
    nInt2 = n2blue - 2;
    nRowsD2 = n2blue / 2;
    k = nRowsD2 / 2;
    rt = 0;
    ju = 0;
    for (i = 0; i <= istart - 2; i++) {
      fy_data[rt] = y_data[i];
      rt = n2blue;
      tst = true;
      while (tst) {
        rt >>= 1;
        ju ^= rt;
        tst = ((ju & rt) == 0);
      }
      rt = ju;
    }
    fy_data[rt] = y_data[istart - 1];
    if (n2blue > 1) {
      for (i = 0; i <= nInt2; i += 2) {
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
    rt = 2;
    nInt2 = 4;
    ju = ((k - 1) << 2) + 1;
    while (k > 0) {
      for (i = 0; i < ju; i += nInt2) {
        nt_re_tmp = i + rt;
        nt_re = fy_data[nt_re_tmp].re;
        nt_im = fy_data[nt_re_tmp].im;
        fy_data[nt_re_tmp].re = fy_data[i].re - nt_re;
        fy_data[nt_re_tmp].im = fy_data[i].im - nt_im;
        fy_data[i].re += nt_re;
        fy_data[i].im += nt_im;
      }
      istart = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab_data[j];
        twid_im = sintab_data[j];
        i = istart;
        ihi = istart + ju;
        while (i < ihi) {
          nt_re_tmp = i + rt;
          b_nt_re_tmp = fy_data[nt_re_tmp].im;
          nt_im = fy_data[nt_re_tmp].re;
          nt_re = twid_re * nt_im - twid_im * b_nt_re_tmp;
          nt_im = twid_re * b_nt_re_tmp + twid_im * nt_im;
          fy_data[nt_re_tmp].re = fy_data[i].re - nt_re;
          fy_data[nt_re_tmp].im = fy_data[i].im - nt_im;
          fy_data[i].re += nt_re;
          fy_data[i].im += nt_im;
          i += nInt2;
        }
        istart++;
      }
      k /= 2;
      rt = nInt2;
      nInt2 += nInt2;
      ju -= rt;
    }
    c_FFTImplementationCallback_r2b(wwc_data, nInt2m1, n2blue, costab_data,
                                    sintab_data, fv_data, &rt);
    for (istart = 0; istart < n2blue; istart++) {
      twid_im = fy_data[istart].re;
      nt_im = fv_data[istart].im;
      nt_re = fy_data[istart].im;
      twid_re = fv_data[istart].re;
      fy_data[istart].re = twid_im * twid_re - nt_re * nt_im;
      fy_data[istart].im = twid_im * nt_im + nt_re * twid_re;
    }
    d_FFTImplementationCallback_r2b(fy_data, n2blue, n2blue, costab_data,
                                    sintabinv_data, fv_data, &rt);
    for (k = nfft; k <= nInt2m1; k++) {
      nt_im = wwc_data[k - 1].re;
      nt_re = fv_data[k - 1].im;
      twid_re = wwc_data[k - 1].im;
      twid_im = fv_data[k - 1].re;
      istart = k - nfft;
      y_data[istart].re = nt_im * twid_im + twid_re * nt_re;
      y_data[istart].im = nt_im * nt_re - twid_re * twid_im;
    }
  }
}

/* End of code generation (FFTImplementationCallback.c) */
