/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_getFreqRep_api.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 27-Jan-2022 13:57:12
 */

#ifndef _CODER_GETFREQREP_API_H
#define _CODER_GETFREQREP_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void getFreqRep(real_T x[2048], real_T y[2048]);

void getFreqRep_api(const mxArray *prhs, const mxArray **plhs);

void getFreqRep_atexit(void);

void getFreqRep_initialize(void);

void getFreqRep_terminate(void);

void getFreqRep_xil_shutdown(void);

void getFreqRep_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_getFreqRep_api.h
 *
 * [EOF]
 */
