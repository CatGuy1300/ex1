#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    return !code; //success in the only code represented by 0
}

const char* error_getErrorMessage(ErrorCode code) {
    const char* str;
    switch (code)
    {
    case ERROR_SUCCESS:
        str = "There is no error";
        break;
    case ERROR_NULL:
        str = "Input is null";
        break;
    case ERROR_POSTIVE_INPUT_REQUIRED:
        str = "Matrix height and width must be positive";
        break;
    case ERROR_OUT_OF_MATRIX_BOUNDS:
        str = "The index you wanted to reach is out of matrix's bounds";
        break;
    case ADDITION_IS_NOT_DEFINED:
        str = "Addition is not defined - the height and width of matrixes should be equal";
        break;   
    case MULTIPLICATION_IS_NOT_DEFINED:
        str = "Multiplication is not defined - the width of first matrix must be equals to height of second matrix";
        break;  
    default:
        str = "Unknown code";
        break;
    }
}
