#include "main.h"
#include "extern.h"

void NodeInitFitnesses( NODE *node, Int NK, enum RndDistrib RDType, Real p1, Real p2)
{
  register Int i;
  Real x;

/*    if(In.nettype) { */
/*      perr("No fitness model is implemented for directed networks yet. Sorry.\n"); */
/*      exit(1); */
/*    } */
/*    if(In.weighted) { */
/*      perr("No fitness model is implemented for weighted networks yet. Sorry.\n"); */
/*      exit(1); */
/*    } */

  Loop(i,NK) {
    x = GetRandom( RDType, p1, p2);
    SetNodeFitness( &node[i], x);
  }
}
