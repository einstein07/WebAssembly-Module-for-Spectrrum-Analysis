/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTImplementationCallback.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 14-Jan-2022 12:29:41
 */

/* Include Files */
#include "FFTImplementationCallback.h"
#include "getFreqRep_emxutil.h"
#include "getFreqRep_types.h"
#include <math.h>

/* Function Declarations */
static void c_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab);

static void c_FFTImplementationCallback_get(const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_real_T *hcostab,
                                            emxArray_real_T *hsintab);

static void d_FFTImplementationCallback_doH(
    const emxArray_real_T *x, emxArray_creal_T *y, int nrowsx, int nRows,
    int nfft, const emxArray_creal_T *wwc, const emxArray_real_T *costab,
    const emxArray_real_T *sintab, const emxArray_real_T *costabinv,
    const emxArray_real_T *sintabinv);

static void d_FFTImplementationCallback_gen(int nRows, emxArray_real_T *costab,
                                            emxArray_real_T *sintab,
                                            emxArray_real_T *sintabinv);

static void d_FFTImplementationCallback_get(
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv,
    emxArray_real_T *hcostab, emxArray_real_T *hsintab,
    emxArray_real_T *hcostabinv, emxArray_real_T *hsintabinv);

static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

static void e_FFTImplementationCallback_get(emxArray_creal_T *y,
                                            const emxArray_creal_T *reconVar1,
                                            const emxArray_creal_T *reconVar2,
                                            const emxArray_int32_T *wrapIndex,
                                            int hnRows);

static void e_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int n1_unsigned,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

static void f_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int n1_unsigned,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 * Return Type  : void
 */
static void c_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab)
{
  emxArray_creal_T *b_y;
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_int32_T *bitrevIndex;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *hcostab;
  emxArray_real_T *hsintab;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  const double *x_data;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  double z;
  double *hcostab_data;
  double *hsintab_data;
  int b_j1;
  int i;
  int iDelta;
  int ihi;
  int istart;
  int iy;
  int ju;
  int k;
  int nRows;
  int nRowsD2;
  int *wrapIndex_data;
  boolean_T tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  y_data = y->data;
  x_data = x->data;
  emxInit_int32_T(&wrapIndex, 2);
  emxInit_real_T(&hcostab, 2);
  emxInit_real_T(&hsintab, 2);
  emxInit_creal_T(&reconVar1, 1);
  emxInit_creal_T(&reconVar2, 1);
  nRows = unsigned_nRows / 2;
  istart = y->size[0];
  if (istart > nRows) {
    istart = nRows;
  }
  ihi = nRows - 2;
  nRowsD2 = nRows / 2;
  k = nRowsD2 / 2;
  c_FFTImplementationCallback_get(costab, sintab, hcostab, hsintab);
  hsintab_data = hsintab->data;
  hcostab_data = hcostab->data;
  b_j1 = reconVar1->size[0];
  reconVar1->size[0] = nRows;
  emxEnsureCapacity_creal_T(reconVar1, b_j1);
  reconVar1_data = reconVar1->data;
  b_j1 = reconVar2->size[0];
  reconVar2->size[0] = nRows;
  emxEnsureCapacity_creal_T(reconVar2, b_j1);
  reconVar2_data = reconVar2->data;
  b_j1 = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = nRows;
  emxEnsureCapacity_int32_T(wrapIndex, b_j1);
  wrapIndex_data = wrapIndex->data;
  for (i = 0; i < nRows; i++) {
    temp_re = sintab_data[i];
    temp_im = costab_data[i];
    reconVar1_data[i].re = temp_re + 1.0;
    reconVar1_data[i].im = -temp_im;
    reconVar2_data[i].re = 1.0 - temp_re;
    reconVar2_data[i].im = temp_im;
    if (i + 1 != 1) {
      wrapIndex_data[i] = (nRows - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  emxInit_int32_T(&bitrevIndex, 1);
  z = (double)unsigned_nRows / 2.0;
  ju = 0;
  iy = 1;
  iDelta = (int)z;
  b_j1 = bitrevIndex->size[0];
  bitrevIndex->size[0] = (int)z;
  emxEnsureCapacity_int32_T(bitrevIndex, b_j1);
  wrapIndex_data = bitrevIndex->data;
  for (b_j1 = 0; b_j1 < iDelta; b_j1++) {
    wrapIndex_data[b_j1] = 0;
  }
  for (b_j1 = 0; b_j1 <= istart - 2; b_j1++) {
    wrapIndex_data[b_j1] = iy;
    iDelta = (int)z;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }
    iy = ju + 1;
  }
  wrapIndex_data[istart - 1] = iy;
  if ((x->size[0] & 1) == 0) {
    tst = true;
    istart = x->size[0];
  } else if (x->size[0] >= unsigned_nRows) {
    tst = true;
    istart = unsigned_nRows;
  } else {
    tst = false;
    istart = x->size[0] - 1;
  }
  if (istart <= unsigned_nRows) {
    iDelta = istart;
  } else {
    iDelta = unsigned_nRows;
  }
  temp_re = (double)iDelta / 2.0;
  if (istart > unsigned_nRows) {
    istart = unsigned_nRows;
  }
  b_j1 = (int)((double)istart / 2.0);
  for (i = 0; i < b_j1; i++) {
    iDelta = i << 1;
    y_data[wrapIndex_data[i] - 1].re = x_data[iDelta];
    y_data[wrapIndex_data[i] - 1].im = x_data[iDelta + 1];
  }
  if (!tst) {
    b_j1 = wrapIndex_data[(int)temp_re] - 1;
    y_data[b_j1].re = x_data[(int)temp_re << 1];
    y_data[b_j1].im = 0.0;
  }
  emxFree_int32_T(&bitrevIndex);
  emxInit_creal_T(&b_y, 1);
  b_j1 = b_y->size[0];
  b_y->size[0] = y->size[0];
  emxEnsureCapacity_creal_T(b_y, b_j1);
  reconVar1_data = b_y->data;
  iDelta = y->size[0];
  for (b_j1 = 0; b_j1 < iDelta; b_j1++) {
    reconVar1_data[b_j1] = y_data[b_j1];
  }
  if (nRows > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp_re_tmp = reconVar1_data[i + 1].re;
      temp_re = reconVar1_data[i + 1].im;
      temp_im = reconVar1_data[i].re;
      twid_re = reconVar1_data[i].im;
      reconVar1_data[i + 1].re = temp_im - temp_re_tmp;
      reconVar1_data[i + 1].im = twid_re - temp_re;
      reconVar1_data[i].re = temp_im + temp_re_tmp;
      reconVar1_data[i].im = twid_re + temp_re;
    }
  }
  iDelta = 2;
  iy = 4;
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += iy) {
      b_j1 = i + iDelta;
      temp_re = reconVar1_data[b_j1].re;
      temp_im = reconVar1_data[b_j1].im;
      reconVar1_data[b_j1].re = reconVar1_data[i].re - temp_re;
      reconVar1_data[b_j1].im = reconVar1_data[i].im - temp_im;
      reconVar1_data[i].re += temp_re;
      reconVar1_data[i].im += temp_im;
    }
    istart = 1;
    for (nRows = k; nRows < nRowsD2; nRows += k) {
      twid_re = hcostab_data[nRows];
      twid_im = hsintab_data[nRows];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        b_j1 = i + iDelta;
        temp_re_tmp = reconVar1_data[b_j1].im;
        temp_im = reconVar1_data[b_j1].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        reconVar1_data[b_j1].re = reconVar1_data[i].re - temp_re;
        reconVar1_data[b_j1].im = reconVar1_data[i].im - temp_im;
        reconVar1_data[i].re += temp_re;
        reconVar1_data[i].im += temp_im;
        i += iy;
      }
      istart++;
    }
    k /= 2;
    iDelta = iy;
    iy += iy;
    ju -= iDelta;
  }
  emxFree_real_T(&hsintab);
  emxFree_real_T(&hcostab);
  b_j1 = y->size[0];
  y->size[0] = b_y->size[0];
  emxEnsureCapacity_creal_T(y, b_j1);
  y_data = y->data;
  iDelta = b_y->size[0];
  for (b_j1 = 0; b_j1 < iDelta; b_j1++) {
    y_data[b_j1] = reconVar1_data[b_j1];
  }
  emxFree_creal_T(&b_y);
  e_FFTImplementationCallback_get(y, reconVar1, reconVar2, wrapIndex, (int)z);
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
}

