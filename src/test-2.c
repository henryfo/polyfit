// Name: test.c
// Description: Test file to exercise the MLS polynomial fitting function.
// Author: Stephen P. Morgan, San Jose, CA
// Derived from work by: Henry Forson, Melbourne, Florida USA

//------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  "polyfit.h"

// Buffer to hold a string representation of a polynomial:

#define POLY_STRING_BF_SZ   (256)

char polyStringBf[POLY_STRING_BF_SZ];

double x[] = {
#include "test-2-x.h"
};

double y[] = {
#include "test-2-y.h"
};

int cc = 13;

int pc = (int)(sizeof(x) / sizeof(x[0])); // pointCount

double* cr;

//--------------------------------------------------------
// main()
//
// This is a test program of (augmented) polyfilt which takes
// measurement data "test-2-x.h" and "test-2-y.h", the X and Y
// coordinates of samples taken for the number of threads and
// weighted system performance, respectively, for an actual
// computing system with 56 CPUs. X ranges from [56..1120], or one
// thread per CPU to 20 threads per CPU, and Y ranges from
// [0.0..1.0], where a higher weight corresponds to better
// performance.
// 
// The goal of this test is to identify a polynomial regression in
// one variable (X) which optimally models the relationship between
// the number of threads and system performance.
// 
// The test works by fitting the data to all order polynomials from
// zeroth to twelfth, and showing the error associated with each.
// The user must "eyeball" the optimal polynomial (if any).
//--------------------------------------------------------
#define MAX_POLYNOMIAL 12

int
main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	double error_original;
	double error_previous;

	// Generate even-ordered polynomials of orders 0 to 12 to fit the supplied data.

	for (int cc = 1; cc <= MAX_POLYNOMIAL + 1; cc += 2) {
		printf("Test: Polynomial Order %d:\n", cc - 1);

		// Allocate storage to hold polynomial coefficients,

		cr = calloc(cc, sizeof(double)); // coefficientResults

		// Fit a polynomial of order cc-1 to the data.

		int rVal = polyfit(pc, x, y, cc, cr);

		// Check whether polyfit was able to generate the desired polynomial.

		if (0 == rVal) { 
			// Format the polynomial.

			polyToString(polyStringBf, POLY_STRING_BF_SZ, cc, cr);
		}
		else {
			// Format the polynomial (such as it is) with an error message.

			snprintf(polyStringBf, POLY_STRING_BF_SZ, "error = %d", rVal);
		}

		// Print polynomial or error string.

		printf("Test produced %s\n", polyStringBf);

		// If no error, analyze the polynomial.

		if (0 == rVal) {
			// Compute the error associated with the polynomial.

			double error = polyError(pc, x, y, cc, cr);

			printf("Error was %.6f", error);

			if (cc == 1) {
				printf(".\n");

				// If this is the first valid polynomial, remember its error.

				error_original = error;
			}
			else {
				// If this is not the first valid polynomial, print the change
				// in the error overall and for this step.

				printf("; error improvement: total %7.3f%%, step %7.3f%%.\n",
					100.0 * (1.0 - error / error_original),
					100.0 * (1.0 - error / error_previous));

				if (100.0 * (1.0 - error / error_previous) < 1.0) {
					printf("\nThe order %u polynomial is the best fit.\n", cc - 3);
					free(cr);
					goto Exit;
				}
			}

			// Remember this error for stepwise error comparison(s).

			error_previous = error;
		}

		printf("-------------------\n");

		// Free allocated resources.

		free(cr);
	}

	printf("\nThe %uth-order polynomial is the best fit.\n", MAX_POLYNOMIAL);

Exit:

	// Done.

	return 0;
}

