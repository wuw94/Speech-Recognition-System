#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

struct matrix
{
    int rows;
    int columns;
    float** element
};

struct matrix CopyMatrix(struct matrix A);
struct matrix AddMatrix(struct matrix A, struct matrix B);
struct matrix SubMatrix(struct matrix A, struct matrix B);
struct matrix ScaleMatrix(struct matrix A, float scale);
struct matrix MultiplyMatrix(struct matrix A, struct matrix B);
struct matrix InverseMatrix(struct matrix A);
struct matrix TransposeMatrix(struct matrix A);
struct matrix CreateMatrix(unsigned int rows, unsigned int columns);
void DeleteMatrix(struct matrix A);
void PrintMatrix(struct matrix A);

#endif
