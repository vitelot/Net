#include "main.h"
#include "extern.h"

#define EPS 1e-2
#define NREPS 1e-4 /* newton raphson conv param */
#define L 1.0 /* rest length of springs */
#define W 1.0 /* spring stiffness */
#define Q 0.2 /* charge */

typedef struct { 
  float x,y; /* coordinates */
  float r; /* radius (size) */
  float cr,cg,cb; /* rgb color */
} Point; /* point in the plane */

typedef struct {
  float x,y;
} P2D;

static void SpringCharge( Point *P, NODE *node, Int NK);
static void Force( P2D *force, Int m, Point *P, P2D *V, NODE *node, Int NK);
static float Distance(Point *p, Point *q);
static void GradE(P2D *grad, int m, Point *P, NODE *node, Int NK);
static void MovePoint(int m, Point *P, NODE *node, Int NK);
static float DDExx(int m, Point *P, NODE *node, Int NK);
static float DDEyy(int m, Point *P, NODE *node, Int NK);
static float DDExy(int m, Point *P, NODE *node, Int NK);

void PlacePoints( Point *P, NODE *node, Int NK) {

  SpringCharge( P, node, NK);
  
}

static void SpringCharge( Point *P, NODE *node, Int NK) {

  register int i;
  int m;
  float absgrad, maxabsgrad;
  P2D grade;
  printf("Drawing the network. It will stop below %.1e.\n",EPS);
  /* select point with max gradient */
  do {
    maxabsgrad = 0.0;
    Loop(i,NK) {
      GradE( &grade, i, P, node, NK);
      absgrad = fabs(grade.x)+fabs(grade.y);
      if(maxabsgrad<absgrad) {
	maxabsgrad = absgrad;
	m = i;
      }
    }
    printf("%8.3f\r", maxabsgrad);
/*     printf("# %d %f grad: %g %g\n", m, maxabsgrad, grade.x, grade.y); */
    MovePoint(m, P, node, NK);
  } while(maxabsgrad > EPS);
}

static float Distance(Point *p, Point *q) {

  return sqrt((p->x-q->x)*(p->x-q->x) + (p->y-q->y)*(p->y-q->y));
/*   return fabs(p->x - q->x) + fabs(p->y - q->y); */
}

static void GradE(P2D *grad, int m, Point *P, NODE *node, Int NK) {
  register int j;
  float d, d3, dex, dey;
  int Nn, K = GetNodeDegree(&node[m]);
  
  dex = dey = 0.0;
  /* Spring contribution -nearest neighs- only */
  Loop(j,K) {
    Nn = node[m].links[j];
    d = Distance(&P[m], &P[Nn]);
    d3 = W * (d-L)/d;
    dex += d3 * (P[m].x-P[Nn].x);
    dey += d3 * (P[m].y-P[Nn].y);
  }
  /* Electrostatic contribution */
  if(Q!=0.0) {
    Loop(j,NK) {
      if(j==m) continue;
      d = Distance(&P[m], &P[j]);
      d3 = Q/(d*d*d);
      dex -= d3 * (P[m].x-P[j].x);
      dey -= d3 * (P[m].y-P[j].y);
    }
  }

  grad->x = dex;
  grad->y = dey;
  return;
}

static void MovePoint(int m, Point *P, NODE *node, Int NK) {
  /* moves point m keeping all others fixed */
  int count=40;
  float xm, ym, dxm, dym, delta;
  float ddExx, ddEyy, ddExy;
  P2D z;

  do {
    GradE( &z, m, P, node, NK);
    xm = P[m].x;
    ym = P[m].y;
    ddExx = DDExx(m, P, node, NK);
    ddExy = DDExy(m, P, node, NK);
    ddEyy = DDEyy(m, P, node, NK);

    delta = ddExx*ddEyy-ddExy*ddExy;
/*     printf("delta %g\n", delta); */
    dxm = (z.x*ddEyy - z.y*ddExy)/delta;
    dym = (z.y*ddExx - z.x*ddExy)/delta;
    P[m].x -= dxm;
    P[m].y -= dym;
  } while(count-- && fabs(dxm)+fabs(dym)>NREPS);
}

static float DDExx(int m, Point *P, NODE *node, Int NK) {
  register int j;
  float d, dex;
  int Nn, K = GetNodeDegree(&node[m]);
  
  dex = 0.0;
  /* Spring contribution -nearest neighs- only */
  Loop(j,K) {
    Nn = node[m].links[j];
    d = Distance(&P[m], &P[Nn]);
    dex += W * (1.0 - L * (P[m].y-P[Nn].y)*(P[m].y-P[Nn].y)/(d*d*d));
  }
  /* Electrostatic contribution */
  if(Q!=0.0) {
    Loop(j,NK) {
      if(j==m) continue;
      d = Distance(&P[m], &P[j]);
      dex -= Q * (1.0 - 3.0*(P[m].x-P[j].x)*(P[m].x-P[j].x)/(d*d))/(d*d*d);
    }
  }

  return dex;
}

static float DDEyy(int m, Point *P, NODE *node, Int NK) {
  register int j;
  float d, dey;
  int Nn, K = GetNodeDegree(&node[m]);
  
  dey = 0.0;
  /* Spring contribution -nearest neighs- only */
  Loop(j,K) {
    Nn = node[m].links[j];
    d = Distance(&P[m], &P[Nn]);
    dey += W * (1.0 - L * (P[m].x-P[Nn].x)*(P[m].x-P[Nn].x)/(d*d*d));
  }
  /* Electrostatic contribution */
  if(Q!=0.0) {
    Loop(j,NK) {
      if(j==m) continue;
      d = Distance(&P[m], &P[j]);
      dey -= Q * (1.0 - 3.0*(P[m].y-P[j].y)*(P[m].y-P[j].y)/(d*d))/(d*d*d);
    }
  }

  return dey;
}

static float DDExy(int m, Point *P, NODE *node, Int NK) {
  register int j;
  float d, dexy;
  int Nn, K = GetNodeDegree(&node[m]);
  
  dexy = 0.0;
  /* Spring contribution -nearest neighs- only */
  Loop(j,K) {
    Nn = node[m].links[j];
    d = Distance(&P[m], &P[Nn]);
    dexy += W * L * (P[m].x-P[Nn].x)*(P[m].y-P[Nn].y)/(d*d*d);
  }
  /* Electrostatic contribution */
  if(Q!=0.0) {
    Loop(j,NK) {
      if(j==m) continue;
      d = Distance(&P[m], &P[j]);
      dexy += Q * 3.0*(P[m].x-P[j].x)*(P[m].y-P[j].y)/(d*d)/(d*d*d);
    }
  }

  return dexy;
}
