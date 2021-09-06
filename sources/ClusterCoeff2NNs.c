#include "main.h"
#include "extern.h"

/* Transitivity only for 2nd neighbors:
   Fraction of 2nd neighs that are 1st neighs each other */
void ClusterCoeff2NNstar( NODE *node, Int NK)
{
  register Int i, j0,j1, j,jmax, TK, N1,N2;
  Int K0, K1, Dimnnlst;
  Int *DD, *DD2, *NN2, *NN2Edges, *edges, *done, *nnlst;
  Int *Nn0, *Nn1;
  Real *CCk, *CCi, *CuDD2;
  Real cc, average=0;
  char file[128];
  FILE *fp;
  
  if(!In.cl2coeff) return;
  if(In.nettype) {
    printf(
	   "No Transitivity Definition for directed graphs available.\n"
	   "Skipping Clustering coefficient calculations.\n");
    return;
  }

  DD       =  IntVectorAlloc(NK);
  DD2      =  IntVectorAlloc(NK); /* distrib of 2nd nearest neighs */
  CuDD2    = RealVectorAlloc(NK); /* cumulative distrib of 2nd nearest neighs */
  NN2      =  IntVectorAlloc(NK);
  NN2Edges =  IntVectorAlloc(NK);
  nnlst    =  IntVectorAlloc(Dimnnlst=NK);
  edges    =  IntVectorAlloc(NK);
  done     =  IntVectorAlloc(NK);
  CCk      = RealVectorAlloc(NK);
  CCi      = RealVectorAlloc(NK);

  sprintf(file, "=%s.%s.dat", In.projname, "ClusterCoefficient2NNs");
  printf("Calculating the Clustering Coefficient for the 2nd neigbors only.\n"
	 "Output on file \"%s\".\n",
	 file);

  IntVectorInit(   DD, NK, 0);
  IntVectorInit(  DD2, NK, 0);
  RealVectorInit( CCk, NK, 0.0);

  Loop(i,NK) {
    Dots( '.', i, 1+(NK>>8));

    Nn0 = node[i].links; /*  get the list of 1st neighbors of node i */
    K0 = GetNodeDegree( &node[i]);
    ++DD[K0]; /* build the degree distribution */
    if(K0<1) { CCi[i] = NN2[i] = NN2Edges[i] = 0; continue; }
    
    /* build list of neighs and initialize only what one needs for node i */
    j=0;
    Loop(j0,K0) {
      N1 = Nn0[j0]; /* scan each nearest neighb */

/*        if( j == Dimnnlst) */
/*  	nnlst = IntVectorRealloc( nnlst, Dimnnlst+=NK); */

/*        nnlst[j++] = N1;  add 1st neighs to the list */
/*        edges[ N1 ] = 0; */

/*        done[N1] = 1;  skip 1st neighs */

      Nn1 = node[N1].links; /* get the list of 2nd neighbors of node i */
      K1 = GetNodeDegree( &node[N1]);
      Loop(j1,K1) {
	N2 = Nn1[j1];
	done[N2] = 0;
	if( j == Dimnnlst)
	  nnlst = IntVectorRealloc( nnlst, Dimnnlst+=NK);
	nnlst[j++] = N2; /* add 2nd neighs to the list */
	edges[ N2 ] = 0;
      }
    }
    jmax = j;

    /* set the number of edges coming into each node */
    Loop(j0,K0) { N1 = Nn0[j0]; done[N1] = 1; }/* skip 1st neighs */
    done[i] = 1; /* do not parse the node i */
    Loop(j,jmax) {
      N1 = nnlst[j]; /* for each 2nd neighbor */
      if(!done[N1]) { /* only true 2nd neighs and only once */
	K1 = GetNodeDegree( &node[N1]);
	done[N1] = 1;
	Nn1 = node[N1].links;
	Loop(j1,K1) {
	  N2 = Nn1[j1]; /* set edges to what pointed from up the 2nd neighbhood */
	  edges[ N2 ]++;
	}
      }
    }

    Loop(j,jmax) done[ nnlst[j] ]=0; /* reset the parsing */
    Loop(j0,K0) { N1 = Nn0[j0]; done[N1] = 1; }/* skip 1st neighs */
    done[i] = 1; /* do not parse the node i */
    

    /* count edges and number 2nd neighbors */
    TK = cc = 0;
    Loop(j,jmax) {
      N1 = nnlst[j]; /* for each 2nd neighbor */
      if(!done[N1]) { /* only once */
	TK++;
	done[N1] = 1;
	cc += edges[ N1 ];
      }
    }

    NN2[i] = TK; /* total number of 2nd neighs */
    NN2Edges[i] = cc/2;
    if( TK>1) CCi[i] = (Real) cc /( (Real) TK*(TK-1));
    average += CCi[i];
    CCk[K0] += CCi[i];    
  }

  printf("\nAverage Node Clustering Coefficient2star: %g\n\n", average / NK);

  Loop(i,NK) ++DD2[ NN2[i] ]; /* calc 2nd neighs distrib */
  /* calculate the cumulative distrib */
  CuDD2[NK-1] = (Real) DD2[NK-1];
  for(i=NK-2; i>=0; i--)
    CuDD2[i] = (Real) DD2[i] + CuDD2[i+1];
  /* normalize */
  Loop(i,NK)
    CuDD2[i] /= (Real) NK;

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%7s\t%10s\t%10s\t%8s\t%8s\t%11s\t%10s\n",
	  "i,k,nn2", "CC2s(k)", "CC2s(i)",
	  "NN2(i)", "P(nn2)", "NN2Edges(i)",
	  "Fitness(i)");
  Loop(i,NK) {
    if(DD[i]) CCk[i] /= (Real)DD[i];
    fprintf(fp, "%8d\t%10g\t%10g\t%8d\t%8d\t%11d\t%10g\n",
	    i, CCk[i], CCi[i], 
	    NN2[i], DD2[i], NN2Edges[i],
	    ReadNodeFitness(&node[i]));
  }

  fclose(fp);

  if(In.multi==1) {
    RunXmgrace(NULL, CCk   ,INT,REAL, NK,"C\\s2\\N\\S*\\N(k)","","");
    RunXmgrace(NULL, CuDD2 ,INT,REAL, NK,"Cumulative distribution of 2\\Snd\\N nearest neighbors", "","");
  }

  IntVectorFree(  edges);
  IntVectorFree(  nnlst);
  IntVectorFree(  done);
  IntVectorFree(  DD);
  IntVectorFree(  DD2);
  IntVectorFree(  NN2);
  IntVectorFree(  NN2Edges);
  RealVectorFree( CuDD2);
  RealVectorFree( CCk);
  RealVectorFree( CCi);
}
