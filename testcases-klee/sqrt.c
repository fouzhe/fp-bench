// Computes the square root of a number using a naive binary search.
//

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "klee/klee.h"


#define EPSILON 0.0000001f

// Check whether two floats are within EPSILON of each other
bool almost_equal(float x, float y) {
  // DL: Need to implement fabs() internally.
  return fabs(x - y) < EPSILON;
}

float naive_sqrt(float x) {

  assert(x >= 1.0f);
  assert(!isnan(x));

  // Binary search for a number a with the property that a*a is almost
  // equal to x

  float lo = 1.0f;
  float hi = x;
  for(;;) {
    assert(lo <= hi);
    float candidate = (hi + lo)/2.0f;
    if(almost_equal(candidate*candidate, x)) {
      return candidate;
    }
    if(candidate*candidate > x) {
      hi = candidate;
    } else {
      lo = candidate;
    }
    assert(lo != hi);
  }

}


int main(int argc, char** argv) {

  float x;

  klee_make_symbolic(&x, sizeof(float), "x");

  // Restrict to values that are numbers, and are within a small
  // range.

  if(isnan(x)) {
    return 0;
  }

  if(x < 1.0f || x > 100.0f) {
    return 0;
  }

  // Check that square root of x does not exceed x, and that the value
  // computed squares to give almost x.
  float sqrt_x = naive_sqrt(x);
  assert(sqrt_x <= x);
  if (!almost_equal(x, sqrt_x*sqrt_x)) {
    printf("BUG triggered\n");
    return 1;
  }

  return 0;

}
