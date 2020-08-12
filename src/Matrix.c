#include "Matrix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Matrix {
    uint32_t height;
    uint32_t width;
    double** array; 
} Matrix;

const uint32_t MIN_INDEX_VAL = 0;

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    //dims must be positive
    if (height < MIN_INDEX_VAL + 1 || width < MIN_INDEX_VAL + 1) {
        return ERROR_NEG_INDEX;
    }

    //better safe than sorry
    *matrix = NULL;

    //allocating memory for struct
    *matrix = (PMatrix) malloc(sizeof(Matrix));
    (*matrix)->height = height;
    (*matrix)->width = width;

     //creating the array repersenig the matrix
    ((*matrix)->array) = (double**) malloc(height * sizeof(double*));
    if (((*matrix)->array) == NULL) {
        return ERROR_MEMORY;
    }

    //creating the arrays inside the array (2d array)
    for (uint32_t i = 0; i < height; ++i) {
        ((*matrix)->array)[i] = (double*) calloc(width, sizeof(double));
        if (((*matrix)->array)[i] == NULL) {
            return ERROR_MEMORY;
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    //checking for null
    if (source == NULL) {
        return ERROR_NULL;
    }

    //creating new matrix with same dimenstions
    ErrorCode error = matrix_create(result, source->height, source->width);
    if (!error_isSuccess(error)) {
        return error; 
    }

    //copies data of source to result
    for (uint32_t i = 0; i < source->height; ++i) {
        for (uint32_t j = 0; j < source->width; ++j) {
            ((*result)->array)[i][j] = (source->array)[i][j];
        }
    }

    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    if (matrix != NULL) {
        //freeing 2d array
    for (uint32_t i = 0; i < matrix->height; ++i) {
            free((matrix->array)[i]);
         }
        free(matrix->array);

        //freeing sturct
        free(matrix);

        //better safe than sorry
        matrix = NULL;
    }
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    //checking for null
    if (matrix == NULL) {
        return ERROR_NULL;
    }

    //setting result to be height
    *result = matrix->height;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    //checking for null
    if (matrix == NULL) {
        return ERROR_NULL;
    }

    //setting result to be height
    *result = matrix->width;

    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    //checking for null
    if (matrix == NULL) {
        return ERROR_NULL;
    }

    //checking for invalid input
    if (rowIndex < MIN_INDEX_VAL || colIndex < MIN_INDEX_VAL) {
        return ERROR_NEG_INDEX;
    }
    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_OUT_OF_MATRIX_BOUNDS;
    }

    //setting the value
    (matrix->array)[rowIndex][colIndex] = value;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
    //checking for null
    if (matrix == NULL) {
        return ERROR_NULL;
    }

    //checking for invalid input
    if (rowIndex < MIN_INDEX_VAL || colIndex < MIN_INDEX_VAL) {
        return ERROR_NEG_INDEX;
    }
    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_OUT_OF_MATRIX_BOUNDS;
    }

    //setting value to be the value
    *value = (matrix->array)[rowIndex][colIndex];
    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    //checking for null
    if (lhs == NULL || rhs == NULL) {
        return ERROR_NULL;
    }

    //cheking if addition can be done (by definition)
    if (lhs->height != rhs->height ||
        lhs->width != rhs->width) {
            return ERROR_ADDITION_IS_NOT_DEFINED;
    }

    //creating the result matrix
    ErrorCode error = matrix_create(result, lhs->height, lhs->width);
    if (!error_isSuccess(error)) {
        return error;
    }
    
    //calculating the addition matrix by definition
    for (uint32_t i = 0; i < lhs->height; ++i) {
        for (uint32_t j = 0; j < lhs->width; ++j) {
            ((*result)->array)[i][j] = (lhs->array)[i][j] + (rhs->array)[i][j];
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    //checking for null
    if (lhs == NULL || rhs == NULL) {
        return ERROR_NULL;
    }

    //cheking if multiplication can be done (by definition)
    if (lhs->width != rhs->height) {
            return ERROR_MULTIPLICATION_IS_NOT_DEFINED;
        }

    //creating the result matrix
    ErrorCode error = matrix_create(result, lhs->height, rhs->width);
    if (!error_isSuccess(error)) {
        return error;
    }

    //calculating the multiplication matrix by definition
    for (uint32_t i = 0; i < lhs->height; ++i) {
        for (uint32_t j = 0; j < rhs->width; ++j) {
            double product = 0;
            for (uint32_t k = 0; k < lhs->width; ++k) {
                product += (lhs->array)[i][k] * (rhs->array)[k][j];
            }
            ((*result)->array)[i][j] = product;
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    //checking for null
    if (matrix == NULL) {
        return ERROR_NULL;
    }

    //calculating the multiplication matrix by definition
    for (uint32_t i = 0; i < matrix->height; ++i) {
        for (uint32_t j = 0; j < matrix->width; ++j) {
            (matrix->array)[i][j] *= scalar;
        }
    }

    return ERROR_SUCCESS;
}