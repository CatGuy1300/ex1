#include "Matrix.h"
#include <stdio.h>

void printMat(PMatrix matrix);

int main() {
    PMatrix matrix;
    matrix_create(&matrix, 3, 2);
    double val;
    matrix_setValue(matrix, 1, 1, 5);
    printMat(matrix);
    return 0;
}

void printMat(PMatrix matrix) {
    double value;
    int height;
    int width;
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