// file: polyfit.h
// Description:	Header file for MLS polynomial fitting.
// Author: Henry Forson
// Copyright 2020 Henry Forson, Melbourne, FL

#ifndef POLYFIT_H
#define POLYFIT_H

//------------------------------------------------
// TYPEDEFS
//------------------------------------------------

// Structure of a point.
typedef struct point_s
{
	double x;
	double y;
} point_t;



//------------------------------------------------
// Function Prototypes
//------------------------------------------------

//--------------------------------------------------------
// polyfit()
// Computes polynomial coefficients that best fit a set
// of input points.
//
// The degree of the fitted polynomial is one less than
// the count of coefficients in the coefficients array.
//
// Returns 0 if success.
//--------------------------------------------------------
int polyfit( int pointCount, point_t pointArray[],  int coeffCount, double coeffArray[] );

//--------------------------------------------------------
// showPoly()
// Prints the coefficients of a polynomial.
//--------------------------------------------------------
void showPoly( int coeffCount, double coeffArray[] );



#endif	// POLYFIT_H
