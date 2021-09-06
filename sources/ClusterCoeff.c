#include "main.h"
#include "extern.h"

void ClusterCoeff( NODE *node, Int NK)
{
  register Int i,j,n;
  Int *nnlst, *Nn, *DD;
  Int Nnode, cc;
  Int Kn, K;
  Real *CCk, *CCi;
  Real average=0;
  char file[128];
  FILE *fp;

  if(!In.clcoeff) return;
  if(In.nettype) {
    printf(
	   "No Transitivity Definition for directed graphs available.\n"
	   "Skipping Clustering coefficient calculations.\n");
    return;
  }

  DD    = IntVectorAlloc(NK);
  nnlst = IntVectorAlloc(NK);
  CCk = RealVectorAlloc( NK);
  CCi = RealVectorAlloc( NK);

  sprintf(file, "=%s.%s.dat", In.projname, "ClusterCoefficient");
  printf("Calculating the Clustering Coefficient. Output on file \"%s\".\n",
	 file);

  IntVectorInit(   DD, NK, 0);
  RealVectorInit( CCk, NK, 0.0);

  Loop(i,NK) {
    Dots( '.', i, 1+(NK>>6));
    K = GetNodeDegree( &node[i]);
    ++DD[K]; /* build the degree distribution */
    if(K<=1) { CCi[i] = 0; continue; }
    
    Nn = node[i].links; /*  get the list of neighbors of node i */
    /* initialize only what one needs for node i */
    Loop(j,K) nnlst[ Nn[j] ] = 0;

    Loop(j,K) {
      Nnode = Nn[j]; /* scan each nearest neighb */
      Kn = GetNodeDegree( &node[Nnode] ); /* its degree */
      /* only those which were set to zero will be significant later,
	 the rest does not matter */
      Loop(n,Kn) nnlst[ node[Nnode].links[n] ]++;
    }

    cc = 0;
    Loop(j,K) cc += nnlst[ Nn[j] ]; /* here they are counted */

    CCi[i] = (Real) cc /( (Real) K*(K-1));
    average += CCi[i];

    CCk[K] += CCi[i];
  }

  Loop(K,NK)
    if((cc=DD[K])!=0) CCk[K] /= (Real) DD[K];

  printf("\nAverage Node Cluster Coefficient: %g\n\n", average / NK);

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%10s\t%10s\t%10s\n", "k,i", "CC(k)", "CC(i)", "Fitness(i)");
  Loop(i,NK) {
    fprintf(fp, "%6d\t%10g\t%10g\t%10g\n",
	    i, CCk[i], CCi[i], ReadNodeFitness(&node[i]));
  }

  fclose(fp);

  if(In.multi==1)
    RunXmgrace(NULL, CCk, INT,REAL, NK,"C(k)", "","");

  IntVectorFree( nnlst);
  IntVectorFree( DD);
  RealVectorFree( CCk);
  RealVectorFree( CCi);
}
