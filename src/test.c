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

// Create test data to find the closest parabola to the points shown
// as example "4.3 B" on page 226 of: https://math.mit.edu/~gs/linearalgebra/ila0403.pdf
point_t m_pts43[] =
{
  {-2,0},
  {-1,0},
  {0,1},
  {1,0},
  {2,0}
};

int numPoints43 = (int) (sizeof(m_pts43) / sizeof(m_pts43[0]));
double coeff43[] = {0, 0, 0};
int numCoeffs43 = (int) (sizeof(coeff43) / sizeof(coeff43[0]));




int main()
{
  // printf("Hello world test stub.\n" );
  int result = poly( numPoints, &m_pts1[0], numCoeffs, &coeff1[0]);
  if( 0 == result)
  {
    printf( "test 1 polynomial = ");
    for( int i = 0; i < numCoeffs; i++)
    {
      printf( "(%f * x^%d)%s", coeff1[i], i, i < (numCoeffs - 1) ? " + " : "" );
    }
    printf("; should be equivalent to 5 + -3x.\n");
  }
  else
  {
    printf( "Error in test 1: poly returned %d.\n", result );
  }
  
 result = poly( numPoints43, &m_pts43[0], numCoeffs43, &coeff43[0]);
  if( 0 == result)
  {
    printf( "test 4.3 B polynomial = ");
    for( int i = 0; i < numCoeffs43; i++)
    {
      printf( "(%f * x^%d)%s", coeff43[i], i, i < (numCoeffs43 - 1) ? " + " : "" );
    }
    printf("; should be equivalent to (34/70) + (-10/70)(x^2).\n");
  }
  else
  {
    printf( "Error in test 4.3 B: poly returned %d.\n", result );
  }
  
  return( 0 );
}

