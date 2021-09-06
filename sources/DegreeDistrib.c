#include "main.h"
#include "extern.h"

static void UndirectedDD( NODE *node, Int NK);
static void WUndirectedDD( NODE *node, Int NK);
static void DirectedDD( NODE *node, Int NK);
static void OutDegreeDistrib(NODE *node, Int NK);
static void InDegreeDistrib(NODE *node, Int NK);

static int sortfn( const Real * a, const Real * b);

void DegreeDistribution( NODE *node, Int NK)
{
  if(!In.degdistr) return;

  if(In.nettype) DirectedDD(node,NK);
  else {
    if(In.weighted) WUndirectedDD(node,NK);
    else UndirectedDD(node,NK);
  }
}

static void UndirectedDD( NODE *node, Int NK)
{
register Int i;
Int *dd, K;
Real average=0, *CuDD;
char file[128];
FILE *fp;

  dd  =  IntVectorAlloc( NK);
  CuDD  =  RealVectorAlloc( NK);
  sprintf(file, "=%s.%s.dat", In.projname, "DegreeDistribution");
  printf("Calculating the Degree Distribution. Output on file \"%s\".\n",file);

  IntVectorInit( dd, NK, 0);
  RealVectorInit( CuDD, NK, 0.0);

  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    ++dd[K];
    average += K;
  }

  printf("Average Node Degree: %g\n\n", average / NK);

  /* calculate the cumulative distrib */
  CuDD[NK-1] = (Real) dd[NK-1];
  for(i=NK-2; i>=0; i--)
    CuDD[i] = (Real) dd[i] + CuDD[i+1];
  /* normalize */
  Loop(i,NK)
    CuDD[i] /= (Real) NK;

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%6s\t%10s\t%6s\t%10s\n",
	  "K,i", "P(K)", "CuP(K)", "K(i)", "Fitness(i)");
  Loop(i,NK)
    fprintf(fp, "%6d\t%6d\t%10g\t%6d\t%10g\n",
	    i, dd[i], CuDD[i], GetNodeDegree(&node[i]), ReadNodeFitness(&node[i]));
  fclose(fp);

  if(In.multi==1) {
    RunXmgrace(NULL, CuDD, INT, REAL, NK,"Cumulative P(k)","","");
    RunXmgrace(NULL, dd  , INT, INT, NK,"P(k)","","");
  }

  IntVectorFree( dd);
  RealVectorFree( CuDD);

}

static void WUndirectedDD( NODE *node, Int NK)
{
  register int i, j;
  Int K, *Pk;
  Real average=0, *wd, *wdsorted, *Wk;
  char file[128];
  FILE *fp;

  wd = RealVectorAlloc( NK); /* strenght for each node */
  Wk = RealVectorAlloc( NK); /* strenght for each k */
  Pk =  IntVectorAlloc( NK); /* P(k) */
  wdsorted  =  RealVectorAlloc( NK);
  sprintf(file, "=%s.%s.dat", In.projname, "WDegreeDistribution");
  printf("Calculating the Weighted Degree Distribution (Strenght). Output on file \"%s\".\n",file);

  IntVectorInit ( Pk, NK, 0);
  RealVectorInit( wd, NK, 0.0);
  RealVectorInit( Wk, NK, 0.0);

  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    ++Pk[K]; /* build topological degree distrib. */
    Loop(j,K) {
      wd[i] += node[i].weights[j]; /* strenght is the sum of link weights */
    }
    Wk[K] += wd[i];
    average += wd[i];
  }

  printf("Average Weighted Node Degree (Strenght): %g\n\n", average / NK);

  Loop(K,NK) {
    if( Pk[K]!=0) Wk[K] /= Pk[K];
  }

  /* calculate the cumulative distrib */
  RealVectorCopy( wdsorted, wd, NK);
  qsort( &wdsorted[0], NK, sizeof(Real),
	 (int (*)(const void *, const void *)) sortfn);

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%16s\t%16s\t%10s\t%10s\t%10s\n",
	  "i,k", "s(k)", "s", "CuP(s)", "s(i)", "Fitness(i)");
  Loop(i,NK)
    fprintf(fp, "%6d\t%16g\t%16g\t%10g\t%10g\t%10g\n",
	    i, Wk[i], wdsorted[i], (Real)(NK-i)/NK, wd[i], ReadNodeFitness(&node[i]));
  fclose(fp);

  if(In.multi==1) {
    Real *CuP = RealVectorAlloc(NK);
    Loop(i,NK) CuP[i] = (Real)(NK-i)/NK;
    RunXmgrace( NULL, Wk, INT,REAL, NK,
		"Strenght as function of node degree",
		"k","s");
    RunXmgrace( wdsorted, CuP, REAL,REAL, NK,
		"Cumulative Strenght Distribution",
		"s","Cumulative P(s)");
    RealVectorFree(CuP);
  }

  RealVectorFree( wd);
  RealVectorFree( Wk);
  RealVectorFree( wdsorted);
  IntVectorFree ( Pk);

}

