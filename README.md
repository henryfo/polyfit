Name
====

**polyfit** — "C" function that fits a polynomial to a set of points

Synopsis
========

**#include "polyfit.h"**

__int polyfit( int__ _pointCount_, **double \***_x_, **double \***_y_,  __int__ _coefficientCount_, **double \***_coefficients_ __);__

Description
===========

The **polyfit**() function regresses a line or a higher-order polynomial to a set of points, using the Method of Least Squares. Its design goals were simplicity and ease of porting, as opposed to run-time efficiency when using large data-sets.

Arguments
---------
_pointCount_ — input. The total number of points in the set. For the algorithm to work, this must be greater than or equal to _coefficientCount_.

_x_  — input. Points to the X coordinates of the points.

_y_ — input. Points to the Y coordinates of the points.

_coefficientCount_ — input. The number of coefficients to be computed, equal to the degree of the polynomial plus 1. For instance, if fitting a line _coefficientCount_ would be 2, and for fitting a parabola it would be 3.

_coefficients_ — input pointing to the coefficient values that will get modified. The resulting coefficients are ordered   such that the polynomial:

     (5.7 * x^2) + (3.1 * x) - 15.4
     
produces:

     [ -15.4, 3.1, 5.7 ] 


Return Value
------------
In addition to setting the coefficients, the **polyfit**() function returns **0** on success.

FILES
-----
*./src/polyfit.c* — defines the **polyfit**() function.

*./inc/polyfit.h* — declares the **polyfit**() function's prototype.

In addition, *test.c* exercises **polyfit**() and provides examples of usage, and *Makefile* builds an executable for testing on Linux using _gcc C99_.
