#include "main.h"
#include "extern.h"

extern void DistanceDistrib( Int s, Int *d, Int NK);

static void BCprint( NODE *node, Int NK, Real *BCi);

struct MD {
  int dist;
  Int from;
  Int to;
};
static void GetMaxDistance( Int from, struct MD *MaxDistance, Int *d, Int NK);
static void InitMaxDistance( struct MD *MaxDistance);

void SiteBetweenness( NODE *node, Int NK)
/* Brandes algorithm */
{
register Int s,v,w, i;
Int k;
Int *sigma, *d;
Int * ClusterSize;
Real *delta;
Real *BCi;
Real minBCi, maxBCi;
Int minidx, maxidx;
STACK S;
LIST *P;
QUEUE Q;
struct MD MaxDistance;

  if(!In.sitebetw) return;

  printf("Calculating the Site Betweennes Centrality.\n");
  printf("[-------------------------------------------------------------]\n");

  BCi  = RealVectorAlloc( NK);
  ClusterSize = IntVectorAlloc( NK);/* number of nodes of the belonging cluster */

  sigma =  IntVectorAlloc( NK);/* number of shortest paths between w and s */
  d     =  IntVectorAlloc( NK);/* distance from s */
  delta = RealVectorAlloc( NK);

  P = ListAlloc( NK); /* create and initialize LIST P[w] */
  ListInit( P, NK); /* P[w] = list of predecessor of w coming from s */

  StackInit( &S);

  QueueInit( &Q);

  IntVectorInit( ClusterSize, NK, 0);
  RealVectorInit( BCi, NK, 0.0);

  InitMaxDistance( &MaxDistance);

  Loop( s, NK) {
    StackEmpty( &S);
    ListEmpty( P, NK);
    IntVectorInit( sigma, NK, 0); sigma[s] = 1;
    IntVectorInit(     d, NK,-1);     d[s] = 0;
    QueueEmpty( &Q);

    enQueue( &Q, s);

    while( QueueSize( &Q)) {
      v = deQueue( &Q);
      StackPush( &S, v);
      k = GetNodeDegree( &node[v]);
      for( i=0; i<k; i++) { /* browse v's nearest neighbors */
	w = node[v].links[i];
	if( d[w] < 0) { /*  w found for the first time? */
	  enQueue( &Q, w);
	  d[w] = d[v] + 1;
	}
	if( d[w] == d[v] + 1) { /* shortest path to v via w? */
	  sigma[w] = sigma[v] + sigma[w];
	  IntListAppend( &P[w], v);
	}
      }
    }

    DistanceDistrib( s, d, NK);
    GetMaxDistance( s, &MaxDistance, d, NK);

    RealVectorInit( delta, NK, 0.0);
/*      S returns vertices in order of non-increasing distance from s */
    while( StackSize( &S)) {
      w = StackPop( &S);
      k = IntListSize( &P[w]);
      for( i=0; i<k; i++) {
	v = P[w].list[i];
	delta[v] += (Real) sigma[v]/ (Real) sigma[w] * (1.0+delta[w]);
      }
      if( w != s) BCi[w] += 0.5*delta[w];
    }
    Dots( '+', s, 1+(NK>>6));
  }
  printf("\n");

  Loop(i, NK) BCi[i] *= 2.0/(NK-2)/(NK-1); /* normalization */

  BCprint( node, NK, BCi);

  maxBCi=minBCi=BCi[0];
  maxidx=minidx=0;
  Loop(i,NK) {
    if(BCi[i]>maxBCi) { maxBCi=BCi[i]; maxidx=i; }
    if(BCi[i]<minBCi) { minBCi=BCi[i]; minidx=i; }
  }

  printf("Net Diameter: %d (from node %d to node %d).\n\n",
	 MaxDistance.dist, MaxDistance.from, MaxDistance.to );
  printf("Max Site Betweenness value: %g at node number %d\n", maxBCi, maxidx);
  printf("Min Site Betweenness value: %g at node number %d\n", minBCi, minidx);

  IntVectorFree( ClusterSize);
  IntVectorFree( sigma);
  IntVectorFree(     d);
  RealVectorFree(delta);
  ListFree( P, NK);

  RealVectorFree( BCi);
}

static int sortfn( const Real * a, const Real * b);

