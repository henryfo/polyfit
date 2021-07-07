// Name: polyfit.c
// Description: Simple polynomial fitting functions.
// Author: Henry M. Forson, Melbourne, Florida USA

//------------------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2020 Henry M. Forson
// Copyright (c) 2021 Stephen P. Morgan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//------------------------------------------------------------------------------------

#include <assert.h>
#include <math.h>       // pow()
#include <stdbool.h>    // bool
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>      // printf()
#include <stdlib.h>     // calloc()
#include <string.h>     // strlen()

#include "polyfit.h"

// Define SHOW_MATRIX to display intermediate matrix values:
// #define SHOW_MATRIX 1

// Structure of a matrix.
typedef struct matrix_s
{
	int	rows;
	int	cols;
	double *pContents;
} matrix_t;

// MACRO to access a value with a matrix.
#define MATRIX_VALUE_PTR( pA, row, col )  (&(((pA)->pContents)[ (row * (pA)->cols) + col]))

#ifdef SHOW_MATRIX
#define showMatrix( x ) do {\
    printf( "   @%d: " #x " =\n", __LINE__ ); \
    reallyShowMatrix( x ); \
    printf( "\n" ); \
} while( 0 )
#else   // SHOW_MATRIX
#define showMatrix( x )
#endif   // SHOW_MATRIX


//------------------------------------------------
// Private Function Prototypes
//------------------------------------------------

static matrix_t *   createMatrix( int rows, int cols );
static void         destroyMatrix( matrix_t *pMat );
#ifdef SHOW_MATRIX
static void         reallyShowMatrix( matrix_t *pMat );
#endif  // SHOW_MATRIX
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
int polyfit( int pointCount, const double *xValues, const double *yValues, int coefficientCount, double *coefficientResults )
{
    int rVal = 0;
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

    showMatrix( pMatA );

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

    // Make the transpose of matrix A
    matrix_t * pMatAT = createTranspose( pMatA );
    if( NULL == pMatAT )
    {
        return -3;
    }

    showMatrix( pMatAT );

    // Make the product of matrices AT and A:
    matrix_t *pMatATA = createProduct( pMatAT, pMatA );
    if( NULL == pMatATA )
    {
        return -3;
    }

     showMatrix( pMatATA );

    // Make the product of matrices AT and b:
    matrix_t *pMatATB = createProduct( pMatAT, pMatB );
    if( NULL == pMatATB )
    {
        return -3;
    }

    showMatrix( pMatATB );

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
            showMatrix( pMatATA );
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

                    // showMatrix( pMatATA );
                   
                }
                *MATRIX_VALUE_PTR(pMatATB, r, 0) -=  *MATRIX_VALUE_PTR(pMatATB, pr, 0) * factor;

                showMatrix( pMatATB );
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

    showMatrix( pMatATA );

    showMatrix( pMatATB );

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
// polyToString()
// Produces a string representation of a polynomial from
// its coefficients.
// Returns 0 on success.
//--------------------------------------------------------
int polyToString( char *stringBuffer, size_t stringBufferSz, int coeffCount, double *coefficients )
{
    bool isThisTheFirstTermShown = true;
    if( (NULL == stringBuffer) || (NULL == coefficients) )
    {
        return -1;  // NULL pointer passed as a parameter
    }
        if( (0 == stringBufferSz) || (coeffCount <= 0) )
    {
        return -2;  // parameter out of range.
    }

    stringBuffer[0] = 0;

    for( int i = 0; i < coeffCount; i++)
    {
        int exponent = (coeffCount - 1) - i;
        bool isTermPrintable = (coefficients[i] != 0.0);
        if( isTermPrintable )
        {
            int stringIndex = strlen( stringBuffer );           // Index of where to write the next term.
            char *pNext = &(stringBuffer[ stringIndex ]);       // Pointer to where to write the next term.
            int remainingSize = stringBufferSz - stringIndex;   // Space left in buffer.
 
            if( 0 == exponent )
            {
                snprintf( pNext, remainingSize, "%s%.12g", isThisTheFirstTermShown ? "" : " + ", coefficients[ i ] );
            }
            else if( 1 == exponent)
            {
                snprintf( pNext, remainingSize, "%s(%.12g * x)", isThisTheFirstTermShown ? "" : " + ", coefficients[ i ] );
            }
            else
            {
                snprintf( pNext, remainingSize, "%s(%.12g * x^%d)", isThisTheFirstTermShown ? "" : " + ", coefficients[i], exponent );
            }
            isThisTheFirstTermShown = false;
        }
    }
    return 0;
}

