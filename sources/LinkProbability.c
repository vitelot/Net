#include "main.h"
#include "extern.h"

#define THETA(x) ((x)>=0?1:0)

static Real Theta1( Real x, Real y, Real Z, Real E, Real m);
static Real Theta2( Real x, Real y, Real Z, Real E, Real m);
static Real XY    ( Real x, Real y, Real Z, Real E, Real m);
static Real User1 ( Real x, Real y, Real Z, Real E, Real m);
static Real User2 ( Real x, Real y, Real Z, Real E, Real m);
static Real User3 ( Real x, Real y, Real Z, Real E, Real m);

Real LinkProbability( Real x, Real y, Real Z, Real E, Real m)
{
  Real (*F)(Real, Real, Real, Real, Real);

  switch( In.linktype) {
  case 1:  F = Theta2; break;
  case 2:  F = XY;     break;
  case 3:  F = User1;  break;
  case 4:  F = User2;  break;
  case 5:  F = User3;  break;
  default: F = Theta1;
  }


  return F( x, y, m, Z, E);
}


static Real Theta1( Real x, Real y, Real m, Real Z, Real E)
{ 
  if( E==0) return m*THETA(x+y -Z); 
  else
    return m/(1.0+ exp((Z-x-y)/E));
}

static Real Theta2( Real x, Real y, Real m, Real Z, Real E)
{ 
  if( E==0) return m*THETA(Z-fabs(x-y)); 
  else
    return m/(1.0+ exp((fabs(x-y)-Z)/E));
}

static Real XY( Real x, Real y, Real m, Real Z, Real E)
{ 
  return m * x*y / (Z*Z);
}


/* USER DEFINED FUNCTIONS */

static Real User1( Real x, Real y, Real m, Real Z, Real E)
{
  Real k0=m, xmin=Z, alpha=E;
  Real z, beta, betaalp, c;

/*    z = fabs(x-y); */
/*    r = exp(-z); */
/*    return m/2.0*exp((1-r)/Z)*(1.+r/Z-r*r/Z/Z); */

  if(fabs(x-y)>60) return 0;

  alpha = 1.-alpha;

  beta = k0/In.nk;
  betaalp = pow(beta, alpha);
  c = 1.-betaalp;

  z = x+y;

  return betaalp + c * (1. - pow(z/xmin, alpha) * (alpha/z -1.));

/*    z=x+y; */
/*    r = exp(-z); */
/*    f = 1.0/m-(1.-r)/Z; */
/*    return (1./m-1./Z)/(f*f); */
}

/*  static Real User2( Real x, Real y, Real m, Real Z, Real E) */
/*  { */
/*    Real c, k0=m, N, z, R, f; */

/*    N=In.nk; */
/*    c = 1./(1./k0-1./N); */

/*    z=x+y; */
/*    R = 1.-exp(-z); */
/*    f = 1.0/k0-R/c; */
/*    return (1./k0-1./c)/(f*f)/N; */
/*  } */

static Real User3( Real x, Real y, Real m, Real Z, Real E)
{
Real c, k0=m, N, Rx,Ry;
Real alpha=Z;

  N=In.nk;
  Rx = 1.0-exp(-x);
  Ry = 1.0-exp(-y);

  if(alpha==-1.0) {
    c = 1./log(N/k0);
    return k0/(c*(exp(1./c)-1.))/N * exp(Rx/c)* exp(Ry/c);
  } else {
    c = (alpha+1.0)/(pow(N, alpha+1.0)-pow(k0, alpha+1.0));
    return pow(pow(k0, alpha+1.0)+(alpha+1.0)/c*Rx, 1./(alpha+1.))*
           pow(pow(k0, alpha+1.0)+(alpha+1.0)/c*Ry, 1./(alpha+1.));
  }
}

/*  static Real User2( Real x, Real y, Real m, Real Z, Real E) */
/*  { */
/*    return 1.0-m*x*y/Z; */
/*  } */
static Real User2( Real x, Real y, Real m, Real Z, Real E)
{ 
  float a=.45;
  float b=.65;
  float c=.75;
  float d=.25;

  if( (                x<a && y<a) ||
      (x>=a && y>=a && x<b && y<b) ||
      (x>=b && y>=b && x<c && y<c) ||
      (x>=c && y>=c)                    ) {
    return m;
  }
  return Z;
}