static void DirectedDD( NODE *node, Int NK)
{
  if(!In.weighted) {
    OutDegreeDistrib(node,NK);
    InDegreeDistrib(node,NK);
  } else {
    printf("No degree distribution calculation for weighted-directed nets is available yet, sorry.\n");
    return;
  }
}

static void OutDegreeDistrib(NODE *node, Int NK)
{
  register Int i;
  Int *dd, K;
  Real average=0;
  char file[128];
  FILE *fp;

  dd  =  IntVectorAlloc( NK);

  sprintf(file, "=%s.%s.dat", In.projname, "OutDegreeDistribution");
  printf("Calculating the Out-Degree Distribution. Output on file \"%s\".\n",file);

  IntVectorInit( dd, NK, 0);

  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    ++dd[K];
    average += K;
  }

  printf("Average Node Out-Degree: %g\n\n", average / NK);

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%8s\t%9s\t%9s\t%10s\n", "Kout,i", "P(Kout)", "Kout(i)", "Fitness(i)");
  Loop(i,NK)
    fprintf(fp, "%9d\t%9d\t%9d\t%10g\n",
	    i, dd[i], GetNodeDegree(&node[i]), ReadNodeFitness(&node[i]));
  fclose(fp);

  if(In.multi==1) {
    RunXmgrace(NULL, dd, INT,INT, NK,"P(k\\sout\\N)","","");
  }

  IntVectorFree( dd);
}

static void InDegreeDistrib(NODE *node, Int NK)
{
register Int i, j;
Int *Kin, *DD, *L, K;
Real average=0;
char file[128];
FILE *fp;

  Kin  = IntVectorAlloc( NK);
  DD   = IntVectorAlloc( NK);

  sprintf(file, "=%s.%s.dat", In.projname, "InDegreeDistribution");
  printf("Calculating the In-Degree Distribution. Output on file \"%s\".\n",file);

  IntVectorInit(   DD, NK, 0);
  IntVectorInit(  Kin, NK, 0);

  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    L = node[i].links;
    Loop(j,K) {
      ++Kin[ L[j] ];
    }
  }

  Loop(i,NK) {
    ++DD[ Kin[i] ];
    average += Kin[i];
  }
  average /= NK;
    
  printf("Average Node In-Degree: %g\n\n", average);

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%6s\t%7s\t%7s\t%8s\t%10s\n", "Kin,i", "P(Kin)", "Kin(i)", "Kout(i)", "Fitness(i)");
  Loop(i,NK)
    fprintf(fp, "%7d\t%7d\t%7d\t%8d\t%10g\n",
	    i, DD[i], Kin[i], GetNodeDegree(&node[i]), ReadNodeFitness(&node[i]));
  fclose(fp);

  if(In.multi==1) {
    RunXmgrace(NULL, DD, INT,INT, NK,"P(k\\sin\\N)", "","");
  }

 IntVectorFree( Kin);
  IntVectorFree( DD);
}

static int sortfn( const Real * a, const Real * b)
{ /* sorts in ascending order */
  if(*a==*b) return 0;
  return ((*a<*b)?-1:1);
}
