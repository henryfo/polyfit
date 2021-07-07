Name
====

**polyfit** — "C" function that fits a polynomial to a set of points

Synopsis
========

**#include "polyfit.h"**

__int polyfit(int__ _pointCount_, **const double\*** _xValues_, **const double\*** _yValues_,  __int__ _coefficientCount_, **double\*** _coefficientResults___);__

Description
===========

The **polyfit**() function regresses a line or a higher-order polynomial to a set of points, using the Method of Least Squares. Its design goals were simplicity and ease of porting, as opposed to run-time efficiency with large data.

Arguments
---------
_pointCount_ — input. The total number of points in the set. For the algorithm to work, this must be greater than or equal to _coefficientCount_.

_xValues_  — input. Points to an array of the X coordinates of the points. There should be _pointCount_ X coordinates.

_yValues_ — input. Points to an array of the Y coordinates of the points. There should be _pointCount_ Y coordinates.

_coefficientCount_ — input. The number of coefficients to be computed, equal to the degree of the polynomial plus 1. For instance, if fitting a line — a first degree polynomial — then _coefficientCount_ would be 2, and for fitting a parabola — a second degree polynomial — _coefficientCount_ would be 3.

_results_ — input. Points to where the computed coefficients will be stored. There should be space for _coefficientCount_ coefficients. These coefficients are ordered from the highest-order monomial term to the lowest, such that for instance the polynomial: 5x² + 3x - 7 is represented as: [ 5, 3, -7 ].

Return Value
------------
In addition to setting the coefficient results, the **polyfit**() function returns **0** on success.

FILES
-----
*./src/polyfit.c* — defines the **polyfit**() function.

*./inc/polyfit.h* — declares the **polyfit**() function's prototype.

MISC
----
To support unit testing on Linux with gcc, the repo has these additional files:

*./src/test-1.c* — exercises **polyfit**() and provides examples of usage.

*./Makefile* — allows the *make* command to build an executable, *./bin/test-1*, that tests **polyfit**().
