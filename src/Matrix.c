#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Matrix {
  uint32_t height;
  uint32_t width;
  double *array;
} Matrix;

ErrorCode matrix_create(PMatrix *matrix, const uint32_t height,
                        const uint32_t width) {
  // dims must be positive
  if (height == 0 || width == 0) {
    return ERROR_SIZE_CANT_BE_ZERO;
  }

  // allocating memory for struct
  *matrix = (PMatrix)malloc(sizeof(Matrix));
  if (*matrix == NULL) {
    return ERROR_MEMORY;
  }
  (*matrix)->height = height;
  (*matrix)->width = width;

  // creating the array repersenig the matrix
  ((*matrix)->array) = (double *)calloc(height * width, sizeof(double));
  if (((*matrix)->array) == NULL) {
    free(*matrix);
    *matrix = NULL;
    return ERROR_MEMORY;
  }
  return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix *result, CPMatrix source) {
  // checking for null
  if (source == NULL) {
    return ERROR_NULL;
  }

  // creating new matrix with same dimenstions
  ErrorCode error = matrix_create(result, source->height, source->width);
  if (!error_isSuccess(error)) {
    return error;
  }

  // copies data of source to result
  for (uint32_t i = 0; i < source->height; ++i) {
    for (uint32_t j = 0; j < source->width; ++j) {
      ((*result)->array)[i * source->width + j] =
          (source->array)[i * source->width + j];
    }
  }

  return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
  if (matrix != NULL) {
    free(matrix->array);

    // freeing sturct
    free(matrix);
  }
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t *const result) {
  // checking for null
  if (matrix == NULL) {
    return ERROR_NULL;
  }

  // setting result to be height
  *result = matrix->height;

  return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t *const result) {
  // checking for null
  if (matrix == NULL) {
    return ERROR_NULL;
  }

  // setting result to be height
  *result = matrix->width;

  return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, const uint32_t rowIndex,
                          const uint32_t colIndex, const double value) {
  // checking for null
  if (matrix == NULL) {
    return ERROR_NULL;
  }

  // checking for invalid input
  if (rowIndex >= matrix->height || colIndex >= matrix->width) {
    return ERROR_OUT_OF_MATRIX_BOUNDS;
  }

  // setting the value
  (matrix->array)[rowIndex * matrix->width + colIndex] = value;
  return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, const uint32_t rowIndex, const uint32_t colIndex,
                          double *const value) {
  // checking for null
  if (matrix == NULL) {
    return ERROR_NULL;
  }

  // checking for invalid input
  if (rowIndex >= matrix->height || colIndex >= matrix->width) {
    return ERROR_OUT_OF_MATRIX_BOUNDS;
  }

  // setting value to be the value
  *value = (matrix->array)[rowIndex * matrix->width + colIndex];
  return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix *result, CPMatrix lhs, CPMatrix rhs) {
  // checking for null
  if (lhs == NULL || rhs == NULL) {
    return ERROR_NULL;
  }

  // cheking if addition can be done (by definition)
  if (lhs->height != rhs->height || lhs->width != rhs->width) {
    return ERROR_ADDITION_IS_NOT_DEFINED;
  }

  // creating the result matrix
  ErrorCode error = matrix_create(result, lhs->height, lhs->width);
  if (!error_isSuccess(error)) {
    return error;
  }

  // calculating the addition matrix by definition
  for (uint32_t i = 0; i < lhs->height; ++i) {
    for (uint32_t j = 0; j < lhs->width; ++j) {
      ((*result)->array)[i * (*(result))->width + j] =
          (lhs->array)[i * lhs->width + j] + (rhs->array)[i * rhs->width + j];
    }
  }

  return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix *result, CPMatrix lhs, CPMatrix rhs) {
  // checking for null
  if (lhs == NULL || rhs == NULL) {
    return ERROR_NULL;
  }

  // cheking if multiplication can be done (by definition)
  if (lhs->width != rhs->height) {
    return ERROR_MULTIPLICATION_IS_NOT_DEFINED;
  }

  // creating the result matrix
  ErrorCode error = matrix_create(result, lhs->height, rhs->width);
  if (!error_isSuccess(error)) {
    return error;
  }

  // calculating the multiplication matrix by definition
  for (uint32_t i = 0; i < lhs->height; ++i) {
    for (uint32_t j = 0; j < rhs->width; ++j) {
      double product = 0;
      for (uint32_t k = 0; k < lhs->width; ++k) {
        product +=
            (lhs->array)[i * lhs->width + k] * (rhs->array)[k * lhs->width + j];
      }
      ((*result)->array)[i * (*(result))->width + j] = product;
    }
  }

  return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, const double scalar) {
  // checking for null
  if (matrix == NULL) {
    return ERROR_NULL;
  }

  // calculating the multiplication matrix by definition
  for (uint32_t i = 0; i < matrix->height; ++i) {
    for (uint32_t j = 0; j < matrix->width; ++j) {
      (matrix->array)[i * matrix->width + j] *= scalar;
    }
  }

  return ERROR_SUCCESS;
}