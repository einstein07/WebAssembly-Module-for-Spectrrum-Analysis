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
static void c_FFTImplementationCallback_doH(
    const double x[100000], creal_T y[100000], const creal_T wwc[99999],
    const double costab[131073], const double sintab[131073],
    const double costabinv[131073], const double sintabinv[131073]);

static void c_FFTImplementationCallback_gen(double costab[100001],
                                            double sintab[100001],
                                            double sintabinv[100001]);

static void c_FFTImplementationCallback_r2b(const creal_T x[50000],
                                            const double costab[65536],
                                            const double sintab[65536],
                                            creal_T y[131072]);

static void d_FFTImplementationCallback_r2b(const creal_T x[99999],
                                            const double costab[65536],
                                            const double sintab[65536],
                                            creal_T y[131072]);

static void e_FFTImplementationCallback_r2b(const creal_T x[131072],
                                            const double costab[65536],
                                            const double sintab[65536],
                                            creal_T y[131072]);

/* Function Definitions */
static void c_FFTImplementationCallback_doH(
    const double x[100000], creal_T y[100000], const creal_T wwc[99999],
    const double costab[131073], const double sintab[131073],
    const double costabinv[131073], const double sintabinv[131073])
{
  static creal_T b_fv[131072];
  static creal_T fv[131072];
  static creal_T reconVar1[50000];
  static creal_T reconVar2[50000];
  static creal_T ytmp[50000];
  static double a__1[100001];
  static double costable[100001];
  static double sintable[100001];
  static double hcostab[65536];
  static double hcostabinv[65536];
  static double hsintab[65536];
  static double hsintabinv[65536];
  static int wrapIndex[50000];
  double b_im;
  double b_re;
  double b_re_tmp;
  double b_ytmp_re_tmp;
  double c_ytmp_re_tmp;
  double re_tmp;
  double ytmp_im_tmp;
  double ytmp_re_tmp;
  int hcostab_tmp;
  int i;
  c_FFTImplementationCallback_gen(costable, sintable, a__1);
  for (i = 0; i < 65536; i++) {
    hcostab_tmp = ((i + 1) << 1) - 2;
    hcostab[i] = costab[hcostab_tmp];
    hsintab[i] = sintab[hcostab_tmp];
    hcostabinv[i] = costabinv[hcostab_tmp];
    hsintabinv[i] = sintabinv[hcostab_tmp];
  }
  for (i = 0; i < 50000; i++) {
    hcostab_tmp = i << 1;
    re_tmp = sintable[hcostab_tmp];
    b_re_tmp = costable[hcostab_tmp];
    reconVar1[i].re = re_tmp + 1.0;
    reconVar1[i].im = -b_re_tmp;
    reconVar2[i].re = 1.0 - re_tmp;
    reconVar2[i].im = b_re_tmp;
    if (i + 1 != 1) {
      wrapIndex[i] = 50001 - i;
    } else {
      wrapIndex[0] = 1;
    }
    b_re = x[hcostab_tmp];
    b_im = x[hcostab_tmp + 1];
    re_tmp = wwc[i + 49999].re;
    b_re_tmp = wwc[i + 49999].im;
    ytmp[i].re = re_tmp * b_re + b_re_tmp * b_im;
    ytmp[i].im = re_tmp * b_im - b_re_tmp * b_re;
  }
  c_FFTImplementationCallback_r2b(ytmp, hcostab, hsintab, fv);
  d_FFTImplementationCallback_r2b(wwc, hcostab, hsintab, b_fv);
  for (hcostab_tmp = 0; hcostab_tmp < 131072; hcostab_tmp++) {
    b_re = fv[hcostab_tmp].re;
    b_im = b_fv[hcostab_tmp].im;
    re_tmp = fv[hcostab_tmp].im;
    b_re_tmp = b_fv[hcostab_tmp].re;
    b_fv[hcostab_tmp].re = b_re * b_re_tmp - re_tmp * b_im;
    b_fv[hcostab_tmp].im = b_re * b_im + re_tmp * b_re_tmp;
  }
  e_FFTImplementationCallback_r2b(b_fv, hcostabinv, hsintabinv, fv);
  for (hcostab_tmp = 0; hcostab_tmp < 50000; hcostab_tmp++) {
    re_tmp = wwc[hcostab_tmp + 49999].re;
    b_re_tmp = fv[hcostab_tmp + 49999].im;
    b_re = wwc[hcostab_tmp + 49999].im;
    b_im = fv[hcostab_tmp + 49999].re;
    ytmp[hcostab_tmp].re = re_tmp * b_im + b_re * b_re_tmp;
    ytmp[hcostab_tmp].im = re_tmp * b_re_tmp - b_re * b_im;
  }
  for (i = 0; i < 50000; i++) {
    b_re = ytmp[i].re;
    b_im = reconVar1[i].im;
    re_tmp = ytmp[i].im;
    b_re_tmp = reconVar1[i].re;
    hcostab_tmp = wrapIndex[i];
    ytmp_re_tmp = ytmp[hcostab_tmp - 1].re;
    ytmp_im_tmp = -ytmp[hcostab_tmp - 1].im;
    b_ytmp_re_tmp = reconVar2[i].im;
    c_ytmp_re_tmp = reconVar2[i].re;
    y[i].re =
        0.5 * ((b_re * b_re_tmp - re_tmp * b_im) +
               (ytmp_re_tmp * c_ytmp_re_tmp - ytmp_im_tmp * b_ytmp_re_tmp));
    y[i].im =
        0.5 * ((b_re * b_im + re_tmp * b_re_tmp) +
               (ytmp_re_tmp * b_ytmp_re_tmp + ytmp_im_tmp * c_ytmp_re_tmp));
    y[i + 50000].re = 0.5 * ((b_re * c_ytmp_re_tmp - re_tmp * b_ytmp_re_tmp) +
                             (ytmp_re_tmp * b_re_tmp - ytmp_im_tmp * b_im));
    y[i + 50000].im = 0.5 * ((b_re * b_ytmp_re_tmp + re_tmp * c_ytmp_re_tmp) +
                             (ytmp_re_tmp * b_im + ytmp_im_tmp * b_re_tmp));
  }
}

