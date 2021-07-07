Name
====

**polyRoot** — "C" function that computes a real root of a polynomial within the range [_x0_, _x1_].

Synopsis
========

**#include "polyfit.h"**

__double polyRoot(int__ _coefficientCount_, **const double\*** _coefficients_ **double** _x0_, **double** _x1_,  __int\*__ _iterations_, **double\*** _epsilon___);__

Description
===========

The **polyRoot**() function computes a real root of a polynomial within the range [_x0_, _x1_],
in no more than _\*iterations_ and with no more then _\*epsilon_ error.
Note that, if _\*iterations_ returns with a larger value than input, the method did not meet
its requirements, and the error of the approximation is _\*epsilon_.

**polyRoot**() uses the well-known _secant method_ of root approximation.

Arguments
---------
_coefficientCount_ — input. The number of coefficients.i, equal to the degree of the polynomial plus 1.
For instance, if the polynomial is of the first degree, i.e., a line, then _coefficientCount_ would be 2, and if of of the second degree, i.e., a parabola, then _coefficientCount_ would be 3.

_coefficients_ — input. Points to where the computed coefficients are stored. There should be _coefficientCount_ coefficients.
These coefficients are ordered from the highest-order monomial term to the lowest, such that for instance the polynomial:
5x² + 3x - 7 is represented as: [ 5, 3, -7 ].

_x0_ — input. The value of the start of the range.

_x1_ — input. The value of the end of the range.

_iterations_ — input/output. On input, points to the value of the maximum number of iterations the method should employ.
On output, points to the value of the number of iterations actually employed.
Note: On input, _iterations_ may be _NULL_, in which case the method will employ no more than 16 iterations.

_epsilon_ — input/output. On input, points to the value of the maximum error that may exist between the root and the estimate returned.
On output, points to the value of the actual error determined.
Note: On input, _epsilon_ may be _NULL_, in which case the method will seek an error of no more than 0.000001.

Return Value
------------
The **polyRoot**() function returns the real root on success.

FILES
-----
*./src/polyfit.c* — defines the **polyRoot**() function.

*./inc/polyfit.h* — declares the **polyRoot**() function's prototype.

MISC
----
To support unit testing on Linux with gcc, the repo has these additional files:

*./src/test-2.c* — exercises **polyRoot**() and provides examples of usage.

*./src/test-3.c* — exercises **polyRoot**() and provides examples of usage.

*./Makefile* — allows the *make* command to build executables *./bin/test-2* and *./bin/test-3* that test **polyRoot**().