/*
 * Arguments    : const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_real_T *hcostab
 *                emxArray_real_T *hsintab
 * Return Type  : void
 */
static void c_FFTImplementationCallback_get(const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_real_T *hcostab,
                                            emxArray_real_T *hsintab)
{
  const double *costab_data;
  const double *sintab_data;
  double *hcostab_data;
  double *hsintab_data;
  int hcostab_tmp;
  int hszCostab;
  int i;
  sintab_data = sintab->data;
  costab_data = costab->data;
  hszCostab = costab->size[1] / 2;
  hcostab_tmp = hcostab->size[0] * hcostab->size[1];
  hcostab->size[0] = 1;
  hcostab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostab, hcostab_tmp);
  hcostab_data = hcostab->data;
  hcostab_tmp = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintab, hcostab_tmp);
  hsintab_data = hsintab->data;
  for (i = 0; i < hszCostab; i++) {
    hcostab_tmp = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[hcostab_tmp];
    hsintab_data[i] = sintab_data[hcostab_tmp];
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 *                int nrowsx
 *                int nRows
 *                int nfft
 *                const emxArray_creal_T *wwc
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *costabinv
 *                const emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void d_FFTImplementationCallback_doH(
    const emxArray_real_T *x, emxArray_creal_T *y, int nrowsx, int nRows,
    int nfft, const emxArray_creal_T *wwc, const emxArray_real_T *costab,
    const emxArray_real_T *sintab, const emxArray_real_T *costabinv,
    const emxArray_real_T *sintabinv)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *r;
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_creal_T *ytmp;
  emxArray_cuint8_T *b_y;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *a__1;
  emxArray_real_T *costable;
  emxArray_real_T *hcostabinv;
  emxArray_real_T *hsintab;
  emxArray_real_T *hsintabinv;
  emxArray_real_T *sintable;
  const creal_T *wwc_data;
  creal_T *fv_data;
  creal_T *r1;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  creal_T *ytmp_data;
  cuint8_T *b_y_data;
  const double *x_data;
  double a_im;
  double a_re;
  double b_im;
  double b_re;
  double b_ytmp_re_tmp;
  double ytmp_im_tmp;
  double ytmp_re_tmp;
  double z_tmp;
  double *costable_data;
  double *sintable_data;
  int hnRows;
  int i;
  int k1;
  int loop_ub;
  int u0;
  int *wrapIndex_data;
  boolean_T nxeven;
  wwc_data = wwc->data;
  y_data = y->data;
  x_data = x->data;
  emxInit_cuint8_T(&b_y);
  hnRows = nRows / 2;
  i = b_y->size[0];
  b_y->size[0] = hnRows;
  emxEnsureCapacity_cuint8_T(b_y, i);
  b_y_data = b_y->data;
  if (hnRows > nrowsx) {
    i = b_y->size[0];
    b_y->size[0] = hnRows;
    emxEnsureCapacity_cuint8_T(b_y, i);
    b_y_data = b_y->data;
    for (i = 0; i < hnRows; i++) {
      b_y_data[i].re = 0U;
      b_y_data[i].im = 0U;
    }
  }
  emxInit_creal_T(&ytmp, 1);
  i = ytmp->size[0];
  ytmp->size[0] = b_y->size[0];
  emxEnsureCapacity_creal_T(ytmp, i);
  ytmp_data = ytmp->data;
  loop_ub = b_y->size[0];
  for (i = 0; i < loop_ub; i++) {
    ytmp_data[i].re = 0.0;
    ytmp_data[i].im = b_y_data[i].im;
  }
  emxFree_cuint8_T(&b_y);
  if ((x->size[0] & 1) == 0) {
    nxeven = true;
    u0 = x->size[0];
  } else if (x->size[0] >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x->size[0] - 1;
  }
  emxInit_real_T(&a__1, 2);
  emxInit_int32_T(&wrapIndex, 2);
  emxInit_real_T(&costable, 2);
  emxInit_real_T(&sintable, 2);
  emxInit_real_T(&hsintab, 2);
  emxInit_real_T(&hcostabinv, 2);
  emxInit_real_T(&hsintabinv, 2);
  emxInit_creal_T(&reconVar1, 1);
  emxInit_creal_T(&reconVar2, 1);
  if (u0 > nRows) {
    u0 = nRows;
  }
  d_FFTImplementationCallback_gen(nRows << 1, costable, sintable, a__1);
  sintable_data = sintable->data;
  costable_data = costable->data;
  d_FFTImplementationCallback_get(costab, sintab, costabinv, sintabinv, a__1,
                                  hsintab, hcostabinv, hsintabinv);
  i = reconVar1->size[0];
  reconVar1->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar1, i);
  reconVar1_data = reconVar1->data;
  i = reconVar2->size[0];
  reconVar2->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar2, i);
  reconVar2_data = reconVar2->data;
  i = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = hnRows;
  emxEnsureCapacity_int32_T(wrapIndex, i);
  wrapIndex_data = wrapIndex->data;
  for (loop_ub = 0; loop_ub < hnRows; loop_ub++) {
    i = loop_ub << 1;
    z_tmp = sintable_data[i];
    a_re = costable_data[i];
    reconVar1_data[loop_ub].re = z_tmp + 1.0;
    reconVar1_data[loop_ub].im = -a_re;
    reconVar2_data[loop_ub].re = 1.0 - z_tmp;
    reconVar2_data[loop_ub].im = a_re;
    if (loop_ub + 1 != 1) {
      wrapIndex_data[loop_ub] = (hnRows - loop_ub) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  emxFree_real_T(&sintable);
  emxFree_real_T(&costable);
  z_tmp = (double)u0 / 2.0;
  i = (int)((double)u0 / 2.0);
  for (k1 = 0; k1 < i; k1++) {
    loop_ub = (hnRows + k1) - 1;
    a_re = wwc_data[loop_ub].re;
    a_im = wwc_data[loop_ub].im;
    loop_ub = k1 << 1;
    b_re = x_data[loop_ub];
    b_im = x_data[loop_ub + 1];
    ytmp_data[k1].re = a_re * b_re + a_im * b_im;
    ytmp_data[k1].im = a_re * b_im - a_im * b_re;
  }
  if (!nxeven) {
    loop_ub = (hnRows + (int)z_tmp) - 1;
    a_re = wwc_data[loop_ub].re;
    a_im = wwc_data[loop_ub].im;
    b_re = x_data[(int)z_tmp << 1];
    ytmp_data[(int)z_tmp].re = a_re * b_re + a_im * 0.0;
    ytmp_data[(int)z_tmp].im = a_re * 0.0 - a_im * b_re;
    if ((int)z_tmp + 2 <= hnRows) {
      i = (int)((double)u0 / 2.0) + 2;
      for (loop_ub = i; loop_ub <= hnRows; loop_ub++) {
        ytmp_data[loop_ub - 1].re = 0.0;
        ytmp_data[loop_ub - 1].im = 0.0;
      }
    }
  } else if ((int)z_tmp + 1 <= hnRows) {
    i = (int)((double)u0 / 2.0) + 1;
    for (loop_ub = i; loop_ub <= hnRows; loop_ub++) {
      ytmp_data[loop_ub - 1].re = 0.0;
      ytmp_data[loop_ub - 1].im = 0.0;
    }
  }
  emxInit_creal_T(&fv, 1);
  emxInit_creal_T(&r, 1);
  u0 = (int)((double)nfft / 2.0);
  d_FFTImplementationCallback_r2b(ytmp, u0, a__1, hsintab, fv);
  fv_data = fv->data;
  e_FFTImplementationCallback_r2b(wwc, u0, a__1, hsintab, r);
  r1 = r->data;
  loop_ub = fv->size[0];
  emxFree_real_T(&hsintab);
  emxFree_real_T(&a__1);
  for (i = 0; i < loop_ub; i++) {
    z_tmp = fv_data[i].re;
    a_re = r1[i].im;
    a_im = fv_data[i].im;
    b_re = r1[i].re;
    fv_data[i].re = z_tmp * b_re - a_im * a_re;
    fv_data[i].im = z_tmp * a_re + a_im * b_re;
  }
  f_FFTImplementationCallback_r2b(fv, u0, hcostabinv, hsintabinv, r);
  r1 = r->data;
  i = fv->size[0];
  fv->size[0] = r->size[0];
  emxEnsureCapacity_creal_T(fv, i);
  fv_data = fv->data;
  loop_ub = r->size[0];
  emxFree_real_T(&hsintabinv);
  emxFree_real_T(&hcostabinv);
  for (i = 0; i < loop_ub; i++) {
    fv_data[i] = r1[i];
  }
  emxFree_creal_T(&r);
  i = wwc->size[0];
  for (u0 = hnRows; u0 <= i; u0++) {
    z_tmp = wwc_data[u0 - 1].re;
    a_re = fv_data[u0 - 1].im;
    a_im = wwc_data[u0 - 1].im;
    b_re = fv_data[u0 - 1].re;
    loop_ub = u0 - hnRows;
    ytmp_data[loop_ub].re = z_tmp * b_re + a_im * a_re;
    ytmp_data[loop_ub].im = z_tmp * a_re - a_im * b_re;
  }
  emxFree_creal_T(&fv);
  for (loop_ub = 0; loop_ub < hnRows; loop_ub++) {
    i = wrapIndex_data[loop_ub];
    z_tmp = ytmp_data[loop_ub].re;
    a_re = reconVar1_data[loop_ub].im;
    a_im = ytmp_data[loop_ub].im;
    b_re = reconVar1_data[loop_ub].re;
    b_im = ytmp_data[i - 1].re;
    ytmp_im_tmp = -ytmp_data[i - 1].im;
    ytmp_re_tmp = reconVar2_data[loop_ub].im;
    b_ytmp_re_tmp = reconVar2_data[loop_ub].re;
    y_data[loop_ub].re =
        0.5 * ((z_tmp * b_re - a_im * a_re) +
               (b_im * b_ytmp_re_tmp - ytmp_im_tmp * ytmp_re_tmp));
    y_data[loop_ub].im =
        0.5 * ((z_tmp * a_re + a_im * b_re) +
               (b_im * ytmp_re_tmp + ytmp_im_tmp * b_ytmp_re_tmp));
    i = hnRows + loop_ub;
    y_data[i].re = 0.5 * ((z_tmp * b_ytmp_re_tmp - a_im * ytmp_re_tmp) +
                          (b_im * b_re - ytmp_im_tmp * a_re));
    y_data[i].im = 0.5 * ((z_tmp * ytmp_re_tmp + a_im * b_ytmp_re_tmp) +
                          (b_im * a_re + ytmp_im_tmp * b_re));
  }
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
  emxFree_creal_T(&ytmp);
}

/*
 * Arguments    : int nRows
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void d_FFTImplementationCallback_gen(int nRows, emxArray_real_T *costab,
                                            emxArray_real_T *sintab,
                                            emxArray_real_T *sintabinv)
{
  emxArray_real_T *b_costab;
  emxArray_real_T *b_sintab;
  emxArray_real_T *b_sintabinv;
  emxArray_real_T *costab1q;
  double e;
  double *b_costab_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int i;
  int k;
  int n;
  int nd2;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab_data = costab1q->data;
  costab_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab_data[k] = sin(e * (double)(n - k));
  }
  emxInit_real_T(&b_costab, 2);
  emxInit_real_T(&b_sintab, 2);
  emxInit_real_T(&b_sintabinv, 2);
  costab_data[n] = 0.0;
  n = costab1q->size[1] - 1;
  nd2 = (costab1q->size[1] - 1) << 1;
  i = b_costab->size[0] * b_costab->size[1];
  b_costab->size[0] = 1;
  b_costab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(b_costab, i);
  b_costab_data = b_costab->data;
  i = b_sintab->size[0] * b_sintab->size[1];
  b_sintab->size[0] = 1;
  b_sintab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(b_sintab, i);
  sintab_data = b_sintab->data;
  b_costab_data[0] = 1.0;
  sintab_data[0] = 0.0;
  i = b_sintabinv->size[0] * b_sintabinv->size[1];
  b_sintabinv->size[0] = 1;
  b_sintabinv->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(b_sintabinv, i);
  sintabinv_data = b_sintabinv->data;
  for (k = 0; k < n; k++) {
    sintabinv_data[k + 1] = costab_data[(n - k) - 1];
  }
  i = costab1q->size[1];
  for (k = i; k <= nd2; k++) {
    sintabinv_data[k] = costab_data[k - n];
  }
  for (k = 0; k < n; k++) {
    b_costab_data[k + 1] = costab_data[k + 1];
    sintab_data[k + 1] = -costab_data[(n - k) - 1];
  }
  i = costab1q->size[1];
  for (k = i; k <= nd2; k++) {
    b_costab_data[k] = -costab_data[nd2 - k];
    sintab_data[k] = -costab_data[k - n];
  }
  emxFree_real_T(&costab1q);
  i = costab->size[0] * costab->size[1];
  costab->size[0] = 1;
  costab->size[1] = b_costab->size[1];
  emxEnsureCapacity_real_T(costab, i);
  costab_data = costab->data;
  nd2 = b_costab->size[1];
  for (i = 0; i < nd2; i++) {
    costab_data[i] = b_costab_data[i];
  }
  emxFree_real_T(&b_costab);
  i = sintab->size[0] * sintab->size[1];
  sintab->size[0] = 1;
  sintab->size[1] = b_sintab->size[1];
  emxEnsureCapacity_real_T(sintab, i);
  costab_data = sintab->data;
  nd2 = b_sintab->size[1];
  for (i = 0; i < nd2; i++) {
    costab_data[i] = sintab_data[i];
  }
  emxFree_real_T(&b_sintab);
  i = sintabinv->size[0] * sintabinv->size[1];
  sintabinv->size[0] = 1;
  sintabinv->size[1] = b_sintabinv->size[1];
  emxEnsureCapacity_real_T(sintabinv, i);
  costab_data = sintabinv->data;
  nd2 = b_sintabinv->size[1];
  for (i = 0; i < nd2; i++) {
    costab_data[i] = sintabinv_data[i];
  }
  emxFree_real_T(&b_sintabinv);
}

/*
 * Arguments    : const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *costabinv
 *                const emxArray_real_T *sintabinv
 *                emxArray_real_T *hcostab
 *                emxArray_real_T *hsintab
 *                emxArray_real_T *hcostabinv
 *                emxArray_real_T *hsintabinv
 * Return Type  : void
 */
static void d_FFTImplementationCallback_get(
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv,
    emxArray_real_T *hcostab, emxArray_real_T *hsintab,
    emxArray_real_T *hcostabinv, emxArray_real_T *hsintabinv)
{
  const double *costab_data;
  const double *costabinv_data;
  const double *sintab_data;
  const double *sintabinv_data;
  double *hcostab_data;
  double *hcostabinv_data;
  double *hsintab_data;
  double *hsintabinv_data;
  int hcostab_tmp;
  int hszCostab;
  int i;
  sintabinv_data = sintabinv->data;
  costabinv_data = costabinv->data;
  sintab_data = sintab->data;
  costab_data = costab->data;
  hszCostab = costab->size[1] / 2;
  hcostab_tmp = hcostab->size[0] * hcostab->size[1];
  hcostab->size[0] = 1;
  hcostab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostab, hcostab_tmp);
  hcostab_data = hcostab->data;
  hcostab_tmp = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintab, hcostab_tmp);
  hsintab_data = hsintab->data;
  hcostab_tmp = hcostabinv->size[0] * hcostabinv->size[1];
  hcostabinv->size[0] = 1;
  hcostabinv->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostabinv, hcostab_tmp);
  hcostabinv_data = hcostabinv->data;
  hcostab_tmp = hsintabinv->size[0] * hsintabinv->size[1];
  hsintabinv->size[0] = 1;
  hsintabinv->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintabinv, hcostab_tmp);
  hsintabinv_data = hsintabinv->data;
  for (i = 0; i < hszCostab; i++) {
    hcostab_tmp = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[hcostab_tmp];
    hsintab_data[i] = sintab_data[hcostab_tmp];
    hcostabinv_data[i] = costabinv_data[hcostab_tmp];
    hsintabinv_data[i] = sintabinv_data[hcostab_tmp];
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y)
{
  emxArray_creal_T *b_y;
  const creal_T *x_data;
  creal_T *b_y_data;
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
  int ihi;
  int istart;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  boolean_T tst;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  emxInit_creal_T(&b_y, 1);
  ju = b_y->size[0];
  b_y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(b_y, ju);
  y_data = b_y->data;
  if (unsigned_nRows > x->size[0]) {
    ju = b_y->size[0];
    b_y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(b_y, ju);
    y_data = b_y->data;
    for (ju = 0; ju < unsigned_nRows; ju++) {
      y_data[ju].re = 0.0;
      y_data[ju].im = 0.0;
    }
  }
  ju = y->size[0];
  y->size[0] = b_y->size[0];
  emxEnsureCapacity_creal_T(y, ju);
  b_y_data = y->data;
  iy = b_y->size[0];
  for (ju = 0; ju < iy; ju++) {
    b_y_data[ju] = y_data[ju];
  }
  iDelta2 = x->size[0];
  if (iDelta2 > unsigned_nRows) {
    iDelta2 = unsigned_nRows;
  }
  istart = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    b_y_data[iy] = x_data[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  b_y_data[iy] = x_data[iDelta2 - 1];
  ju = b_y->size[0];
  b_y->size[0] = y->size[0];
  emxEnsureCapacity_creal_T(b_y, ju);
  y_data = b_y->data;
  iy = y->size[0];
  for (ju = 0; ju < iy; ju++) {
    y_data[ju] = b_y_data[ju];
  }
  if (unsigned_nRows > 1) {
    for (i = 0; i <= istart; i += 2) {
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
  ju = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ju; i += iDelta2) {
      b_temp_re_tmp = i + iy;
      temp_re = y_data[b_temp_re_tmp].re;
      temp_im = y_data[b_temp_re_tmp].im;
      y_data[b_temp_re_tmp].re = y_data[i].re - temp_re;
      y_data[b_temp_re_tmp].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = istart;
      ihi = istart + ju;
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
      istart++;
    }
    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    ju -= iy;
  }
  ju = y->size[0];
  y->size[0] = b_y->size[0];
  emxEnsureCapacity_creal_T(y, ju);
  b_y_data = y->data;
  iy = b_y->size[0];
  for (ju = 0; ju < iy; ju++) {
    b_y_data[ju] = y_data[ju];
  }
  emxFree_creal_T(&b_y);
}

/*
 * Arguments    : emxArray_creal_T *y
 *                const emxArray_creal_T *reconVar1
 *                const emxArray_creal_T *reconVar2
 *                const emxArray_int32_T *wrapIndex
 *                int hnRows
 * Return Type  : void
 */
static void e_FFTImplementationCallback_get(emxArray_creal_T *y,
                                            const emxArray_creal_T *reconVar1,
                                            const emxArray_creal_T *reconVar2,
                                            const emxArray_int32_T *wrapIndex,
                                            int hnRows)
{
  const creal_T *reconVar1_data;
  const creal_T *reconVar2_data;
  creal_T *y_data;
  double b_temp1_re_tmp;
  double b_temp2_re_tmp;
  double b_y_re_tmp;
  double c_temp1_re_tmp;
  double c_temp2_re_tmp;
  double c_y_re_tmp;
  double d_y_re_tmp;
  double temp1_im_tmp;
  double temp1_re_tmp;
  double temp2_im_tmp;
  double temp2_re_tmp;
  double y_re_tmp;
  const int *wrapIndex_data;
  int b_i;
  int i;
  int i1;
  int iterVar;
  wrapIndex_data = wrapIndex->data;
  reconVar2_data = reconVar2->data;
  reconVar1_data = reconVar1->data;
  y_data = y->data;
  iterVar = hnRows / 2;
  temp1_re_tmp = y_data[0].re;
  temp1_im_tmp = y_data[0].im;
  y_data[0].re = 0.5 * ((temp1_re_tmp * reconVar1_data[0].re -
                         temp1_im_tmp * reconVar1_data[0].im) +
                        (temp1_re_tmp * reconVar2_data[0].re -
                         -temp1_im_tmp * reconVar2_data[0].im));
  y_data[0].im = 0.5 * ((temp1_re_tmp * reconVar1_data[0].im +
                         temp1_im_tmp * reconVar1_data[0].re) +
                        (temp1_re_tmp * reconVar2_data[0].im +
                         -temp1_im_tmp * reconVar2_data[0].re));
  y_data[hnRows].re = 0.5 * ((temp1_re_tmp * reconVar2_data[0].re -
                              temp1_im_tmp * reconVar2_data[0].im) +
                             (temp1_re_tmp * reconVar1_data[0].re -
                              -temp1_im_tmp * reconVar1_data[0].im));
  y_data[hnRows].im = 0.5 * ((temp1_re_tmp * reconVar2_data[0].im +
                              temp1_im_tmp * reconVar2_data[0].re) +
                             (temp1_re_tmp * reconVar1_data[0].im +
                              -temp1_im_tmp * reconVar1_data[0].re));
  for (i = 2; i <= iterVar; i++) {
    temp1_re_tmp = y_data[i - 1].re;
    temp1_im_tmp = y_data[i - 1].im;
    b_i = wrapIndex_data[i - 1];
    temp2_re_tmp = y_data[b_i - 1].re;
    temp2_im_tmp = y_data[b_i - 1].im;
    y_re_tmp = reconVar1_data[i - 1].im;
    b_y_re_tmp = reconVar1_data[i - 1].re;
    c_y_re_tmp = reconVar2_data[i - 1].im;
    d_y_re_tmp = reconVar2_data[i - 1].re;
    y_data[i - 1].re =
        0.5 * ((temp1_re_tmp * b_y_re_tmp - temp1_im_tmp * y_re_tmp) +
               (temp2_re_tmp * d_y_re_tmp - -temp2_im_tmp * c_y_re_tmp));
    y_data[i - 1].im =
        0.5 * ((temp1_re_tmp * y_re_tmp + temp1_im_tmp * b_y_re_tmp) +
               (temp2_re_tmp * c_y_re_tmp + -temp2_im_tmp * d_y_re_tmp));
    i1 = (hnRows + i) - 1;
    y_data[i1].re =
        0.5 * ((temp1_re_tmp * d_y_re_tmp - temp1_im_tmp * c_y_re_tmp) +
               (temp2_re_tmp * b_y_re_tmp - -temp2_im_tmp * y_re_tmp));
    y_data[i1].im =
        0.5 * ((temp1_re_tmp * c_y_re_tmp + temp1_im_tmp * d_y_re_tmp) +
               (temp2_re_tmp * y_re_tmp + -temp2_im_tmp * b_y_re_tmp));
    c_temp2_re_tmp = reconVar1_data[b_i - 1].im;
    b_temp2_re_tmp = reconVar1_data[b_i - 1].re;
    b_temp1_re_tmp = reconVar2_data[b_i - 1].im;
    c_temp1_re_tmp = reconVar2_data[b_i - 1].re;
    y_data[b_i - 1].re =
        0.5 *
        ((temp2_re_tmp * b_temp2_re_tmp - temp2_im_tmp * c_temp2_re_tmp) +
         (temp1_re_tmp * c_temp1_re_tmp - -temp1_im_tmp * b_temp1_re_tmp));
    y_data[b_i - 1].im =
        0.5 *
        ((temp2_re_tmp * c_temp2_re_tmp + temp2_im_tmp * b_temp2_re_tmp) +
         (temp1_re_tmp * b_temp1_re_tmp + -temp1_im_tmp * c_temp1_re_tmp));
    b_i = (b_i + hnRows) - 1;
    y_data[b_i].re =
        0.5 *
        ((temp2_re_tmp * c_temp1_re_tmp - temp2_im_tmp * b_temp1_re_tmp) +
         (temp1_re_tmp * b_temp2_re_tmp - -temp1_im_tmp * c_temp2_re_tmp));
    y_data[b_i].im =
        0.5 *
        ((temp2_re_tmp * b_temp1_re_tmp + temp2_im_tmp * c_temp1_re_tmp) +
         (temp1_re_tmp * c_temp2_re_tmp + -temp1_im_tmp * b_temp2_re_tmp));
  }
  if (iterVar != 0) {
    temp1_re_tmp = y_data[iterVar].re;
    temp1_im_tmp = y_data[iterVar].im;
    y_re_tmp = reconVar1_data[iterVar].im;
    b_y_re_tmp = reconVar1_data[iterVar].re;
    c_y_re_tmp = reconVar2_data[iterVar].im;
    d_y_re_tmp = reconVar2_data[iterVar].re;
    b_temp2_re_tmp = temp1_re_tmp * d_y_re_tmp;
    b_temp1_re_tmp = temp1_re_tmp * b_y_re_tmp;
    y_data[iterVar].re = 0.5 * ((b_temp1_re_tmp - temp1_im_tmp * y_re_tmp) +
                                (b_temp2_re_tmp - -temp1_im_tmp * c_y_re_tmp));
    c_temp1_re_tmp = temp1_re_tmp * c_y_re_tmp;
    c_temp2_re_tmp = temp1_re_tmp * y_re_tmp;
    y_data[iterVar].im = 0.5 * ((c_temp2_re_tmp + temp1_im_tmp * b_y_re_tmp) +
                                (c_temp1_re_tmp + -temp1_im_tmp * d_y_re_tmp));
    b_i = hnRows + iterVar;
    y_data[b_i].re = 0.5 * ((b_temp2_re_tmp - temp1_im_tmp * c_y_re_tmp) +
                            (b_temp1_re_tmp - -temp1_im_tmp * y_re_tmp));
    y_data[b_i].im = 0.5 * ((c_temp1_re_tmp + temp1_im_tmp * d_y_re_tmp) +
                            (c_temp2_re_tmp + -temp1_im_tmp * b_y_re_tmp));
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void e_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
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

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void f_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
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

/*
 * Arguments    : const emxArray_real_T *x
 *                int n2blue
 *                int nfft
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void c_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *b_fv;
  emxArray_creal_T *fv;
  emxArray_creal_T *wwc;
  creal_T *b_fv_data;
  creal_T *fv_data;
  creal_T *wwc_data;
  creal_T *y_data;
  const double *x_data;
  double b_re_tmp;
  double nt_im;
  double nt_re;
  double re_tmp;
  int i;
  int k;
  int minNrowsNx;
  int nInt2;
  int nInt2m1;
  int nRows;
  int rt;
  x_data = x->data;
  emxInit_creal_T(&wwc, 1);
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    nRows = nfft / 2;
    nInt2m1 = (nRows + nRows) - 1;
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nRows - 1].re = 1.0;
    wwc_data[nRows - 1].im = 0.0;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      minNrowsNx = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= minNrowsNx) {
        rt += minNrowsNx - nInt2;
      } else {
        rt += minNrowsNx;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nRows;
      if (nt_im == 0.0) {
        nt_re = 1.0;
        nt_im = 0.0;
      } else {
        nt_re = cos(nt_im);
        nt_im = sin(nt_im);
      }
      i = (nRows - k) - 2;
      wwc_data[i].re = nt_re;
      wwc_data[i].im = -nt_im;
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nRows; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
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
      i = (nfft - k) - 2;
      wwc_data[i].re = nt_re;
      wwc_data[i].im = -nt_im;
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nfft; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  }
  i = y->size[0];
  y->size[0] = nfft;
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0];
    y->size[0] = nfft;
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    for (i = 0; i < nfft; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  emxInit_creal_T(&fv, 1);
  emxInit_creal_T(&b_fv, 1);
  if ((n2blue != 1) && ((nfft & 1) == 0)) {
    d_FFTImplementationCallback_doH(x, y, x->size[0], nfft, n2blue, wwc, costab,
                                    sintab, costab, sintabinv);
  } else {
    minNrowsNx = x->size[0];
    if (nfft <= minNrowsNx) {
      minNrowsNx = nfft;
    }
    for (k = 0; k < minNrowsNx; k++) {
      nInt2m1 = (nfft + k) - 1;
      y_data[k].re = wwc_data[nInt2m1].re * x_data[k];
      y_data[k].im = wwc_data[nInt2m1].im * -x_data[k];
    }
    i = minNrowsNx + 1;
    for (k = i; k <= nfft; k++) {
      y_data[k - 1].re = 0.0;
      y_data[k - 1].im = 0.0;
    }
    e_FFTImplementationCallback_r2b(y, n2blue, costab, sintab, fv);
    fv_data = fv->data;
    e_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, b_fv);
    i = b_fv->size[0];
    b_fv->size[0] = fv->size[0];
    emxEnsureCapacity_creal_T(b_fv, i);
    b_fv_data = b_fv->data;
    minNrowsNx = fv->size[0];
    for (i = 0; i < minNrowsNx; i++) {
      nt_re = fv_data[i].re;
      nt_im = b_fv_data[i].im;
      re_tmp = fv_data[i].im;
      b_re_tmp = b_fv_data[i].re;
      b_fv_data[i].re = nt_re * b_re_tmp - re_tmp * nt_im;
      b_fv_data[i].im = nt_re * nt_im + re_tmp * b_re_tmp;
    }
    f_FFTImplementationCallback_r2b(b_fv, n2blue, costab, sintabinv, fv);
    fv_data = fv->data;
    i = wwc->size[0];
    for (k = nfft; k <= i; k++) {
      nt_re = wwc_data[k - 1].re;
      nt_im = fv_data[k - 1].im;
      re_tmp = wwc_data[k - 1].im;
      b_re_tmp = fv_data[k - 1].re;
      minNrowsNx = k - nfft;
      y_data[minNrowsNx].re = nt_re * b_re_tmp + re_tmp * nt_im;
      y_data[minNrowsNx].im = nt_re * nt_im - re_tmp * b_re_tmp;
    }
  }
  emxFree_creal_T(&b_fv);
  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : int nRows
 *                boolean_T useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
void c_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int i;
  int k;
  int n;
  int nd2;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    sintabinv_data = sintabinv->data;
    for (k = 0; k < n; k++) {
      sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }
  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void c_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *b_y;
  creal_T *b_y_data;
  creal_T *y_data;
  const double *x_data;
  int i;
  int u0;
  x_data = x->data;
  i = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    for (i = 0; i < n1_unsigned; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  if (n1_unsigned != 1) {
    c_FFTImplementationCallback_doH(x, y, n1_unsigned, costab, sintab);
  } else {
    emxInit_creal_T(&b_y, 1);
    u0 = x->size[0];
    if (u0 > 1) {
      u0 = 1;
    }
    y_data[0].re = x_data[u0 - 1];
    y_data[0].im = 0.0;
    i = b_y->size[0];
    b_y->size[0] = y->size[0];
    emxEnsureCapacity_creal_T(b_y, i);
    b_y_data = b_y->data;
    u0 = y->size[0];
    for (i = 0; i < u0; i++) {
      b_y_data[i] = y_data[i];
    }
    i = y->size[0];
    y->size[0] = b_y->size[0];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    u0 = b_y->size[0];
    for (i = 0; i < u0; i++) {
      y_data[i] = b_y_data[i];
    }
    emxFree_creal_T(&b_y);
  }
}

/*
 * File trailer for FFTImplementationCallback.c
 *
 * [EOF]
 */
