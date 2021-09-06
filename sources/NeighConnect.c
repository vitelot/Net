#include "main.h"
#include "extern.h"

static void  UndirKnn( NODE *node, Int NK);
static void WUndirKnn( NODE *node, Int NK);
static void   DirKnn( NODE *node, Int NK);
static void OutKnn( NODE *node, Int NK);
static void  InKnn( NODE *node, Int NK);

void NeighConnect( NODE *node, Int NK)
{
  if(!In.knn) return;

  if(In.nettype) DirKnn( node, NK);
  else {
    if(In.weighted) WUndirKnn( node, NK);
    else UndirKnn( node, NK);
  }
}

static void UndirKnn( NODE *node, Int NK)
{
register Int i,j;
Int K, k, Nn;
Int *NnList, *DD;
Real average=0;
Real *Knnk, *Knni;
Real *Knnk2, *Knni2;
Real Kk, Kpk, K2pk2; /* product, sum and sum of squares of degree of nodes connected by link */
Real r; /* assortativity index: PRL 89, 208701*/
Int M=0; /* twice the nr of links */
char file[128], file2[128];
FILE *fp;

  Knnk = RealVectorAlloc( NK);
  Knnk2= RealVectorAlloc( NK);
  Knni = RealVectorAlloc( NK);
  Knni2= RealVectorAlloc( NK);
  RealVectorInit( Knnk,  NK, 0.0);
  RealVectorInit( Knni,  NK, 0.0);
  RealVectorInit( Knnk2, NK, 0.0);
  RealVectorInit( Knni2, NK, 0.0);

  DD   = IntVectorAlloc(NK);
  IntVectorInit(   DD, NK, 0);

  sprintf(file, "=%s.%s.dat", In.projname, "NeighbourConnectivity");
  printf("Calculating the Neighbour Connectivity. Output on file \"%s\".\n",file);
  sprintf(file2, "=%s.%s.dat", In.projname, "NeighbourConnectivity_Pkk");
  printf("Calculating the P(k,k') Neighbour Connectivity. Output on file \"%s\".\n",file2);

  fp = fopen( file2, "w");
  if( !fp)  FileOpenError(file2);

  fprintf(fp, "#%5s\t%6s\t%6s\t%6s\n", 
          "K(i)", "K(j)", "i", "j");

  Kk = Kpk = K2pk2 = 0.0;
  Loop(i,NK) {
    K = GetNodeDegree( &node[i]);
    ++DD[K]; /* build the degree distribution */
    NnList = node[i].links;
    Loop(j,K) {
      Nn = NnList[j];
      /*      printf("%5d %5d\n", i,Nn);  vvvvv */
      k = GetNodeDegree( &node[Nn]);
      Knnk[K]  += (Real) k;
      Knni[i]  += (Real) k;
      Knnk2[K] += ((Real) k)*((Real) k);
      Knni2[i] += ((Real) k)*((Real) k);
      if(i<Nn)
         fprintf(fp, "%6d\t%6d\t%6d\t%6d\n",
                       K, k,
                       GetNodeIndex(&node[i]), GetNodeIndex(&node[Nn]));
      Kk += K*k;
      Kpk += K+k;
      K2pk2 += K*K + k*k;
      M++;
    }
    if( K>0) {
      Knni[i]  /= (Real) K;
      Knni2[i] /= (Real) K;
      Knni2[i] = sqrt(Knni2[i]/(Real) K);
    }
  }
  Kpk /= 2.0; K2pk2 /= 2.0;
  r = (Kk - Kpk*Kpk/M) / (K2pk2-Kpk*Kpk/M);

  Loop(i,NK) {
    average += Knni[i];
    if( i>=1 && DD[i]) {
      Knnk[i]  /= (Real)i * (Real)DD[i];
      Knnk2[i] /= (Real)i * (Real)DD[i];
      Knnk2[i] = sqrt(Knnk2[i] / ((Real)i * (Real)DD[i]));
    }
  }
  printf("Average Node Neighbour-Connectivity: %g\n", average / NK);
  printf("Assortativity index: %g\n\n", r);

  fclose(fp);

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%10s\t%10s\t%10s\t%10s\t%10s\n", 
	  "k,i", "Knn(k)", "VarKnn(k)", "Knn(i)", "VarKnn(i)", "K(i)");
  Loop(i,NK)
    fprintf(fp, "%6d\t%10g\t%10g\t%10g\t%10g\t%10d\n",
	    i, Knnk[i], Knnk2[i], Knni[i], Knni2[i], GetNodeDegree(&node[i]));
  fclose(fp);

  if(In.multi==1)
    RunXmgrace(NULL, Knnk, INT,REAL, NK,"K\\snn\\N(k)","","k");

  IntVectorFree( DD);
  RealVectorFree( Knnk);
  RealVectorFree( Knnk2);
  RealVectorFree( Knni);
  RealVectorFree( Knni2);
}

