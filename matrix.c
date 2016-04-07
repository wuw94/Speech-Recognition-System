#include "matrix.h"

/*
 * AddMatrix
 * - adds the values of two matrices together
 * - make sure they are the same number of rows and columns
 */
struct matrix AddMatrix(struct matrix A, struct matrix B)
{
    if ((A.rows != B.rows) || (A.columns != B.columns))
        printf("Error in AddMatrix(): Matrix dimensions must match.\n");
        
    struct matrix R;
    R.rows = A.rows;
    R.columns = A.columns;
    
    R.element = (float **) malloc(A.rows * sizeof(float *));
    
    for (unsigned int i = 0; i < A.rows; i++)
        R.element[i] = (float *) malloc(A.columns * sizeof(float));
    
    for (unsigned int i = 0; i < A.rows; i++)
        for (unsigned int j = 0; j < A.columns; j++)
            R.element[i][j] = A.element[i][j] + B.element[i][j];

    return R;
}

struct matrix SubMatrix(struct matrix A, struct matrix B)
{
    if ((A.rows != B.rows) || (A.columns != B.columns))
        printf("Error in SubMatrix(): Matrix dimensions must match.\n%d %d %d %d",A.rows,A.columns,B.rows,B.columns);
    
    struct matrix R;
    R.rows = A.rows;
    R.columns = A.columns;

    R.element = (float **) malloc(A.rows * sizeof(float *));
    
    for (unsigned int i = 0; i < A.rows; i++)
        R.element[i] = (float *) malloc(A.columns * sizeof(float));
    
    for (unsigned int i = 0; i < A.rows; i++)
        for (unsigned int j = 0; j < A.columns; j++)
            R.element[i][j] = A.element[i][j] - B.element[i][j];
    
    return R;
}

struct matrix ScaleMatrix(struct matrix A, float scale)
{
    struct matrix R;
    R.rows = A.rows;
    R.columns = A.columns;

    R.element = (float **) malloc(A.rows * sizeof(float *));
    
    for (unsigned int i = 0; i < A.rows; i++)
        R.element[i] = (float *) malloc(A.columns * sizeof(float));
    
    for (unsigned int i = 0; i < A.rows; i++)
        for (unsigned int j = 0; j < A.columns; j++)
            R.element[i][j] = A.element[i][j] * scale;
    
    return R;
}

struct matrix MultiplyMatrix(struct matrix A, struct matrix B)
{
    if(A.columns != B.rows)
        printf("Error in MultiplyMatrix(): Matrix A columns must match matrix B rows.\n");
    
    struct matrix R;
    R.rows = A.rows;
    R.columns = B.columns;
    
    R.element = (float **) malloc(A.rows * sizeof(float *));
    
    for(unsigned int i = 0; i < A.rows; i++)
        R.element[i] = (float *) malloc(B.columns * sizeof(float));
    
    for (unsigned int i = 0; i < A.rows; ++i)
        for (unsigned int j = 0; j < B.columns; ++j)
            for (unsigned int k = 0; k < B.rows; ++k)
                R.element[i][j] += A.element[i][k] * B.element[k][j];
    
    return R;
}

struct matrix InverseMatrix(struct matrix A)
{
    if (A.rows != A.columns)
        printf("Error in InverseMatrix(): Columns must match rows.\n");
    
    struct matrix I;
    I.rows = A.rows;
    I.columns = A.rows;

    float temp;
    
    I.element = (float **) malloc(A.rows * sizeof(float *));
    for(unsigned int i = 0; i < A.rows; i++)
        I.element[i] = (float *) malloc(A.rows * sizeof(float));
    
    for(unsigned int i = 0; i < A.rows; i++)
        for(unsigned int j = 0; j < A.rows; j++)
            if(i == j)
                I.element[i][j] = 1;
            else
                I.element[i][j] = 0;
    
    for(unsigned int k = 0; k < A.rows; k++)
    {
        temp = A.element[k][k];
        for(unsigned int j = 0; j < A.rows; j++)
        {
            A.element[k][j] /= temp;
            I.element[k][j] /= temp;
        }
        for(unsigned int i = 0; i < A.rows; i++)
        {
            temp = A.element[i][k];
            for(unsigned int j = 0; j < A.rows; j++)
            {
                if(i == k)
                    break;
                A.element[i][j] -= A.element[k][j] * temp;
                I.element[i][j] -= I.element[k][j] * temp;
            }
        }
    }
    
    return I;
    
}

struct matrix TransposeMatrix(struct matrix A)
{    
    struct matrix T;
    T.rows = A.columns;
    T.columns = A.rows;
    
    T.element = (float **) malloc(A.columns * sizeof(float *));
    
    for(unsigned int i = 0; i < A.columns; i++)
        T.element[i] = (float *) malloc(A.rows * sizeof(float));
    
    for (unsigned int i = 0; i < A.rows; ++i)
        for (unsigned int j = 0; j < A.columns; ++j)
            T.element[j][i] = A.element[i][j];
    
    return T;
    
}

struct matrix CreateMatrix(unsigned int rows, unsigned int columns)
{
    struct matrix M;
    M.rows = rows;
    M.columns = columns;
    
    M.element = (float **) malloc(rows * sizeof(float *));
    
    for (unsigned int i = 0; i < rows; i++)
        M.element[i] = (float *) malloc(columns * sizeof(float));
    
    
    for (unsigned int i = 0; i < rows; i++)
        for (unsigned int j = 0; j < columns; j++)
            M.element[i][j] = 0.0;
    
    return M;
}

void DeleteMatrix(struct matrix A)
{
    for (unsigned int i = 0; i < A.rows; i++)
        free(A.element[i]);
    
    free(A.element);
}

void PrintMatrix(struct matrix A)
{
    for(unsigned int i = 0; i < A.rows; i++)
    {
        for(unsigned int j = 0; j < A.columns; j++)
            printf("%f\t", A.element[i][j]);
        printf("\n");
    }
}