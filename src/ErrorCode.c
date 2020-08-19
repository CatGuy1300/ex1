#include "ErrorCode.h"

bool error_isSuccess(const ErrorCode code) {
    return (bool)(!code); //success in the only code represented by 0
}

const char* error_getErrorMessage(const ErrorCode code) {
    switch (code)
    {
    case ERROR_SUCCESS:
        return "There is no error";
        break;
    case ERROR_NULL:
        return "Input is null";
        break;
    case ERROR_SIZE_CANT_BE_ZERO:
        return "Matrix height and width mustn't be zero";
        break;
    case ERROR_OUT_OF_MATRIX_BOUNDS:
        return "The index you wanted to reach is out of matrix's bounds";
        break;
    case ERROR_ADDITION_IS_NOT_DEFINED:
        return "Addition is not defined - the height and width of matrixes should be equal";
        break;   
    case ERROR_MULTIPLICATION_IS_NOT_DEFINED:
        return "Multiplication is not defined - the width of first matrix must be equals to height of second matrix";
        break;  
    case ERROR_MEMORY:
        return "There is not enough memory";
        break;  
    default:
        return "Unknown code";
        break;
    }
}
