#include "Matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Matrix {
    int height;
    int width;
    double** array; 
} Matrix;

const int MIN_INDEX_VAL = 0;

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    if (height < MIN_INDEX_VAL || width < MIN_INDEX_VAL) {
        return ERROR_NEG_INDEX;
    }

    *matrix = NULL;
    *matrix = (PMatrix) malloc(sizeof(Matrix));
    (*matrix)->height = height;
    (*matrix)->width = width;
    ((*matrix)->array) = (double**) malloc(height * sizeof(double*));

    //creating the array repersenig the matrix
    if (((*matrix)->array) == NULL) {
        return ERROR_MEMORY;
    }

    //
    for (int i = 0; i < height; ++i) {
        ((*matrix)->array)[i] = (double*) calloc(width, sizeof(double));
        if (((*matrix)->array)[i] == NULL) {
            return ERROR_MEMORY;
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    if (source == NULL) {
        return ERROR_NULL;
    }
    //creating new matrix with same dimenstions
    ErrorCode error = matrix_create(result, source->height, source->width);
    if (!error_isSuccess(error)) {
        return error; 
    }
    //copies data of source to result using
    for (int i = 0; i < source->height; ++i) {
        for (int j = 0; j < source->width; ++j) {
            ((*result)->array)[i][j] = (source->array)[i][j];
        }
    }
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    for (int i = 0; i < matrix->height; ++i) {
        free((matrix->array)[i]);
    }
    free(matrix->array);
    free(matrix);
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    if (matrix == NULL) {
        return ERROR_NULL;
    }
    *result = matrix->height;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    if (matrix == NULL) {
        return ERROR_NULL;
    }
    *result = matrix->width;
    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    if (matrix == NULL) {
        return ERROR_NULL;
    }
    if (rowIndex < MIN_INDEX_VAL || colIndex < MIN_INDEX_VAL) {
        return ERROR_NEG_INDEX;
    }
    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_OUT_OF_MATRIX_BOUNDS;
    }
    (matrix->array)[rowIndex][colIndex] = value;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
    if (matrix == NULL) {
        return ERROR_NULL;
    }
    if (rowIndex < MIN_INDEX_VAL || colIndex < MIN_INDEX_VAL) {
        return ERROR_NEG_INDEX;
    }
    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_OUT_OF_MATRIX_BOUNDS;
    }
    *value = (matrix->array)[rowIndex][colIndex];
    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (lhs->height != rhs->height ||
        lhs->width != rhs->width) {
            return ERROR_ADDITION_IS_NOT_DEFINED;
        }
    ErrorCode error = matrix_create(result, lhs->height, lhs->width);
    if (!error_isSuccess(error)) {
        return error;
    }
    
    for (int i = 0; i < lhs->height; ++i) {
        for (int j = 0; j < lhs->width; ++j) {
            ((*result)->array)[i][j] = (lhs->array)[i][j] + (rhs->array)[i][j];
        }
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (lhs->width != rhs->height) {
            return ERROR_MULTIPLICATION_IS_NOT_DEFINED;
        }
    ErrorCode error = matrix_create(result, lhs->height, rhs->width);
    if (!error_isSuccess(error)) {
        return error;
    }

    for (int i = 0; i < lhs->height; ++i) {
        for (int j = 0; j < rhs->width; ++j) {
            double product = 0;
            for (int k = 0; k < lhs->width; ++k) {
                product += (lhs->array)[i][k] * (rhs->array)[k][j];
            }
            ((*result)->array)[i][j] = product;
        }
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    return ERROR_SUCCESS;
}