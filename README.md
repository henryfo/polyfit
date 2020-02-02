Name
====

**polyfit** — fits a polynomial to a set of points

Synopsis
========

**#include "polyfit.h"**

__int polyfit( int__ _pointCount_, **double \***_x_, **double \***_y_,  __int__ _coefficientCount_, **double \***_coefficients_ __);__

Description
===========

The **polyfit**() function regresses a line or a higher-order polynomial to a set of points, using the Method of Least Squares. It was written in "C" with design goals of simplicity and ease of porting, instead of optimizing for large data-sets.

Arguments
---------
_pointCount_ — input. The total number of points in the set. For the algorithm to work, this must be greater or equal to _coefficientCount_.

_x_  — input. Points to the X coordinates of the points.

_y_ — input. Points to the Y coordinates of the points.

_coefficientCount_ — input. The number of coefficients to be computed, equal to the degree of the polynomial plus 1. For instance, if fitting a line _coefficientCount_ would be 2, and for fitting a parabola it would be 3.

_coefficients_ — input pointing to polynomial coefficient values, that will get modified. The values of the coefficients are computed by *polyfit*() such that the polynomial "5.7\*(x^2) + 3.1\*x -15.4" would result in _coefficients_ of \[ -15.4, 3.1, 5.7 \]. 


Return Value
------------
The **polyfit**() function returns 0 if the coefficients of the polynomial have been successfully computed and set in _coefficients_.

FILES
-----
*./src/polyfit.c* — defines the *polyfit*() function.

*./inc/polyfit.h* — declares the *polyfit*() function's prototype.

In addition, *test.c* exercises **polyfit**() and provides examples of usage, and *Makefile* build an executable for testing on Linux using **gcc**'s C99.
