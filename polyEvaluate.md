Name
====

**polyEvaluate** — "C" function that evaluates a polynomial at a given _x_ value.

Synopsis
========

**#include "polyfit.h"**

__double polyEvaluate(int__ _coefficientCount_, **const double\*** _coefficients_, **double** _x___);__

Description
===========

The **polyEvaluate**() function evaluates a polynomial at a given _x_ value.

Arguments
---------
_coefficientCount_ — input. The number of coefficients of the polynomial, equal to the degree of the polynomial plus 1.

_coefficients_ — input. Points to where the computed coefficients are stored. There should be _coefficientCount_ coefficients.
These coefficients are ordered from the highest-order monomial term to the lowest, such that for instance the polynomial:
5x² + 3x - 7 is represented as: [ 5, 3, -7 ].

_x_ - input. The _x_ value at which the polynomial is to be evaluated.

Return Value
------------
The **polyEvaluate**() function returns the value of the polynomial at _x_.

FILES
-----
*./src/polyfit.c* — defines the **polyEvaluate**() function.

*./inc/polyfit.h* — declares the **polyEvaluate**() function's prototype.

MISC
----
To support unit testing on Linux with gcc, the repo has these additional files:

*./src/test-2.c* and *.src.test-3.c* — exercise **polyEvaluate**() and provide examples of usage.

*./Makefile* — allows the *make* command to build executables *./bin/test-2* and *./bin/test-3* that test **polyEvaluate**().
