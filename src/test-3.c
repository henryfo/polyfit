// Name: test-3.c
// Description: Another test file to exercise the MLS polynomial fitting function.
// Author: Stephen P. Morgan, San Jose, CA
// Derived from work by: Henry Forson, Melbourne, Florida USA

//-----------------------------------------------------------------------------
// MIT License
//
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
//------------------------------------------------------------------------------

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  "polyfit.h"

// Buffer to hold a string representation of a polynomial:

#define POLY_STRING_BF_SZ   (256)

char polyStringBf[POLY_STRING_BF_SZ];

double x[] = {
#include "test-3-x.h"
};

double y[] = {
#include "test-3-y.h"
};

int cc = 13;

int pc = (int)(sizeof(x) / sizeof(x[0])); // pointCount

double* cr;
double* cr_der;

#define NUM_CPUS 56

//--------------------------------------------------------
// main()
//
// This is a test program of (augmented) polyfilt which takes
// measurement data "test-3-x.h" and "test-3-y.h", the X and Y
// coordinates of samples taken for the number of threads and
// weighted system performance, respectively, for an actual
// computing system with 56 CPUs. X ranges from [56..1120], or one
// thread per CPU to 20 threads per CPU, and Y ranges from
// [0.0..1.0], where a higher weight corresponds to better
// performance. The goal of this test is to identify the optimal
// number of threads with which to run the system, both by the
// number of theads per CPU and the number of threads individually,
// in case they differ.
// 
// The test works by fitting the data to a sixth-order polynomial
// (which we've already decided best models the sysem), then
// searching for a root of the derivative of the polynomial (a
// well-known method to find local maxima and minima) within a
// range. (To do so, we implemented the secant method.)
//
// Next, the program searches for the actual optimal configuration
// by evaluating the polynomial at each of the configurations of
// threads ranging from 1xCPUs, 2xCPUs, ..., 20xCPUs. It also
// searches for the actual optimal number of threads by evaluating
// the polynomial at each individual number of threads, from
// [56..1120].

// Finally, the program determines whether the root found using
// the secant method represents a local maximum or minimum.
//
// Note: We happen to know, a priori, that the actual optimal number
// of threads lies somewhere in the range  [4xCPUs..5xCPUs].
//--------------------------------------------------------
int
main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	printf("Searching for the optimal number of threads for a system with %u CPUs.\n",
			NUM_CPUS);

	int cc = 7;

	printf("\nTest: Polynomial Order %d:\n", cc - 1);

	cr = calloc(cc, sizeof(double)); // coefficientResults
	cr_der = calloc(cc - 1, sizeof(double)); // coefficientResults

	int rVal = polyfit(pc, x, y, cc, cr);

	if (0 == rVal) { 
		polyToString(polyStringBf, POLY_STRING_BF_SZ, cc, cr);
	}
	else {
		snprintf(polyStringBf, POLY_STRING_BF_SZ, "error = %d", rVal);
	}

	printf("\n%s\n", polyStringBf);

	printf("\nThe overall fitting error for that polynomial is %.6f.\n",
			polyError(pc, x, y, cc, cr));

	printf("\nSearching for roots of the derivative of that polynomial"
			" (for local maxima and minima).\n");

	polyDerivative(cc, cr, cr_der);

	polyToString(polyStringBf, POLY_STRING_BF_SZ, cc - 1, cr_der);

	printf("\nThe derivative of that polynomial is %s\n", polyStringBf);

	int iterations = 16;
	double epsilon = 0.000001;

	int root = polyRoot(cc - 1, cr_der, NUM_CPUS, 20 * NUM_CPUS,
			&iterations, &epsilon);

	printf("\npolyRoot returned %u (iterations %u, epsilon %.g).\n", root,
			iterations, epsilon);

	double value = polyEvaluate(cc, cr, root);
	double max = value;
	double root_value = value;
	int max_idx = 0;

	printf("\npolyEvaluate(%u) returned %g.\n", root, root_value);

	for (int i = 1; i <= 20; i++) {
		value = polyEvaluate(cc, cr, i * NUM_CPUS);
		if (value > max) {
			max_idx = i;
			max = value;
		}
	}

	double max_by_cpus = max;

	printf("\nThe optimal number of threads (by CPUs) is %uxCPUs, or %u (value %g).\n",
			max_idx, max_idx * NUM_CPUS, max_by_cpus);

	for (int i = 1; i <= 1120; i++) {
		value = polyEvaluate(cc, cr, i);
		if (value > max) {
			max_idx = i;
			max = value;
		}
	}

	double max_individual = max;

	printf("\nThe optimal number of threads (individually) is %u (value %g), or about %.1fxCPUs.\n",
			max_idx, max_individual, (double)max_idx / NUM_CPUS);

	double max_overall =
			(max_by_cpus > max_individual) ? max_by_cpus : max_individual;

	if (max_overall >= root_value) {
		printf("\nRoot %u is a local minimum.\n", root);
	}
	else {
		printf("\nRoot is a local maximum.\n");
	}

	free(cr);
	free(cr_der);

	return 0;
}

