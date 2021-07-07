Name
====

**polyDerivative** — "C" function that computes a derivative of a polynomial.

Synopsis
========

**#include "polyfit.h"**

__void polyDerivative(int__ _coefficientCount_, **const double\*** _coefficientResultsIn_, **double\*** _coefficientResultsOut___);__

Description
===========

The **polyDerivative**() function computes the derivative of a polynomial.

Arguments
---------

_coefficientCount_ — input. The number of coefficients to be input, equal to the degree of the polynomial plus 1.

_coefficientResultsIn_ — input. The coefficients of the polynomial. There should be _coefficientCount_ coefficients.
These coefficients are ordered from the highest-order monomial term to the lowest, such that for instance the polynomial:
5x² + 3x - 7 is represented as: [ 5, 3, -7 ] 

_coefficientResultsOut_ — ouput. The coefficients of the derivative of the polynomial.
Note that one less coefficient is output than input. These are stored in the same order as _coefficientResultsIn_.
Also, space for the output coeffcient array must be allocated by the caller.

Return Value
------------
No value is returned.

FILES
-----
*./src/polyfit.c* — defines the **polyDerivative**() function.

*./inc/polyfit.h* — declares the **polyDerivative**() function's prototype.

MISC
----
To support unit testing on Linux with gcc, the repo has these additional files:

*./src/test-2.c* — exercises **polyDerivative**() and provides examples of usage.

*./src/test-3.c* — exercises **polyDerivative**() and provides examples of usage.

*./Makefile* — allows the *make* command to build the executables, *./bin/test-2* and *./bin/test-3* that test **polyDerivative**().
