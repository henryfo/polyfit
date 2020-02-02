// file: mls.h
// Description:	Header file for MLS polynomial fitting.
// Author: Henry Forson
// Copyright 2020 Henry Forson, Melbourne, FL

#ifndef MLS_H
#define MLS_H

//------------------------------------------------
// TYPEDEFS
//------------------------------------------------

// Structure of a point.
typedef struct point_s
{
	double x;
	double y;
} point_t;


// Structure of a vector.
typedef struct vector_s
{
	int	count;
	double * pElement;
} vector_t;

// Structure of a list of points.
typedef struct pointlist_s
{
	int count;
	point_t *pPoints;
} pointlist_t;

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
// Function Prototypes
//------------------------------------------------

//--------------------------------------------------------
// poly()
// Computes polynomial coefficients that best fit a set
// of input points.
//
// The degree of the fitted polynomial is one less than
// the count of coefficients in the coefficients array.
//
// Returns 0 if success.
//--------------------------------------------------------
int poly( int pointCount, point_t pointArray[],  int coeffCount, double coeffArray[] );

//--------------------------------------------------------
// showPoly()
// Prints the coefficients of a polynomial.
//--------------------------------------------------------
void showPoly( int coeffCount, double coeffArray[] );



#endif	// MLS_H
