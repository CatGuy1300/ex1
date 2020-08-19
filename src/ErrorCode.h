#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    // DON'T CHANGE THIS VALUE!
    ERROR_SUCCESS = 0,
    ERROR_NULL,
    ERROR_SIZE_CANT_BE_ZERO,
    ERROR_OUT_OF_MATRIX_BOUNDS,
    ERROR_ADDITION_IS_NOT_DEFINED,
    ERROR_MULTIPLICATION_IS_NOT_DEFINED,
    ERROR_MEMORY,

} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char *error_getErrorMessage(ErrorCode code);