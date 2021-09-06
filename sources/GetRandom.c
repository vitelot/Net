#include "main.h"
#include "extern.h"

extern Real UniformDistribution( Real min, Real max);
extern Real ExponentialDistribution( Real a, Real b);
extern Real GaussianDistribution( Real a, Real b);
extern Real PowerDistribution( Real a, Real b);
extern Real UserDistribution( Real a, Real b);

Real GetRandom( enum RndDistrib RDType, Real a, Real b)
{
Real x;

  switch( RDType) {
  case UNIF:
    x =     UniformDistribution( a, b);
    break;
  case EXP:
    x = ExponentialDistribution( a,b);
    break;
  case GAUSS:
    x =    GaussianDistribution( a,b);
    break;
  case POWER:
    x =       PowerDistribution( a,b);
    break;
  case USER:
    x =        UserDistribution( a,b);
    break;
  default:
    perr("No such random distribution found. Exit.\n");
    exit(1);
  }

  return x;
}
