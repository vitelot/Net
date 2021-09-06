/* 
   Builds a 2D geographical network (unit disk network).
   Circles are drawn at random onto a unit square.
   Links are drawn between two cicles if they overlap. 
*/

#include "main.h"
#include "extern.h"

struct Circle {
  Real x,y,r;
};

extern Real UniformDistribution( Real min, Real max);
extern Real CenteredExponentialDistribution( Real a, Real x0);
extern Real BoundedPowerDistribution( Real a, Real xmin, Real xmax);

static Real FreeSpace(struct Circle *, Int NK);
static void BuildNet(NODE *node, struct Circle *, Int NK);
static void Criterium1(NODE *, NODE *, Real, Real, Real);
static void Criterium2(NODE *, NODE *, Real, Real, Real);
static Real GetRadius(void);

void GeoNet( NODE *node, Int NK)
{
  register int i;
  struct Circle *circle;

  circle = (struct Circle *) malloc( (size_t) NK*sizeof(struct Circle));
  Loop(i,NK) {
    circle[i].x = UniformDistribution( 0.0, 1.0);
    circle[i].y = UniformDistribution( 0.0, 1.0);
    SetNodeFitness(&node[i], circle[i].r = GetRadius());
  }

  if(In.printdat) {
    FILE *fp;
    char filename[128];
    sprintf(filename, "=%s.geo", In.projname);
    fp = fopen(filename, "w");
    if(!fp) FileOpenError(filename);
    fprintf(fp,"@    s0 fill type 1\n");
    fprintf(fp,"@    s0 fill color 2\n");
    Loop(i,NK)
      fprintf( fp, "%g %g %g\n", circle[i].x, circle[i].y, circle[i].r);
    printf("File \"%s\" saved.\n", filename);
    if(In.rungrace && In.multi<2) {
      char cmd[128];
      sprintf( cmd, "xmgrace -free -graphtype fixed -settype xyr %s&", filename);
      system(cmd);
    }
  }

  if(In.nettype==0) FreeSpace( circle, NK); /* do it only for undir graphs */

  BuildNet( node, circle, NK);

  free(circle);
  printf("Done.   \n\n");
}

#define DL 2000

static Real FreeSpace(struct Circle *circle, Int NK) {
  register int i,x,y;
  int Xmin, Ymin, Xmax, Ymax, X,Y;
  Real x0, y0, r, r2, area=0.0;
  char grid[DL][DL];

  for(x=0; x<DL; x++)
    for(y=0; y<DL; y++)
      grid[x][y]=1;

  Loop(i,NK) {
    x0 = circle[i].x;
    y0 = circle[i].y;
    r  = circle[i].r;
    r2 = r*r;
    Xmin = (int) (DL*(x0-r));
    Xmax = (int) (DL*(x0+r));
    Ymin = (int) (DL*(y0-r));
    Ymax = (int) (DL*(y0+r));
    
    for(x=Xmin; x<=Xmax; x++) {
      for(y=Ymin; y<=Ymax; y++) {
	if( ((Real)x/DL-x0)*((Real)x/DL-x0)+((Real)y/DL-y0)*((Real)y/DL-y0)>r2 )
	  continue;
	X=x;
	if(x<0) X=DL+x;
	if(x>=DL) X=x-DL;
	Y=y;
	if(y<0) Y=DL+y;
	if(y>=DL) Y=y-DL;
	
	grid[X][Y] = 0;
      }
    }
  }
  for(x=0; x<DL; x++)
    for(y=0; y<DL; y++)
      area += grid[x][y];

  area /= (Real) DL * (Real) DL;

  printf("Free space: %g\n", area);

  return area;
}

static void BuildNet(NODE *node, struct Circle *circle, Int NK) {
  register int i,j;
  Real xi,yi,xj,yj, dx,dy, ri,rj, dist2;
  static void (*Criterium)(NODE *, NODE *, Real, Real, Real);

  if(In.nettype==1) {
    Criterium = Criterium2;
    printf("Building the geographical directed network.\n");
  } else {
    printf("Building the geographical network.\n");
    Criterium = Criterium1;
  }

  Loop(i,NK) {
    ShowProgress(i,NK);
    Loop(j,i) {
      xi=circle[i].x;
      yi=circle[i].y;
      ri=circle[i].r;
      xj=circle[j].x;
      yj=circle[j].y;
      rj=circle[j].r;
      dx = (xi-xj);
      dy = (yi-yj);
      if(dx>.5) dx = 1.-dx; /* PBC */
      if(dy>.5) dy = 1.-dy; /* PBC */
      dist2 = dx*dx + dy*dy;
      (*Criterium)( &node[i], &node[j], dist2, ri,rj);
    }
  }      
}

static void Criterium1(NODE *ni, NODE *nj, 
		Real dist2, Real ri, Real rj) {
  if(dist2<(ri+rj)*(ri+rj))
    AddTwoWayLink( ni, nj, dist2);
}

static void Criterium2(NODE *ni, NODE *nj, 
		Real dist2, Real ri, Real rj) {
  if(ri*ri >= dist2) 
    AddOneWayLink( ni, nj, dist2);
  if(rj*rj >= dist2) 
    AddOneWayLink( nj, ni, dist2);
}

static Real GetRadius(void) {

  switch(In.GNradiusdistr) {

  case RADIUS: return In.GNrmin;

  case RADII:
    if(UniformDistribution(0.0, 1.0)<In.GNprmin) return In.GNrmin;
    return In.GNrmax;
    
  case RUNIF: return UniformDistribution(In.GNrmin, In.GNrmax);

  case RCEXP: return CenteredExponentialDistribution( 1./In.GNrmin, In.GNrmax);

  case RBPL: return BoundedPowerDistribution( -2.0, In.GNrmin, In.GNrmax);

  default: return In.GNrmin;

  }
}
#undef DL
