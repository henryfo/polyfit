// Name: test.c
// Description: Test file to exercise the MLS polynomial fitting function.
// Author: Henry Forson
// Coyright ©2020 Henry Forson, Melbourne, Florida USA

#include  <stdio.h>
#include  "mls.h"

// Create test data to find the closest line to (0,6), (1,0), and (2,0).
// See also page 218 of: https://math.mit.edu/~gs/linearalgebra/ila0403.pdf

point_t m_pts1[] =
{
  {0,6},
  {1,0},
  {2,0}
};
int numPoints = (int) (sizeof(m_pts1) / sizeof(m_pts1[0]));

double coeff1[] = {0, 0};
int numCoeffs = (int) (sizeof(coeff1) / sizeof(coeff1[0]));

int main()
{
  printf("Hello world test stub.\n" );
  int result = poly( numPoints, &m_pts1[0], numCoeffs, &coeff1[0]);
  printf( "poly returned %d.\n", result );
  return( 0 );
}

