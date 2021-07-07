// file: polyfit.h
// Description:	Header file for MLS polynomial fitting.
// Author: Henry Forson, Melbourne, FL

//------------------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2020 Henry M. Forson
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
// Returns 0 if success.
//--------------------------------------------------------
int polyfit( int pointCount, double *xValues, double *yValues, int coefficientCount, double *coefficientResults );

//--------------------------------------------------------
// polyToString()
// Produces a string representation of a polynomial from
// its coefficients.
// Returns 0 on success.
//--------------------------------------------------------
int polyToString( char *stringBuffer, size_t stringBufferSz, int coeffCount, double *coefficients );

void polyDerivative(int cc, const double* cr_in, double* cr_out);
double polyError(int pc, double* x, double* y, int cc, double* cr);
double polyEvaluate(int cc, const double* cr, double x);
double polyRoot(int cc, const double* cr, double x0, double x1, int* iterations, double* epsilon);

#endif	// POLYFIT_H
