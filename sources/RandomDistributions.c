#include <math.h>
#include "main.h"

extern void perr(const char *fmt, ...);

extern long RArg; /* random nr gen argument. never modify it! */

extern float URand(long *idum);

Real UniformDistribution( Real min, Real max)
{ /* uniformly distributed rndm number generator in the interval (min, max) */
  return (max-min)*URand( &RArg)+min;
}

Real ExponentialDistribution( Real r, Real b)
{ /* generator of rndm numbers distributed as r*exp(-r*x), x>0 */
  Real x;

  do
    x = UniformDistribution( 0.0, 1.0);
  while (x == 0.0);

  return (-log(x)/r);
}

Real CenteredExponentialDistribution( Real a, Real x0) { 
  /* generator of rndm numbers distributed as A*exp(-a*|x-x0|), x,a,x0>0
     with A=a/(2-exp(-a x0)) as normalization factor */
  Real u;
  Real Eax0 = exp(-a*x0);
  Real Fx0 = (1.0-Eax0) / (2.0-Eax0);

  do
    u = UniformDistribution( 0.0, 1.0);
  while (u == 0.0);

  if(u<=Fx0)  
    return (x0 - log(u*(2.0-Eax0)+Eax0)/a);
  else
    return (x0 - log((1.0-u)*(2.0-Eax0))/a);
}

Real GaussianDistribution( Real s, Real m)
{ /* generator of rndm numbers distributed as (2*Pi*s^2)^0.5*exp(-(x-m)^2/2s^2), x>0 */
  extern float gasdev(long *idum);

  return m+fabs(s*gasdev( &RArg));
}

Real PowerDistribution( Real a, Real xmin)
/******************************************** 
     generator of rndm numbers distributed as 
     c*x^-a in the interval (xmin,+inf)
     0.0 (0,s) a>1 
*********************************************/
{ 

  Real x;

  if(xmin<=0.0) {
    perr("Power law distribution not valid with parameter b<=0. Use 0.001 for example. Exit\n");
    exit(1);
  }

  if( a>1) {

    do
      x = UniformDistribution( 0.0, 1.0);
    while (x == 1.0);

  } else {
    perr("Power distribution x^-a with a<=1 is not yet implemented. Exit.\n");
    exit(1);
  }
  
  return xmin*pow( 1.-x , 1./(1.-a));
}

Real BoundedPowerDistribution( Real a, Real xmin, Real xmax)
{
/******************************************** 
     generator of rndm numbers distributed as 
     c*x^a in the interval (xmin, xmax)
     0 elsewhere 
*********************************************/
  Real x, c;

  do
    x = UniformDistribution( 0.0, 1.0);
  while (x == 0.0);

  if( a==-1.0) {

    c = log(xmax/xmin);
    return xmin*exp(x/c);

  } else {

    a += 1.; /* use a+1 */
    c = pow(xmax, a)-pow(xmin,a); /* actually (a+1)/c */
    return pow( c*x + pow(xmin,a), 1./a);

  }
}

Real UserDistribution( Real a, Real xmin) {

  return BoundedPowerDistribution( a, xmin, 1000.0);
}