static void WUndirKnn( NODE *node, Int NK)
{
register Int i,j,l;
Int K, Nn, Kn;
Int *NnList;
Real average=0;
Real *Knni, *WD;
char file[128];
FILE *fp;

  Knni = RealVectorAlloc( NK);
  WD   = RealVectorAlloc( NK);
  RealVectorInit( Knni, NK, 0.0);
  RealVectorInit(   WD, NK, 0.0);

  sprintf(file, "=%s.%s.dat", In.projname, "WNeighbourConnectivity");
  printf("Calculating the Weighted Neighbour Connectivity. Output on file \"%s\".\n",file);

  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    Loop(j,K) {
      WD[i] += node[i].weights[j]; /* degree is the sum of link weights */
    }
    NnList = node[i].links;
    Loop(j,K) {
      Nn = NnList[j]; /* one of the nearest neighs */
      Kn = GetNodeDegree( &node[Nn]); /* its coordination number */
      Loop(l,Kn) Knni[i]  += node[Nn].weights[l];
    }
    if( K>0) {
      Knni[i]  /= (Real) K;
    }
  }

  Loop(i,NK) average += Knni[i];

  printf("Average Node Weighted Neighbour-Connectivity: %g\n\n", average / NK);
   
  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%10s\t%10s\t%10s\n", 
	  "i", "Knn(i)", "w(i)", "Fitness(i)");
  Loop(i,NK)
    fprintf(fp, " %5d\t%10g\t%10g\t%10g\n",
	    i, Knni[i], WD[i], ReadNodeFitness(&node[i]));
  fclose(fp);

  RunXmgrace(WD, Knni, REAL,REAL, NK,"K\\snn\\N(w)", "w", "K\\snn\\N");

  RealVectorFree( WD);
  RealVectorFree( Knni);
}

static void DirKnn( NODE *node, Int NK)
{
  if(In.weighted) {
    printf("Degree correlation with weighted-directed nets is not implemented yet. Sorry.\n");
    return;
  }
  OutKnn( node, NK);
   InKnn( node, NK);
}

static void OutKnn( NODE *node, Int NK)
{
register Int i,j;
Int K, Ki, Nn;
Int *NnList, *DDout, *DDin, *Kin;
Real average=0;
Real *Knnk, *Knnki, *Knni;
char file[128];
FILE *fp;

  Knnk = RealVectorAlloc( NK);
  Knnki= RealVectorAlloc( NK);
  Knni = RealVectorAlloc( NK);
  DDout = IntVectorAlloc(NK);
  DDin  = IntVectorAlloc(NK);
  Kin   = IntVectorAlloc(NK);

  RealVectorInit( Knnk, NK, 0.0);
  RealVectorInit(Knnki, NK, 0.0);
  RealVectorInit( Knni, NK, 0.0);
  IntVectorInit(   DDout, NK, 0);
  IntVectorInit(   DDin , NK, 0);
  IntVectorInit(    Kin , NK, 0);

  sprintf(file, "=%s.%s.dat", In.projname, "OutNeighbourConnectivity");
  printf("Calculating the Out Degree Neighbour Connectivity. Output on file \"%s\".\n",file);

  /* build the node in-degree table */
  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    NnList = node[i].links;
    Loop(j,K) {
      ++Kin[ NnList[j] ];
    }
  }

  Loop(i,NK) {
    K  = GetNodeDegree( &node[i]);
    Ki = Kin[i];
    ++DDout[K]; /* build the out degree distribution */
    ++DDin[Ki]; /* build the in  degree distribution */
    NnList = node[i].links;
    Loop(j,K) {
      Nn = NnList[j];
      Knni [i ] += (Real) GetNodeDegree( &node[Nn]);
    }
    if( K>0)
      Knni[i] /= (Real) K;
    
    Knnk [K ] += Knni[i];
    Knnki[Ki] += Knni[i];

  }

  Loop(i,NK) {
    average += Knni[i];
    if( DDout[i])
      Knnk[i] /= (Real)DDout[i];
    if( DDin[i])
      Knnki[i] /= (Real)DDin[i];
  }
  average /= NK;
  printf("Average Node Out Degree Neighbour-Connectivity: %g\n\n", average);
   
  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%8s\t%14s\t%14s\t%13s\t%10s\n",
	  "ko|ki|i", "OutKnn(ko)", "OutKnn(ki)", "OutKnn(i)", "Fitness(i)");
  Loop(i,NK)
    fprintf(fp, "%9d\t%14g\t%14g\t%13g\t%10g\n",
	    i, Knnk[i], Knnki[i], Knni[i], ReadNodeFitness(&node[i]));
  fclose(fp);

  if(In.multi==1) {
    RunXmgrace(NULL, Knnk , INT,REAL, NK,"K\\snn,out\\N(k\\sout\\N)","","");
    RunXmgrace(NULL, Knnki, INT,REAL, NK,"K\\snn,out\\N(k\\sin\\N)","","");
  }

  IntVectorFree( DDout);
  IntVectorFree( DDin );
  IntVectorFree( Kin  );
  RealVectorFree( Knnk);
  RealVectorFree(Knnki);
  RealVectorFree( Knni);
}

