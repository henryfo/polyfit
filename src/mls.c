// Name: mls.c
// Description: MLS polynomial fitting functions.
// Author: Henry Forson
// Coyright ©2020 Henry Forson, Melbourne, Florida USA

#include <stdio.h>
#include <stdlib.h>     // calloc()
#include <math.h>       // pow()
#include "mls.h"

//------------------------------------------------
// Function Prototypes
//------------------------------------------------

void showMat( matrix_t *pMat );
matrix_t * makeTranspose( matrix_t *pMat );
matrix_t * makeProduct( matrix_t *pLeft, matrix_t *pRight );
void destroyMatrix( matrix_t *pMat );
matrix_t *createMatrix( int rows, int cols );



//--------------------------------------------------------
// poly()
// Computes polynomial coefficients that best fit a set
// of input points.
//
// The degree of the fitted polynomial is one less than
// the count of elements in the polynomial vector.
//
// Uses matrix algebra of the form:
//              Ax = b
// To solve the MLS equation:
//              (AT)Ax = (AT)b
// where (AT) is the transpose of A.
//
// If the n+1 input points are {(x0, y0), (x1, y1), ... (xn, yn)},
// then the i'th row of A is: {(xi)^0, (xi)^1, ... (xn)^n},
// and the i'th row of b is: {yi}.
//
// Returns 0 if success.
//--------------------------------------------------------
int poly( int pointCount, point_t pointArray[],  int coeffCount, double coeffArray[] )
{
    int rVal = 0;
    int i;

    printf( "pointCount = %d:", pointCount );

    for( i = 0; i < pointCount; i++ )
    {
        printf( " ( %f, %f )", pointArray[i].x, pointArray[i].y );
    }
    printf( "\n");

    printf( "coeffCount = %d:", coeffCount );

    // Make the A matrix:
    matrix_t *pMatA = createMatrix( pointCount, coeffCount );
    for( int r = 0; r < pointCount; r++)
    {
        for( int c = 0; c < coeffCount; c++)
        {
            *(MATRIX_VALUE_PTR(pMatA, r, c)) = pow((pointArray[r].x), (double) c);
        }
    }

    printf( "matA = \n");
    showMat( pMatA );

    // Make the b matrix
    matrix_t *pMatB = createMatrix( pointCount, 1);
     for( int r = 0; r < pointCount; r++)
    {
        *(MATRIX_VALUE_PTR(pMatB, r, 0)) = pointArray[r].y;
    }

    printf( "matB = \n");
    showMat( pMatB );

    // Make the transpose of matrix A
    matrix_t * pMatAT = makeTranspose( pMatA );
    printf( "matAT = \n");
    showMat( pMatAT );

    // Make the product of matrices AT and A:
    matrix_t *pMatATA = makeProduct( pMatAT, pMatA );
    printf( "matAT * matA = \n");
    showMat( pMatATA );

    // make the product of matrices AT and b:
    matrix_t *pMatATb = makeProduct( pMatAT, pMatB );
    printf( "matAT * matB = \n");
    showMat( pMatATb );

    destroyMatrix( pMatATb );
    destroyMatrix( pMatATA );
    destroyMatrix( pMatAT );

    destroyMatrix( pMatA );     // Free matrix A
    destroyMatrix( pMatB );     // Free matrix b
    return rVal;
}


//--------------------------------------------------------
// showmat()
// Printf the contents of a matrix
//--------------------------------------------------------
void showMat( matrix_t *pMat )
{
    for( int r = 0; r < pMat->rows; r++ )
    {
        for( int c = 0; c < pMat->cols; c++)
        {
            printf( "   %f", *MATRIX_VALUE_PTR(pMat, r, c));
        }
        printf( "\n" );
    }
}

//--------------------------------------------------------
// makeTranspose()
// Returns the transpose of a matrix, or NULL.
//
// The caller must free both the allocated matrix
// and its contents array.
//--------------------------------------------------------
matrix_t * makeTranspose( matrix_t *pMat )
{
    matrix_t *rVal = (matrix_t *) calloc(1, sizeof(matrix_t));
    rVal->pContents = (double *) calloc( pMat->rows * pMat->cols, sizeof( double ));
    rVal->cols = pMat->rows;
    rVal->rows = pMat->cols;
    for( int r = 0; r < rVal->rows; r++ )
    {
        for( int c = 0; c < rVal->cols; c++ )
        {
            *MATRIX_VALUE_PTR(rVal, r, c) = *MATRIX_VALUE_PTR(pMat, c, r);
        }
    }
    return rVal;
}

//--------------------------------------------------------
// makeProduct()
// Returns the product of two matrices, or NULL.
//
// The caller must free both the allocated product matrix
// and its contents array.
//--------------------------------------------------------
matrix_t * makeProduct( matrix_t *pLeft, matrix_t *pRight )
{
    matrix_t *rVal = NULL;
    if( (NULL == pLeft) || (NULL == pRight) || (pLeft->cols != pRight->rows) )
    {
        printf( "Illegal parameter passed to makeProduct().\n");
    }
    else
    {
        // Allocate the product matrix.
        rVal = (matrix_t *) calloc(1, sizeof(matrix_t));
        rVal->rows = pLeft->rows;
        rVal->cols = pRight->cols;
        rVal->pContents = (double *) calloc( rVal->rows * rVal->cols, sizeof( double ));

        // Initialize the product matrix contents:
        // product[i,j] = sum{k = 0 .. (pLeft->cols - 1)} (pLeft[i,k] * pRight[ k, j])
        for( int i = 0; i < rVal->rows; i++)
        {
            for( int j = 0; j < rVal->cols; j++ )
            {
                for( int k = 0; k < pLeft->cols; k++)
                {
                    *MATRIX_VALUE_PTR(rVal, i, j) +=
                        (*MATRIX_VALUE_PTR(pLeft, i, k)) * (*MATRIX_VALUE_PTR(pRight, k, j));
                }
            }
        }
    }    
       
    return rVal;
}

//--------------------------------------------------------
// destroyMatrix()
// Frees both the allocated matrix and its contents array.
//--------------------------------------------------------
void destroyMatrix( matrix_t *pMat )
{
    if(NULL != pMat)
    {
        if(NULL != pMat->pContents)
        {
            free(pMat->pContents);
        }
        free( pMat );
    }
}

//--------------------------------------------------------
// createMatrix()
// Allocates the matrix and clears its contents array.
//--------------------------------------------------------
matrix_t *createMatrix( int rows, int cols )
{
    matrix_t *rVal = (matrix_t *) calloc(1, sizeof(matrix_t));
    if(NULL != rVal)
    {
        rVal->rows = rows;
        rVal->cols = cols;
        rVal->pContents = (double *) calloc( rows * cols, sizeof( double ));
        if(NULL == rVal->pContents)
        {
            free( rVal );
        }
    }

    if( NULL == rVal )
    {
        printf("createMatrix() couldn't allocate matrix memory.\n");
    }
    return rVal;
}

 
