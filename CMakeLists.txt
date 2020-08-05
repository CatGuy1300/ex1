cmake_minimum_required(VERSION 3.0.0)
project(ex1Test VERSION 0.1.0)

add_executable(ex1Test src/main.c src/Matrix.h src/Matrix.c src/ErrorCode.h src/ErrorCode.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

