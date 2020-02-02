// file: polyfit.h
// Description:	Header file for MLS polynomial fitting.
// Author: Henry Forson
// Copyright 2020 Henry Forson, Melbourne, FL

#ifndef POLYFIT_H
#define POLYFIT_H


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
int polyfit( int pointCount, double *xValues, double *yValues, int coefficientCount, double *coefficientResults );

//--------------------------------------------------------
// showPoly()
// Prints the coefficients of a polynomial.
//--------------------------------------------------------
void showPoly( int coeffCount, double *coefficients );



#endif	// POLYFIT_H
