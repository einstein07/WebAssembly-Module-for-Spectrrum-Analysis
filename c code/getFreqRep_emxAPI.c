/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: getFreqRep_emxAPI.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 14-Jan-2022 12:29:41
 */

/* Include Files */
#include "getFreqRep_emxAPI.h"
#include "getFreqRep_emxutil.h"
#include "getFreqRep_types.h"
#include <stdlib.h>

/* Function Definitions */
/*
 * Arguments    : int numDimensions
 *                const int *size
 * Return Type  : emxArray_creal_T *
 */
emxArray_creal_T *emxCreateND_creal_T(int numDimensions, const int *size)
{
  emxArray_creal_T *emx;
  int i;
  int numEl;
  emxInit_creal_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data = (creal_T *)calloc((unsigned int)numEl, sizeof(creal_T));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int numDimensions
 *                const int *size
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreateND_real_T(int numDimensions, const int *size)
{
  emxArray_real_T *emx;
  int i;
  int numEl;
  emxInit_real_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data = (double *)calloc((unsigned int)numEl, sizeof(double));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : creal_T *data
 *                int numDimensions
 *                const int *size
 * Return Type  : emxArray_creal_T *
 */
emxArray_creal_T *emxCreateWrapperND_creal_T(creal_T *data, int numDimensions,
                                             const int *size)
{
  emxArray_creal_T *emx;
  int i;
  int numEl;
  emxInit_creal_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : double *data
 *                int numDimensions
 *                const int *size
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreateWrapperND_real_T(double *data, int numDimensions,
                                           const int *size)
{
  emxArray_real_T *emx;
  int i;
  int numEl;
  emxInit_real_T(&emx, numDimensions);
  numEl = 1;
  for (i = 0; i < numDimensions; i++) {
    numEl *= size[i];
    emx->size[i] = size[i];
  }
  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : creal_T *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_creal_T *
 */
emxArray_creal_T *emxCreateWrapper_creal_T(creal_T *data, int rows, int cols)
{
  emxArray_creal_T *emx;
  emxInit_creal_T(&emx, 2);
  emx->size[0] = rows;
  emx->size[1] = cols;
  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = rows * cols;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : double *data
 *                int rows
 *                int cols
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols)
{
  emxArray_real_T *emx;
  emxInit_real_T(&emx, 2);
  emx->size[0] = rows;
  emx->size[1] = cols;
  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = rows * cols;
  emx->canFreeData = false;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_creal_T *
 */
emxArray_creal_T *emxCreate_creal_T(int rows, int cols)
{
  emxArray_creal_T *emx;
  int numEl;
  emxInit_creal_T(&emx, 2);
  emx->size[0] = rows;
  numEl = rows * cols;
  emx->size[1] = cols;
  emx->data = (creal_T *)calloc((unsigned int)numEl, sizeof(creal_T));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : int rows
 *                int cols
 * Return Type  : emxArray_real_T *
 */
emxArray_real_T *emxCreate_real_T(int rows, int cols)
{
  emxArray_real_T *emx;
  int numEl;
  emxInit_real_T(&emx, 2);
  emx->size[0] = rows;
  numEl = rows * cols;
  emx->size[1] = cols;
  emx->data = (double *)calloc((unsigned int)numEl, sizeof(double));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

/*
 * Arguments    : emxArray_creal_T *emxArray
 * Return Type  : void
 */
void emxDestroyArray_creal_T(emxArray_creal_T *emxArray)
{
  emxFree_creal_T(&emxArray);
}

/*
 * Arguments    : emxArray_real_T *emxArray
 * Return Type  : void
 */
void emxDestroyArray_real_T(emxArray_real_T *emxArray)
{
  emxFree_real_T(&emxArray);
}

/*
 * Arguments    : emxArray_creal_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_creal_T(emxArray_creal_T **pEmxArray, int numDimensions)
{
  emxInit_creal_T(pEmxArray, numDimensions);
}

/*
 * Arguments    : emxArray_real_T **pEmxArray
 *                int numDimensions
 * Return Type  : void
 */
void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxInit_real_T(pEmxArray, numDimensions);
}

/*
 * File trailer for getFreqRep_emxAPI.c
 *
 * [EOF]
 */
