#include "main.h"
#include "extern.h"

extern Real UniformDistribution( Real min, Real max);
extern Real LinkProbability( Real x, Real y, Real Z, Real E, Real m);

static Real Weight(Real x1, Real x2) { return sqrt(x1*x2); }

void AssignLinks( NODE *node, Int NK)
{
  register Int i,j;
  Real x, xi,xj, p;
  Real Z, m, E;
  double exetime;

  int doTree = In.tree;
  int doAcyclic = In.acyclic;

  Z = In.cutoff;
  m = In.m;
  E = In.E;

  printf("Constructing the net based on the FITNESS model:\n");
  exetime  = Timer();

  if(In.nettype==1) { /* directed net */
    printf("DIRECTED net:\n");
    Loop(i,NK) {
/*       Dots( '.', i, 1+(NK>>6)); */
      ShowProgress( i, NK);
      xi = ReadNodeFitness( &node[i]);
      Loop(j,NK) {
	if(i==j) continue;
	xj = ReadNodeFitness( &node[j]);
	x = UniformDistribution( 0.0, 1.0);
	p = LinkProbability( xi, xj, Z, E, m);
	if( p >= x) {
	  AddOneWayLink( &node[i], &node[j], Weight(xi,xj)); /*weight=0.0*/
	}
      }
    }

  } else { /* undirected */

    Loop(i,NK) {
/*       Dots( '.', i, 1+(NK>>6)); */
      ShowProgress( i, NK);
      xi = ReadNodeFitness( &node[i]);
      for( j=0; j<i; ++j) {
	if( doTree) {
	  if( GetNodeDegree(&node[i]) ) break; /* a new node connects only once  */
	  else j = (Int) UniformDistribution( 0.0, i); /* node 0 has more connections */
	}
	/* if node i and j have at least a common neighbor do not connect them */
	if( doAcyclic && HaveCommonNeighbor(&node[i], &node[j], NK)) break;

	xj = ReadNodeFitness( &node[j]);
	x = UniformDistribution( 0.0, 1.0);
	p = LinkProbability( xi, xj, Z, E, m);
	if( p >= x) {
	  AddTwoWayLink( &node[i], &node[j], Weight(xi,xj)); /*weight=0.0*/
	}
      }
    }
  }
  exetime = Timer() - exetime;
  printf("  Done.      \nElapsed Time: %lf sec.\n\n", exetime);
}

