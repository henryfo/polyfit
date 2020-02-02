// Name: polyfit.c
// Description: Simple polynomial fitting functions.
// Author: Henry Forson
// Coyright ©2020 Henry Forson, Melbourne, Florida USA

#include <stdio.h>      // printf()
#include <stdlib.h>     // calloc()
#include <math.h>       // pow()
#include <stdbool.h>    // bool
#include "polyfit.h"


// Structure of a matrix.
typedef struct matrix_s
{
	int	rows;
	int	cols;
	double *pContents;
} matrix_t;

// MACRO to access a value with a matrix.
#define MATRIX_VALUE_PTR( pA, row, col )  (&(((pA)->pContents)[ (row * (pA)->cols) + col]))


//------------------------------------------------
// Private Function Prototypes
//------------------------------------------------

static matrix_t *   createMatrix( int rows, int cols );
static void         destroyMatrix( matrix_t *pMat );
static void         showMatrix( matrix_t *pMat );
static matrix_t *   createTranspose( matrix_t *pMat );
static matrix_t *   createProduct( matrix_t *pLeft, matrix_t *pRight );


//=========================================================
//      Global function definitions
//=========================================================


//--------------------------------------------------------
// polyfit()
// Computes polynomial coefficients that best fit a set
// of input points.
//
// The degree of the fitted polynomial is one less than
// the count of elements in the polynomial vector.
//
// Uses matrix algebra of the form:
//              A * x = b
// To solve the MLS equation:
//              (AT) * A * x = (AT) * b
// where (AT) is the transpose of A.
//
// If the n+1 input points are {(x0, y0), (x1, y1), ... (xn, yn)},
// then the i'th row of A is: {(xi)^0, (xi)^1, ... (xn)^n},
// and the i'th row of b is: {yi}.
//
// Returns   0 if success, 
//          -1 if passed a NULL pointer,
//          -2 if (pointCount < coefficientCount),
//          -3 if unable to allocate memory,
//          -4 if unable to solve equations.
//--------------------------------------------------------
//int polyfit( int pointCount, point_t pointArray[],  int coeffCount, double coeffArray[] )
int polyfit( int pointCount, double *xValues, double *yValues, int coefficientCount, double *coefficientResults )
{
    int rVal = 0;
    int i;
    int degree = coefficientCount - 1;

    // Check that the input pointers aren't null.
    if( (NULL == xValues) || (NULL == yValues) || (NULL == coefficientResults) )
    {
        return -1;
    }
    // Check that pointCount >= coefficientCount.
    if(pointCount < coefficientCount)
    {
        return -2;
    }

    // printf( "pointCount = %d:", pointCount );

    // for( i = 0; i < pointCount; i++ )
    // {
    //     printf( " ( %f, %f )", xValues[i], yValues[i] );
    // }
    // printf( "\n");

    // printf( "coefficientCount = %d\n", coefficientCount );

    // Make the A matrix:
    matrix_t *pMatA = createMatrix( pointCount, coefficientCount );
    if( NULL == pMatA)
    {
        return -3;
    }

    for( int r = 0; r < pointCount; r++)
    {
        for( int c = 0; c < coefficientCount; c++)
        {
            *(MATRIX_VALUE_PTR(pMatA, r, c)) = pow((xValues[r]), (double) (degree -c));
        }
    }

    // printf( "matA = \n");
    // showMatrix( pMatA );

    // Make the b matrix
    matrix_t *pMatB = createMatrix( pointCount, 1);
    if( NULL == pMatB )
    {
        return -3;
    }

    for( int r = 0; r < pointCount; r++)
    {
        *(MATRIX_VALUE_PTR(pMatB, r, 0)) = yValues[r];
    }

    // printf( "matB = \n");
    // showMatrix( pMatB );

    // Make the transpose of matrix A
    matrix_t * pMatAT = createTranspose( pMatA );
    if( NULL == pMatAT )
    {
        return -3;
    }

    // printf( "matAT = \n");
    // showMatrix( pMatAT );

    // Make the product of matrices AT and A:
    matrix_t *pMatATA = createProduct( pMatAT, pMatA );
    if( NULL == pMatATA )
    {
        return -3;
    }

    // printf( "(matAT * matA) =\n");
    // showMatrix( pMatATA );

    // Make the product of matrices AT and b:
    matrix_t *pMatATB = createProduct( pMatAT, pMatB );
    if( NULL == pMatATB )
    {
        return -3;
    }
    // printf( "(matAT * matB) = \n");
    // showMatrix( pMatATB );

    // Now we need to solve the system of linear equations,
    // (AT)Ax = (AT)b for "x", the coefficients of the polynomial.

    for( int c = 0; c < pMatATA->cols; c++ )
    {
        int pr = c;     // pr is the pivot row.
        double prVal = *MATRIX_VALUE_PTR(pMatATA, pr, c);
        // If it's zero, we can't solve the equations.
        if( 0.0 == prVal )
        {
            // printf( "Unable to solve equations, pr = %d, c = %d.\n", pr, c );
            // showMatrix( pMatATA );
            rVal = -4;
            break;
        }
        for( int r = 0; r < pMatATA->rows; r++)
        {
            if( r != pr )
            {
                double targetRowVal = *MATRIX_VALUE_PTR(pMatATA, r, c);
                double factor = targetRowVal / prVal;
                for( int c2 = 0; c2 < pMatATA->cols; c2++ )
                {
                    *MATRIX_VALUE_PTR(pMatATA, r, c2) -=  *MATRIX_VALUE_PTR(pMatATA, pr, c2) * factor; 
                    // printf( "c = %d, pr = %d, r = %d, c2=%d, targetRowVal = %f, prVal = %f, factor = %f.\n",
                    //         c, pr, r, c2, targetRowVal, prVal, factor );
                    // printf( "reduced matATA =\n");
                    // showMatrix( pMatATA );
                   
                }
                *MATRIX_VALUE_PTR(pMatATB, r, 0) -=  *MATRIX_VALUE_PTR(pMatATB, pr, 0) * factor;
                // printf( "reduced matATb =\n");
                // showMatrix( pMatATB );
            }
        }
    }
    for( int c = 0; c < pMatATA->cols; c++ )
    {
        int pr = c;
        // now, pr is the pivot row.
        double prVal = *MATRIX_VALUE_PTR(pMatATA, pr, c);
        *MATRIX_VALUE_PTR(pMatATA, pr, c) /= prVal;
        *MATRIX_VALUE_PTR(pMatATB, pr, 0) /= prVal;
    }

    // printf( "reduced matATA =\n");
    // showMatrix( pMatATA );

    // printf( "reduced matATb =\n");
    // showMatrix( pMatATB );

    for( int i = 0; i < coefficientCount; i++)
    {
        coefficientResults[i] = *MATRIX_VALUE_PTR(pMatATB, i, 0);
    }

    
    destroyMatrix( pMatATB );
    destroyMatrix( pMatATA );
    destroyMatrix( pMatAT );

    destroyMatrix( pMatA );
    destroyMatrix( pMatB );
    return rVal;
}

