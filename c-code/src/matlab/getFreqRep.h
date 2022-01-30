/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * getFreqRep.h
 *
 * Code generation for function 'getFreqRep'
 *
 */

#ifndef GETFREQREP_H
#define GETFREQREP_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void getFreqRep(const short x_data[], const int x_size[1],
                       creal_T y_data[], int y_size[1],
                       creal_T y_shifted_data[], int y_shifted_size[1]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (getFreqRep.h) */