static void c_FFTImplementationCallback_gen(double costab[100001],
                                            double sintab[100001],
                                            double sintabinv[100001])
{
  static double costab1q[50001];
  double b_sintabinv_tmp;
  double sintabinv_tmp;
  int k;
  costab1q[0] = 1.0;
  for (k = 0; k < 25000; k++) {
    costab1q[k + 1] = cos(3.1415926535897928E-5 * ((double)k + 1.0));
  }
  for (k = 0; k < 24999; k++) {
    costab1q[k + 25001] =
        sin(3.1415926535897928E-5 * (50000.0 - ((double)k + 25001.0)));
  }
  costab1q[50000] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 50000; k++) {
    sintabinv_tmp = costab1q[49999 - k];
    sintabinv[k + 1] = sintabinv_tmp;
    b_sintabinv_tmp = costab1q[k + 1];
    sintabinv[k + 50001] = b_sintabinv_tmp;
    costab[k + 1] = b_sintabinv_tmp;
    sintab[k + 1] = -sintabinv_tmp;
    costab[k + 50001] = -sintabinv_tmp;
    sintab[k + 50001] = -b_sintabinv_tmp;
  }
}

static void c_FFTImplementationCallback_r2b(const creal_T x[50000],
                                            const double costab[65536],
                                            const double sintab[65536],
                                            creal_T y[131072])
{
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_temp_re_tmp;
  int i;
  int iheight;
  int ihi;
  int istart;
  int iy;
  int j;
  int ju;
  int k;
  boolean_T tst;
  memset(&y[0], 0, 131072U * sizeof(creal_T));
  iy = 0;
  ju = 0;
  for (i = 0; i < 49999; i++) {
    y[iy] = x[i];
    iy = 131072;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y[iy] = x[49999];
  for (i = 0; i <= 131070; i += 2) {
    temp_re_tmp = y[i + 1].re;
    temp_im = y[i + 1].im;
    temp_re = y[i].re;
    twid_re = y[i].im;
    y[i + 1].re = temp_re - temp_re_tmp;
    y[i + 1].im = twid_re - temp_im;
    y[i].re = temp_re + temp_re_tmp;
    y[i].im = twid_re + temp_im;
  }
  iy = 2;
  ju = 4;
  k = 32768;
  iheight = 131069;
  while (k > 0) {
    for (i = 0; i < iheight; i += ju) {
      b_temp_re_tmp = i + iy;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < 65536; j += k) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y[b_temp_re_tmp].im;
        temp_im = y[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y[b_temp_re_tmp].re = y[i].re - temp_re;
        y[b_temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ju;
      }
      istart++;
    }
    k /= 2;
    iy = ju;
    ju += ju;
    iheight -= iy;
  }
}

static void d_FFTImplementationCallback_r2b(const creal_T x[99999],
                                            const double costab[65536],
                                            const double sintab[65536],
                                            creal_T y[131072])
{
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_temp_re_tmp;
  int i;
  int iheight;
  int ihi;
  int istart;
  int iy;
  int j;
  int ju;
  int k;
  boolean_T tst;
  memset(&y[0], 0, 131072U * sizeof(creal_T));
  iy = 0;
  ju = 0;
  for (i = 0; i < 99998; i++) {
    y[iy] = x[i];
    iy = 131072;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y[iy] = x[99998];
  for (i = 0; i <= 131070; i += 2) {
    temp_re_tmp = y[i + 1].re;
    temp_im = y[i + 1].im;
    temp_re = y[i].re;
    twid_re = y[i].im;
    y[i + 1].re = temp_re - temp_re_tmp;
    y[i + 1].im = twid_re - temp_im;
    y[i].re = temp_re + temp_re_tmp;
    y[i].im = twid_re + temp_im;
  }
  iy = 2;
  ju = 4;
  k = 32768;
  iheight = 131069;
  while (k > 0) {
    for (i = 0; i < iheight; i += ju) {
      b_temp_re_tmp = i + iy;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < 65536; j += k) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y[b_temp_re_tmp].im;
        temp_im = y[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y[b_temp_re_tmp].re = y[i].re - temp_re;
        y[b_temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ju;
      }
      istart++;
    }
    k /= 2;
    iy = ju;
    ju += ju;
    iheight -= iy;
  }
}

static void e_FFTImplementationCallback_r2b(const creal_T x[131072],
                                            const double costab[65536],
                                            const double sintab[65536],
                                            creal_T y[131072])
{
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int b_temp_re_tmp;
  int i;
  int iheight;
  int ihi;
  int istart;
  int iy;
  int j;
  int ju;
  int k;
  boolean_T tst;
  iy = 0;
  ju = 0;
  for (i = 0; i < 131071; i++) {
    y[iy] = x[i];
    iy = 131072;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  y[iy] = x[131071];
  for (i = 0; i <= 131070; i += 2) {
    temp_re_tmp = y[i + 1].re;
    temp_im = y[i + 1].im;
    temp_re = y[i].re;
    twid_re = y[i].im;
    y[i + 1].re = temp_re - temp_re_tmp;
    y[i + 1].im = twid_re - temp_im;
    y[i].re = temp_re + temp_re_tmp;
    y[i].im = twid_re + temp_im;
  }
  iy = 2;
  ju = 4;
  k = 32768;
  iheight = 131069;
  while (k > 0) {
    for (i = 0; i < iheight; i += ju) {
      b_temp_re_tmp = i + iy;
      temp_re = y[b_temp_re_tmp].re;
      temp_im = y[b_temp_re_tmp].im;
      y[b_temp_re_tmp].re = y[i].re - temp_re;
      y[b_temp_re_tmp].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }
    istart = 1;
    for (j = k; j < 65536; j += k) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        b_temp_re_tmp = i + iy;
        temp_re_tmp = y[b_temp_re_tmp].im;
        temp_im = y[b_temp_re_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y[b_temp_re_tmp].re = y[i].re - temp_re;
        y[b_temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ju;
      }
      istart++;
    }
    k /= 2;
    iy = ju;
    ju += ju;
    iheight -= iy;
  }
  for (iy = 0; iy < 131072; iy++) {
    y[iy].re *= 7.62939453125E-6;
    y[iy].im *= 7.62939453125E-6;
  }
}

void c_FFTImplementationCallback_dob(const double x[100000],
                                     const double costab[131073],
                                     const double sintab[131073],
                                     const double sintabinv[131073],
                                     creal_T y[100000])
{
  static creal_T wwc[99999];
  double nt_im;
  double nt_re;
  int b_y;
  int k;
  int rt;
  rt = 0;
  wwc[49999].re = 1.0;
  wwc[49999].im = 0.0;
  for (k = 0; k < 49999; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (100000 - rt <= b_y) {
      rt = (b_y + rt) - 100000;
    } else {
      rt += b_y;
    }
    nt_im = -3.1415926535897931 * (double)rt / 50000.0;
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = cos(nt_im);
      nt_im = sin(nt_im);
    }
    wwc[49998 - k].re = nt_re;
    wwc[49998 - k].im = -nt_im;
  }
  for (k = 49998; k >= 0; k--) {
    wwc[k + 50000] = wwc[49998 - k];
  }
  c_FFTImplementationCallback_doH(x, y, wwc, costab, sintab, costab, sintabinv);
}

/* End of code generation (FFTImplementationCallback.c) */
