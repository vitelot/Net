/* random walk site-betweenness as defined
 *   by M.E.J. Newman, cond-mat/0309045
 *   requires GSL libraries
 */

/* #define GSL */

#include "main.h"
#include "extern.h"

#ifndef GSL
void RWSiteBetweenness(NODE * node, Int NK)
{
  if(!In.rwsitebetw) return;

  printf("Sorry, you do not have the gsl libraries installed.\n");
  printf("You cannot perform calculations of the Random Walk Betweenness .\n\n");
}
#else

#include <gsl/gsl_linalg.h>

#define CONDUCTANCE 1 /* link weights are conductances */
#define RESISTANCE  2 /* link weights are resistances */

#define ALLOUT 0

static void BCprint( NODE *node, Int NK, Real *BCi);
static gsl_matrix * CreateL0(NODE * node, Int NK);
static void OneIn_OneOut(NODE *node, Int NK, Real *BCi, gsl_matrix *L0_inverse);
static void OneIn_AllOut(NODE *node, Int NK, Real *BCi, gsl_matrix *L0_inverse);

void RWSiteBetweenness( NODE *node, Int NK) {
  if(!In.rwsitebetw) return;

{ 
  Real tmp;
  Real *BCi = RealVectorAlloc( NK);
  gsl_matrix *L0 =  CreateL0( node, NK);
  gsl_matrix *L0_inverse = gsl_matrix_alloc( NK-1, NK-1);
  gsl_permutation *P = gsl_permutation_alloc( NK-1);
  int signum;


  if(In.rwsitebetw==CONDUCTANCE)
    printf("\nCalculating the Random-Walk Site Betweennes Centrality with link weights as conductances.\n");
  if(In.rwsitebetw==RESISTANCE)
    printf("\nCalculating the Random-Walk Site Betweennes Centrality with link weights as resistances.\n");
/*   printf("[-------------------------------------------------------------]\n"); */

  if(ALLOUT)
    printf("One source and N-1 sinks at time.\n");
  else
    printf("One source and one sink at time.\n");


  printf("Calculating the LU decomposition of the generalized Laplacian matrix.\n");
  gsl_linalg_LU_decomp( L0, P, &signum);

  printf("Checking whether the determinant is not zero: ");
  tmp = gsl_linalg_LU_det ( L0, signum);
  printf("DET = %g\n", tmp);
  if(tmp==0.0) {
    printf("Determinant is zero. Please split all graph components. Return.\n");
    return;
  }

  printf("Calculating the inverse of the previous LU decomposition.\n");
  gsl_linalg_LU_invert( L0, P, L0_inverse);

  if(ALLOUT) OneIn_AllOut( node, NK, BCi, L0_inverse);
  else       OneIn_OneOut( node, NK, BCi, L0_inverse);

  BCprint( node, NK, BCi);

  gsl_matrix_free(L0);
  gsl_matrix_free(L0_inverse);
  RealVectorFree( BCi);

 }}

static int sortfn( const Real * a, const Real * b);

static void BCprint( NODE *node, Int NK, Real *BCi)
{
register int i,j;
Real *BCiSorted, *BCk, *BCki;
Int *DD, *DDin, *Kin, K, Ki, *NnList;
Real average=0;
char file[128];
FILE *fp;

 Loop( i, NK) if(fabs(BCi[i])<1e-9) BCi[i]=0.0; /* clean spurious small terms */

 if(ALLOUT)
   sprintf(file, "=%s.%s.dat", In.projname, "RWSiteBetweennessOA");
 else
   sprintf(file, "=%s.%s.dat", In.projname, "RWSiteBetweenness");
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
  printf("Average Random Walk Site Betweenness Centrality: %g\n\n", average);

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
      RunXmgrace(NULL, BCk , INT, REAL, NK,"B\\Srw\\N\\ssite\\N(k\\sout\\N)","","");
      RunXmgrace(NULL, BCki, INT, REAL ,NK,"B\\Srw\\N\\ssite\\N(k\\sin\\N)", "","");
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
      RunXmgrace(NULL, BCk, INT, REAL, NK, "B\\Srw\\N\\ssite\\N(k)", "","");

  }

  RealVectorFree( BCiSorted);
  RealVectorFree( BCk);
  IntVectorFree( DD);
}

static int sortfn( const Real * a, const Real * b)
{ /* sorts in descending order */
  if(*a==*b) return 0;
  return ((*a>*b)?-1:1);
}