static void InKnn( NODE *node, Int NK)
{
register Int i,j;
Int K, Ki, Nn;
Int *NnList, *Kin, *DDout, *DDin;
Real average=0;
Real *Knnk, *Knnki, *Knni;
char file[128];
FILE *fp;

  Knnk= RealVectorAlloc( NK);
  Knnki= RealVectorAlloc( NK);
  Knni= RealVectorAlloc( NK);
  DDout = IntVectorAlloc(NK);
  DDin  = IntVectorAlloc(NK);
  Kin  = IntVectorAlloc( NK);

  RealVectorInit( Knnk, NK, 0.0);
  RealVectorInit(Knnki, NK, 0.0);
  RealVectorInit( Knni, NK, 0.0);
  IntVectorInit(   DDout, NK, 0);
  IntVectorInit(   DDin , NK, 0);
  IntVectorInit(  Kin, NK, 0);

  sprintf(file, "=%s.%s.dat", In.projname, "InNeighbourConnectivity");
  printf("Calculating the In-Degree Neighbour Connectivity. Output on file \"%s\".\n",file);

  /* build the node in-degree table */
  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    NnList = node[i].links;
    Loop(j,K) {
      ++Kin[ NnList[j] ];
    }
  }

  Loop(i,NK) {
    K = GetNodeDegree( &node[i]);
    Ki = Kin[i];
    ++DDout[K]; /* build the out degree distribution */
    ++DDin[Ki]; /* build the in  degree distribution */
    NnList = node[i].links;
    Loop(j,K) {
      Nn = NnList[j];
      Knni[i] += (Real) Kin[Nn];
    }
    if( K>0)
      Knni[i] /= (Real) K;

    Knnk [K ] += Knni[i];
    Knnki[Ki] += Knni[i];
  }

  Loop(i,NK) {
    average += Knni[i];    
    if( DDout[i] )
      Knnk[i] /= (Real)DDout[i];
    if( DDin[i])
      Knnki[i] /= (Real)DDin[i];
  }
  average /= NK;
  printf("Average Node In-Degree Neighbour-Connectivity: %g\n\n", average);
   
  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%8s\t%13s\t%13s\t%12s\t%10s\n",
	  "ko|ki|i", "InKnn(ko)", "InKnn(ki)", "InKnn(i)", "Fitness(i)");
  Loop(i,NK)
    fprintf(fp, "%9d\t%13g\t%13g\t%12g\t%10g\n",
	    i, Knnk[i], Knnki[i], Knni[i], ReadNodeFitness(&node[i]));
  fclose(fp);

  if(In.multi==1) {
    RunXmgrace(NULL, Knnk , INT,REAL, NK,"K\\snn,in\\N(k\\sout\\N)","","");
    RunXmgrace(NULL, Knnki, INT,REAL, NK,"K\\snn,in\\N(k\\sin\\N)","","");
  }

  IntVectorFree( DDout);
  IntVectorFree( DDin );
  IntVectorFree( Kin  );
  RealVectorFree( Knnk);
  RealVectorFree(Knnki);
  RealVectorFree( Knni);
}