//--------------------------------------------------------
// showPoly()
// Prints the coefficients of a polynomial.
//--------------------------------------------------------
//void showPoly( int coeffCount, double coeffArray[] )
void showPoly( int coeffCount, double *coefficients )
{
    bool isThisTheFirstTermShown = true;
    for( int i = 0; i < coeffCount; i++)
    {
        int exponent = (coeffCount - 1) - i;
        bool isTermPrintable = (coefficients[i] != 0.0);
        if( isTermPrintable )
        {
            if( 0 == exponent )
            {
                printf( "%s%f", isThisTheFirstTermShown ? "" : " + ", coefficients[ i ] );
            }
            else if( 1 == exponent)
            {
                printf( "%s(%f * x)", isThisTheFirstTermShown ? "" : " + ", coefficients[ i ] );
            }
            else
            {
                printf( "%s(%f * x^%d)", isThisTheFirstTermShown ? "" : " + ", coefficients[i], exponent );
            }
            isThisTheFirstTermShown = false;
        }
    }
    printf("\n");
}

//=========================================================
//      Private function definitions
//=========================================================


//--------------------------------------------------------
// showmat()
// Printf the contents of a matrix
//--------------------------------------------------------
static void showMatrix( matrix_t *pMat )
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
// createTranspose()
// Returns the transpose of a matrix, or NULL.
//
// The caller must free both the allocated matrix
// and its contents array.
//--------------------------------------------------------
static matrix_t * createTranspose( matrix_t *pMat )
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
// createProduct()
// Returns the product of two matrices, or NULL.
//
// The caller must free both the allocated product matrix
// and its contents array.
//--------------------------------------------------------
static matrix_t * createProduct( matrix_t *pLeft, matrix_t *pRight )
{
    matrix_t *rVal = NULL;
    if( (NULL == pLeft) || (NULL == pRight) || (pLeft->cols != pRight->rows) )
    {
        printf( "Illegal parameter passed to createProduct().\n");
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
static void destroyMatrix( matrix_t *pMat )
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
static matrix_t *createMatrix( int rows, int cols )
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
            rVal = NULL;
        }
    }

    return rVal;
}

 