/* allocate and create laplacian matrix with last
   row and column missing. I.e. potential of last
   node is set to 0
*/
static gsl_matrix * CreateL0(NODE * node, Int NK) {
  register Int i, j;
  Int K, *L;
  gsl_matrix *A = gsl_matrix_calloc (NK-1, NK-1); /* connectivity matrix, initialized to 0 already */

  if(!In.weighted) {
    /* Laplacian: D-A */
    /*    printf("Building the Laplacian matrix of the graph: D - A\n"); */
    Loop(i,NK-1) {
      K = GetNodeDegree( &node[i]);
      L = node[i].links;
      gsl_matrix_set( A, i,i, K);
      Loop(j,K) {
	if(L[j]!=NK-1) /* last node is not considered */
	  gsl_matrix_set( A, i,L[j], -1.0);
      }
    }
  } else {
    Real W;
    /*    printf("Building the Weighted Laplacian matrix of the graph: S - W\n"); */
    Loop(i,NK-1) {
      K = GetNodeDegree( &node[i]);
      L = node[i].links;
      W = 0.0;
      Loop(j,K) {
	if(In.rwsitebetw==CONDUCTANCE)
	  W += node[i].weights[j]; /* strenght is the sum of link weights */
	if(In.rwsitebetw==RESISTANCE)
	  W += 1.0/node[i].weights[j]; /* strenght is the sum of link weights */
      }
      gsl_matrix_set( A, i,i, W);
      Loop(j,K) {
	if(L[j]!=NK-1) {/* last node is not considered */
	  W = node[i].weights[j];
	  if(In.rwsitebetw==RESISTANCE)
	    W = 1.0/W;
	  gsl_matrix_set( A, i,L[j], -W);
	}
      }
    }
  }
  
  return A;
}

static void OneIn_OneOut(NODE *node, Int NK, Real *BCi, gsl_matrix *L0_inverse) {
  register int s,t,v,j;
  Int K, *L;
  Real W, tmp;
  Real *Potential = RealVectorAlloc( NK);

  RealVectorInit( BCi, NK, 0.0);

  Loop( s, NK) { /* Loop over all pairs */
    Loop( t, s) { /* s=source t=well */
      Loop( v, NK-1) { /* Loop over all nodes but the last one */
	if(s==NK-1)
	  Potential[v] =  - gsl_matrix_get ( L0_inverse, v, t);
	else
	  Potential[v] = gsl_matrix_get ( L0_inverse, v, s) - gsl_matrix_get ( L0_inverse, v, t);
      }
      Potential[NK-1] = 0.0; /* potential of last node is set to 0 */
      /* calculate currents */
      Loop(v, NK) {
	K = GetNodeDegree( &node[v]);
	L = node[v].links;
	tmp = 0.0;
	/* one of the following 2 lines must be commented out */
	/*	if(v==s || v==t) tmp = 1; // source and well are counted */
	if(v==s || v==t) tmp = -1; /*// source and well are not counted*/
	Loop(j,K) {
	  W = 1.0;/* conductance */
	  if(In.weighted) {
	    W = node[v].weights[j];
	    if(In.rwsitebetw==RESISTANCE) W = 1.0/W;
	  }
	  tmp += fabs(Potential[v]-Potential[L[j]])*W;
	}
	BCi[v] += tmp/2.0;
/* 	printf("### s%d t%d v%d iv=%f Pv=%f\n", s,t,v,tmp, Potential[v]); */
      }
    }
  }
  Loop(v, NK) BCi[v] *= 2.0/(NK-2)/(NK-1); /* normalization */
  RealVectorFree( Potential);

}

static void OneIn_AllOut(NODE *node, Int NK, Real *BCi, gsl_matrix *L0_inverse) {
  register int s,t,v,j;
  Int K, *L;
  Real W, tmp;
  Real *Potential = RealVectorAlloc( NK);

  RealVectorInit( BCi, NK, 0.0);

  Potential[NK-1] = 0.0; /* potential of last node is set to 0 */
  
  Loop( s, NK) { /* Loop over all nodes, one source s at time */
    Loop( v, NK-1) { /* Loop over all nodes but the last one */
      Potential[v] = 0.0;
      Loop(t, NK-1) {
	if(t!=s)
	  Potential[v] -= gsl_matrix_get ( L0_inverse, v, t);
      }
      Potential[v] /= NK-1.0;
      if(s!=NK-1) Potential[v] += gsl_matrix_get ( L0_inverse, v, s);
    }
    /* calculate currents */
    Loop(v, NK) {
      K = GetNodeDegree( &node[v]);
      L = node[v].links;
      tmp = 0.0;
      /* one of the following 2 lines must be commented out */
      /* if(v==s) tmp =  1; else tmp =  1.0/(NK-1.0);  source and well are counted*/
      if(v==s) tmp = -1; else tmp = -1.0/(NK-1.0); /* source and well are not counted*/
      Loop(j,K) {
	W = 1.0;/* conductance */
	if(In.weighted) {
	  W = node[v].weights[j];
	  if(In.rwsitebetw==RESISTANCE) W = 1.0/W;
	}
	tmp += fabs(Potential[v]-Potential[L[j]])*W;
      }
      BCi[v] += tmp/2.0;
      /* 	printf("### s%d t%d v%d iv=%f Pv=%f\n", s,t,v,tmp, Potential[v]); */
    }
  }

  Loop(v, NK) BCi[v] *= 1.0/(NK-1); /* normalization */
  RealVectorFree( Potential);

}

#undef CONDUCTANCE
#undef RESISTANCE
#undef ALLOUT

#endif /* GSL */
