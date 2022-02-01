/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * getFreqRep_initialize.c
 *
 * Code generation for function 'getFreqRep_initialize'
 *
 */

/* Include files */
#include "getFreqRep_initialize.h"
#include "getFreqRep_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void getFreqRep_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_getFreqRep = true;
}

/* End of code generation (getFreqRep_initialize.c) */
