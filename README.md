# Simple polynomial fitting to a set of points.
## Defines a "C" function called "poly" that can regress a line or a higher-order polynomial to a set of points, using the Method of Least Squares.
## Only two source files are needed for this:
### 1.) The "mls.c" file defines the poly() function.
### 2.) The "mls.h" file declares the function's API.

In addion, "test.c" exercises poly() and provides examples of usage. There's a Makefile that compiles the test code into an executable, for testing on Ubuntu Linux using gcc C99.
