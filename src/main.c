#include "Matrix.h"
#include <stdio.h>

void printMat(PMatrix matrix);

int main() {
    PMatrix matrix1 = NULL, matrix2 = NULL, result = NULL;
    ErrorCode code;
    matrix_create(&matrix1, 3, 2);
    matrix_create(&matrix2, 2, 3);
    double val;
    matrix_setValue(matrix1, 1, 1, 5);
    code = matrix_setValue(matrix2, 1, 0, 3);
    printf("%s \n", error_getErrorMessage(code));
    code = matrix_add(&result, matrix1, matrix2);
    printf("%s \n", error_getErrorMessage(code));
    printMat(result);
    matrix_destroy(result);
    code = matrix_multiplyWithScalar(matrix1, 2);
    printf("%s \n", error_getErrorMessage(code));
    printMat(matrix1);
    matrix_destroy(result);
    code = matrix_multiplyMatrices(&result, matrix1, matrix2);
    printf("%s \n", error_getErrorMessage(code));
    printMat(result);
    matrix_destroy(result);
    code = matrix_multiplyMatrices(&result, matrix2, matrix1);
    printf("%s \n", error_getErrorMessage(code));
    printMat(result);
    matrix_destroy(result);
    return 0;
}

void printMat(PMatrix matrix) {
    if (matrix != NULL) {
        double value;
        uint32_t height;
        uint32_t width;
        matrix_getHeight(matrix, &height);
        matrix_getWidth(matrix, &width);
       for (int i = 0; i < height; ++i) {
           for (int j = 0; j < width; ++j) {
                matrix_getValue(matrix, i, j, &value);
                printf("%f, ", value);
            }
            printf("\n");
        }
    }
}