static void BCprint( NODE *node, Int NK, Real *BCi)
{
register int i,j;
Real *BCiSorted, *BCk, *BCki;
Int *DD, *DDin, *Kin, K, Ki, *NnList;
Real average=0;
char file[128];
FILE *fp;

 sprintf(file, "=%s.%s.dat", In.projname, "SiteBetweenness");
 printf("Output on file \"%s\".\n", file);

  BCk  = RealVectorAlloc( NK);

  DD    = IntVectorAlloc(NK);
  IntVectorInit(   DD, NK, 0);

  RealVectorInit( BCk, NK, 0.0);
  Loop(i,NK) {
    K = GetNodeDegree( &node[i]);
    ++DD[K]; /* build the degree distribution */
    BCk[K] += BCi[i];
  }
  Loop(i,NK) {
    average += BCi[i];
    if( DD[i])
      BCk[i] /= (Real)DD[i];
  }
  average /= NK;
  printf("Average Site Betweenness Centrality: %g\n\n", average);

  BCiSorted = RealVectorAlloc( NK);
  RealVectorCopy( BCiSorted, BCi, NK);
  qsort( &BCiSorted[0], NK, sizeof(Real),
	 (int (*)(const void *, const void *)) sortfn);

  if(In.nettype) { /* directed graph */

    BCki  = RealVectorAlloc( NK);
    Kin = IntVectorAlloc(NK);
    DDin = IntVectorAlloc(NK);

    RealVectorInit( BCki, NK, 0.0);
    IntVectorInit( Kin, NK, 0);
    IntVectorInit( DDin, NK, 0);

    /* build the node in-degree table */
    Loop(i,NK) {
      K = GetNodeDegree(&node[i]);
      NnList = node[i].links;
      Loop(j,K) {
	++Kin[ NnList[j] ];
      }
    }

    Loop(i,NK) {
      Ki = Kin[i];
      ++DDin[Ki]; /* build the in degree distribution */
      BCki[Ki] += BCi[i];
    }
    Loop(i,NK)
      if( DDin[i] )
	BCki[i] /= (Real)DDin[i];

    fp = fopen( file, "w");
    if( !fp)  FileOpenError(file);
    fprintf(fp, "#%9s\t%13s\t%13s\t%10s\t%10s\t%10s\n",
	    "ko,ki,i", "BC(kout)", "BC(kin)", "BC(i)", "Fitness(i)", "BC(i)[Sorted]");
    Loop(i,NK) {
      fprintf(fp, "%10d\t%13g\t%13g\t%10g\t%10g\t%10g\n",
	      i, BCk[i], BCki[i], BCi[i], ReadNodeFitness(&node[i]), BCiSorted[i]);
    }
    fclose(fp);

    if(In.multi==1) {
      RunXmgrace(NULL, BCk , INT, REAL, NK,"B\\ssite\\N(k\\sout\\N)","","");
      RunXmgrace(NULL, BCki, INT, REAL ,NK,"B\\ssite\\N(k\\sin\\N)", "","");
    }

    RealVectorFree( BCki);
    IntVectorFree( DDin);
    IntVectorFree( Kin);

  } else {

    fp = fopen( file, "w");
    if( !fp)  FileOpenError(file);
    fprintf(fp, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	    "k,i", "BC(k)", "BC(i)", "Fitness(i)", "BC(i)[Sorted]");
    Loop(i,NK) {
      fprintf(fp, "%6d\t%10g\t%10g\t%10g\t%10g\n",
	      i, BCk[i], BCi[i], ReadNodeFitness(&node[i]), BCiSorted[i]);
    }
    fclose(fp);
    
    if(In.multi==1)
      RunXmgrace(NULL, BCk, INT, REAL, NK, "B\\ssite\\N(k)", "","");

  }

  RealVectorFree( BCiSorted);
  RealVectorFree( BCk);
  IntVectorFree( DD);
}

static void InitMaxDistance( struct MD *MaxDistance)
{ MaxDistance->dist = MaxDistance->from = MaxDistance->to = -1; }

static void GetMaxDistance( Int from, struct MD *MaxDistance, Int *d, Int NK)
{
  register Int i;

  Loop(i,NK) {
    if( d[i] > MaxDistance->dist) {
      MaxDistance->dist = d[i];
      MaxDistance->from = from;
      MaxDistance->to   = i;
    }
  }
}

static int sortfn( const Real * a, const Real * b)
{ /* sorts in descending order */
  if(*a==*b) return 0;
  return ((*a>*b)?-1:1);
}