//--------------------------------------------------------
// polyMultiply()
// Returns a value of x multiplied by itself n times, e.g.,
// x^2 or x^3.
//--------------------------------------------------------
static inline double
polyMultiply(double x, int n)
{
	if (n == 0) {
		return 1.0;
	}
	else {
		return x * polyMultiply(x, n - 1);
	}
}

//--------------------------------------------------------
// polyError()
// Evaluates the error of a polynomial vs. the original
// data used to regress the polynomial, at a point <x,y>.
// Retiurns the error (squared) at that point.
//--------------------------------------------------------
double
polyError(int pc, const double* x, const double* y, int cc, const double* cr)
{
	double error = 0.0;

	for (int n = 0; n < pc; n++) {
		double x_val = x[n];
		double y_val = y[n];

		double y_est = 0.0;

		for (int i = 0; i < cc; i++) {
			y_est += polyMultiply(x_val, cc - i - 1) * *(cr + i);
		}

		double y_trm = y_est - y_val;

		error += y_trm * y_trm;
	}

	return error;
}

//--------------------------------------------------------
// polyEvaluate()
// Evaluates a polynomial at x.
// Returns the value of the polynomial at x.
//--------------------------------------------------------
double
polyEvaluate(int cc, const double* cr, double x)
{
	double value = 0.0;

	for (int i = 0; i < cc; i++) {
		double coeff = *(cr + i);
		value += coeff * polyMultiply(x, cc - i - 1);
	}

	return value;
}


//--------------------------------------------------------
// polyRoot()
//
// Determins a real root of a given polynomial in the range
// [x0..x1].  Iterates no more than *iteration times or until the
// difference between values in the iteration is less than *epsilon.
// Uses the secant iterative root-finding method.  If epsilon is
// NULL, uses an epsilon valu eof 0.000001; otherwise, returns the
// actual epsilon found.  If iterations is NULL, uses an iterations
// value of 16; otherwise, returns the actual number of iterations.
//
// Returns the vaue of one real root in the range (if any). Note
// that, if *epsilon or *iterations is hit, the value returned will
// not be valid. Thus, those values should be checked on exit.
// Call this function with epsilon and/or iterations set to NULL
// at your own risk.
//--------------------------------------------------------

// Value to limit number of iterations in polyRoot.

double
polyRoot(int cc, const double* cr, double x0, double x1,
		int* iterations, double* epsilon)
{
	double x0_init = x0;
	double x1_init = x1;
	double my_epsilon = (epsilon == NULL) ? 0.000001 : *epsilon;
	int my_iterations = (iterations == NULL) ? 16 : *iterations;
	int count;

	double x2 = (x0 + x1) / 2.0;

	for (int i = 0; i < my_iterations; i++) {
		x2 = x1 - polyEvaluate(cc, cr, x1) * (x1 - x0) /
					(polyEvaluate(cc, cr, x1) - polyEvaluate(cc, cr, x0));

		x0 = x1;
		x1 = x2;

		if (x2 < x0_init || x2 > x1_init ||
			fabs(x0 - x2) < my_epsilon || fabs(x1 - x2) < my_epsilon) {
			count = i + 1;
			break;
		}
	}

	if (epsilon != NULL) {
		*epsilon = fabs(x0 - x2) < fabs(x1 - x2) ?
			fabs(x0 - x2) : fabs(x1 - x2);
	}

	if (iterations != NULL) {
		*iterations = count;
	}

	return x2;
}

//--------------------------------------------------------
// polyDerivative().
// Computes the derivative of the given polynomial.
// Returns the derivative polynomial in cr_out. The
// derivative polynomial will have (cc - 1) terms.
// Note that cr_out must be supplied by the caller.
//--------------------------------------------------------
void
polyDerivative(int cc, const double* cr_in, double* cr_out)
{
	for (int i = 0; i < cc - 1; i++) {
		*(cr_out + i) = *(cr_in + i) * (double)(cc - i - 1);
	}
}

//=========================================================
//      Private function definitions
//=========================================================

#ifdef SHOW_MATRIX
//--------------------------------------------------------
// reallyShowMatrix()
// Printf the contents of a matrix
//--------------------------------------------------------
static void reallyShowMatrix( matrix_t *pMat )
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
#endif  // SHOW_MATRIX

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

 
