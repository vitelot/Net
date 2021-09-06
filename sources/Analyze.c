#include "main.h"
#include "extern.h"

extern void DegreeDistribution ( NODE *node, Int NK);
extern void ClusterCoeff       ( NODE *node, Int NK);
extern void ClusterCoeff2NN    ( NODE *node, Int NK);
extern void ClusterCoeff2NNstar( NODE *node, Int NK);
extern void NeighConnect       ( NODE *node, Int NK);
extern void SiteTraffic        ( NODE *node, Int NK);
extern void ConnectedComponents( NODE *node, Int NK);
extern void SiteBetweenness    ( NODE *node, Int NK);
extern Int  EdgeBetweenness    ( NODE *node, Int NK);
extern void RWSiteBetweenness  ( NODE *node, Int NK);
extern void Communities        ( NODE *node, Int NK);
extern void AMatrixStuff       ( NODE *node, Int NK);
extern void Lanczos            ( NODE *node, Int NK);
extern void SCC                ( NODE *node, Int NK);

void Analyze( NODE *node, Int NK)
{

  DegreeDistribution( node, NK);

  NeighConnect( node, NK);

  ClusterCoeff( node, NK);

  ClusterCoeff2NN( node, NK);
  ClusterCoeff2NNstar( node, NK);

  ConnectedComponents(node, NK);

/*    SiteTraffic( node, NK); */
  SiteBetweenness  ( node, NK);
  RWSiteBetweenness( node, NK);
  EdgeBetweenness  ( node, NK);

  Communities( node, NK);

  SCC( node, NK);

  AMatrixStuff( node, NK);
  Lanczos( node, NK);

}
