// Name: test.c
// Description: Test file to exercise the MLS polynomial fitting function.
// Author: Henry Forson
// Coyright ©2020 Henry Forson, Melbourne, Florida USA

#include  <stdio.h>
#include  "polyfit.h"

// ---------------- TEST 1 DATA ------------------------
// Create test data to find the closest line to (0,6), (1,0), and (2,0).
// See also page 218 of: https://math.mit.edu/~gs/linearalgebra/ila0403.pdf
double x1[]   = { 0, 1, 2};
double y1[]   = { 6, 0, 0};
int pc1       = (int) (sizeof(x1) / sizeof(x1[0]));           // pointCount
double cr1[]  = {0, 0};                                       // coefficientResults
int cc1       =  (int) (sizeof(cr1) / sizeof(cr1[0]));        // coefficientCount
char *er1     = "-3x + 5";                                    // expected result

// ---------------- TEST 2 DATA ------------------------
// Create test data to find the closest parabola to the points shown.
// as example "4.3 B" on page 226 of: https://math.mit.edu/~gs/linearalgebra/ila0403.pdf
double x2[]   = { -2, -1, 00, 1, 2};
double y2[]   = { 0, 0, 1, 0, 0};
int pc2       = (int) (sizeof(x2) / sizeof(x2[0]));           // pointCount
double cr2[]  = {0, 0, 0};                                    // coefficientResults
int cc2       =  (int) (sizeof(cr2) / sizeof(cr2[0]));        // coefficientCount
char *er2     = "(-10/70)(x^2) + (34/70)";                    // expected result

// ---------------- TEST 3 DATA ------------------------
// Create a failure test case with impossible to solve data.
double x3[]   = { 0, 1, 1, 0};
double y3[]   = { 0, 1, 1, 0};
int pc3       = (int) (sizeof(x3) / sizeof(x3[0]));           // pointCount
double cr3[]  = {0, 0, 0};                                    // coefficientResults
int cc3       =  (int) (sizeof(cr3) / sizeof(cr3[0]));        // coefficientCount
char *er3     = "this one should fail returning -4";          // expected result

// ---------------- TEST 4 DATA ------------------------
// test MLS regeression example from https://www.mathsisfun.com/data/least-squares-regression.html
double x4[]   = { 2, 3, 5, 7, 9};
double y4[]   = { 4, 5, 7, 10, 15};
int pc4       = (int) (sizeof(x4) / sizeof(x4[0]));           // pointCount
double cr4[]  = {0, 0};                                       // coefficientResults
int cc4       =  (int) (sizeof(cr4) / sizeof(cr4[0]));        // coefficientCount
char *er4     = "(1.518 * x) + 0.305";                        // expected result


//--------------------------------------------------------
// main()
// Unit tests the poly() function.
//--------------------------------------------------------
int main()
{
  int result;

  //---------------------TEST 1---------------------------
  printf( "Test 1 expecting %s\n", er1);
  printf( "Test 1 produced ");
  result = polyfit( pc1, x1, y1, cc1, cr1);
  if( 0 == result)
  { 
    showPoly( cc1, cr1 );
  }
  else
  {
    printf( "result = %d.\n", result );
  }
  
  //---------------------TEST 2---------------------------
  printf( "Test 2 expecting %s\n", er2);
  printf( "Test 2 produced ");
  result = polyfit( pc2, x2, y2, cc2, cr2);
  if( 0 == result)
  { 
    showPoly( cc2, cr2 );
  }
  else
  {
    printf( "result = %d.\n", result );
  }
  
 //---------------------TEST 3---------------------------
  printf( "Test 3 expecting %s\n", er3);
  printf( "Test 3 produced ");
  result = polyfit( pc3, x3, y3, cc3, cr3);
  if( 0 == result)
  { 
    showPoly( cc3, cr3 );
  }
  else
  {
    printf( "result = %d.\n", result );
  }
  
//---------------------TEST 4---------------------------
  printf( "Test 4 expecting %s\n", er4);
  printf( "Test 4 produced ");
  result = polyfit( pc4, x4, y4, cc4, cr4);
  if( 0 == result)
  { 
    showPoly( cc4, cr4 );
  }
  else
  {
    printf( "result = %d.\n", result );
  }
  
  
  
  return( 0 );
}

