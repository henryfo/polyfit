Name
====

**polyError** — "C" function that estimates the error of a polynomial fitted via **polyfit**() vs. the data used to fit the polynomial.

Synopsis
========

**#include "polyfit.h"**

__double polyError(int__ _pointCount_, **const double\*** _xValues_, **const double\*** _yValues_,  __int__ _coefficientCount_, **const double\*** _coefficients___);__

Description
===========

The **polyError**() function estimates the error of a polynomial fitted via **polyfit**() vs. the data used to fit the polynomial.

Arguments
---------
_pointCount_ — input. The total number of points in the set. This must be equal to _coefficientCount_.

_xValues_  — input. Points to an array of the X coordinates of the points. There should be _pointCount_ X coordinates.

_yValues_ — input. Points to an array of the Y coordinates of the points. There should be _pointCount_ Y coordinates.

_coefficientCount_ — input. The number of coefficients, equal to the degree of the polynomial plus 1.

_coefficients_ — input. Points to where the computed coefficients are stored. There should be space for _coefficientCount_ coefficients. These coefficients are ordered from the highest-order monomial term to the lowest, such that for instance the polynomial: 5x² + 3x - 7 is represented as: [ 5, 3, -7 ].

Return Value
------------
The **polyError**() function returns the sum of the errors (squared).

FILES
-----
*./src/polyfit.c* — defines the **polyError**() function.

*./inc/polyfit.h* — declares the **polyError**() function's prototype.

MISC
----
To support unit testing on Linux with gcc, the repo has these additional files:

*./src/test-2.c* — exercises **polyError**() and provides examples of usage.

*./src/test-3.c* — exercises **polyError**() and provides examples of usage.

*./Makefile* — allows the *make* command to build executables *./bin/test-2* and *./bin/test-3* that test **polyError**().
