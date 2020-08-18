#ifndef M_UTIL_H
#define M_UTIL_H

/*
Some math functions compiled with -O3 for calculating curves
*/

// #define INCLUDE_MATH_H

#ifdef INCLUDE_MATH_H
#include <math.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int factorial(int);
int nCr(int, int);

int signum(int);

// binary power algorithm
double fpow(double, int);

// unsigned exponent binary power algorith,
double ufpow(double, unsigned int);

#ifdef __cplusplus
}
#endif

#endif