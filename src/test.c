// Name: test.c
// Description: Test file to exercise the MLS polynomial fitting function.
// Author: Henry Forson
// Coyright ©2020 Henry Forson, Melbourne, Florida USA

#include  <stdio.h>
#include  "polyfit.h"

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

// Create a failure test case with impossible data
point_t m_pts13[] =
{
  {0,0},
  {1,1},
  {1,1},
  {0,0}, 
};
int numPoints13 = (int) (sizeof(m_pts13) / sizeof(m_pts13[0]));
double coeff13[] = {0, 0, 0};
int numCoeffs13 = (int) (sizeof(coeff13) / sizeof(coeff13[0]));

// test MLS regeression example from https://www.mathsisfun.com/data/least-squares-regression.html
point_t m_pts14[] =
{
  {2,4},
  {3,5},
  {5,7},
  {7,10}, 
  {9,15}
};
int numPoints14 = (int) (sizeof(m_pts14) / sizeof(m_pts14[0]));
double coeff14[] = {0, 0};
int numCoeffs14 = (int) (sizeof(coeff14) / sizeof(coeff14[0]));


//--------------------------------------------------------
// main()
// Unit tests the poly() function.
//--------------------------------------------------------
int main()
{
  // printf("Hello world test stub.\n" );
  int result = polyfit( numPoints, &m_pts1[0], numCoeffs, &coeff1[0]);
  if( 0 == result)
  {
    printf( "Test 1 polynomial = ");
    showPoly( numCoeffs, &coeff1[0] );
    printf("Test 1 polynomial should be equivalent to 5 + -3x.\n");
  }
  else
  {
    printf( "Error in test 1: polyfit returned %d.\n", result );
  }
  
 result = polyfit( numPoints43, &m_pts43[0], numCoeffs43, &coeff43[0]);
  if( 0 == result)
  {
    printf( "Test 4.3 B polynomial = ");
    showPoly( numCoeffs43, &coeff43[0] );
    printf("Test 4.3 B polynomial should be equivalent to (34/70) + (-10/70)(x^2).\n");
  }
  else
  {
    printf( "Error in test 4.3 B: polyfit returned %d.\n", result );
  }

  result = polyfit( numPoints13, &m_pts13[0], numCoeffs13, &coeff13[0]);
  if( 0 == result)
  {
    printf( "Test unlucky 13 polynomial = ");
    showPoly( numCoeffs13, &coeff13[0] );
    printf("Test 13 polynomial should fail since we are fitting a parabola to only two unique points.\n");
  }
  else
  {
    printf( "Expected error in test 13 is OK: polyfit returned %d.\n", result );
  }
  
  result = polyfit( numPoints14, &m_pts14[0], numCoeffs14, &coeff14[0]);
  if( 0 == result)
  {
    printf( "Test 14 polynomial = ");
    showPoly( numCoeffs14, &coeff14[0] );
    printf("Test 14 polynomial should be approximately 0.305 + (1.518 * x).\n");
  }
  else
  {
    printf( "Error in test 14: polyfit returned %d.\n", result );
  }
  

  
  return( 0 );
}

