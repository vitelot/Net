#include "main.h"
#include "extern.h"

extern void sort2(unsigned long n, Real *arr, Real *brr);

static void SiteBetweenness_local( NODE *node, Real *BCi, Int NK, Int,Int);

void Reduction(NODE *node, Int NK)
{
  if(!In.reduction) return;
{
  register int i, count0=0, count1=0;
  Int *OldDegree = IntVectorAlloc( NK);      /* Degree of nodes before removals */
  Int *Degree  = IntVectorAlloc( NK);      /* Degree of nodes */
  Int *Degree0 = IntVectorAlloc( NK);      /* nodes with degree 0 */
  Int *Degree1 = IntVectorAlloc( NK);      /* nodes with degree 1 */
  Int k, idx, nrdel = NK-In.reduction;             /* nr of nodes to be deleted */
  Int maxK=0, maxKidx;
  Real *Rank_real = RealVectorAlloc( NK);
  Real *BCi = RealVectorAlloc( NK);
  FILE *fp;
  char filename[128];

  if(In.reduction >= NK)
    perr("ERROR: number of remaining nodes after reduction may not exceed total node number.\n");

  printf("Performing network reduction up to %d nodes (%3.0f%%).\n",
	 In.reduction, 100.*(float)In.reduction/NK);

  Loop(i,NK) {
    k = OldDegree[i] = GetNodeDegree(&node[i]);
    if(maxK<k) { maxK=k; maxKidx = i; }
  }

  for(i=0; i<NK && count0<nrdel; i++) {
    if(OldDegree[i]==0) Degree0[count0++] = i;
  }
  for(i=0; i<NK && count0+count1<nrdel; i++) {
    if(OldDegree[i]==1) Degree1[count1++] = i;
  }

  sprintf(filename, "=%s_R%d_NodesRemoved", In.projname, In.reduction);
  printf("Saving node removed list into file %s\n", filename);

  fp = fopen(filename, "w");
  if( !fp)  FileOpenError(filename);

  fprintf(fp, "# %d Nodes removed:\n", nrdel); 
  fprintf(fp, "#IDX\tBetw\tDegree\n"); 

  if(count0) {
/*     fprintf(fp, "### Nodes with degree 0:\n"); */
/*     Loop(i,count0) fprintf(fp, "%d\t%g\t0\n", Degree0[i], 0.0); */
    printf("Removed %d isolated nodes (Lowest Site-Betweenness)\n", count0);
  }

  if(count1) {
/*     fprintf(fp, "### Nodes with degree 1\n"); */
    Loop(i,count1) {
/*       fprintf(fp, "%d\t%g\t1\n", Degree1[i], 0.0); */
      DisconnectNode( node, &node[Degree1[i]]);
    }
    printf("Removed %d leaves with degree 1 (Lowest Site-Betweenness)\n", count1);
  }

  if( count0+count1<nrdel ) { /* are there still non trivial nodes to remove? */
    Loop(i,NK) Rank_real[i] = (Real) i+0.001;
    SiteBetweenness_local( node, BCi, NK, maxK, maxKidx); /* calculate site betweennes */
    sort2( NK, BCi, Rank_real);

    /*   Loop(i,NK) */
    /*     printf("##### %6d %16g\n", (Int) Rank_real[i], BCi[i]); */


    Loop(i,NK) Degree[i] = GetNodeDegree(&node[i]);
    fprintf(fp, "### Betwennesses of following nodes are calculated after trivial nodes removals\n");
    fprintf(fp, "# IDX\t%12s\tDeg\tOldDeg\n", "Betw");
    for(i=0; i<nrdel; i++) {
      idx = (Int) Rank_real[i];
      k = Degree[idx];
      fprintf(fp, "%d\t%12g\t%d\t%d\n", idx, BCi[i], k, OldDegree[idx]);
      if(k>0) DisconnectNode( node, &node[idx]);
    }
  }

  fclose(fp);

  printf("\n"); 
 
  IntVectorFree( OldDegree );
  IntVectorFree( Degree );
  IntVectorFree( Degree1);
  IntVectorFree( Degree0);
  RealVectorFree( BCi);
  RealVectorFree( Rank_real);

 }}


static void SiteBetweenness_local( NODE *node, Real *BCi, Int NK,
				   Int maxK, Int maxKidx)
/* Brandes algorithm */
{
  register Int s,v,w, i;
  Int k, mK, mKi;
  Int *sigma, *d;
  Real *delta;
  Real minBCi, maxBCi;
  Int minidx, maxidx;
  STACK S;
  LIST *P;
  QUEUE Q;
  char tmpfile[128];
  FILE *TMP;

  /* if the maximum degree of the net AND the corresponding index 
     differ from that stored in the temporary file, OR the temp
     file does not exist, THEN the betwenness is recalculated  */

  sprintf(tmpfile, "=%s.%d.%s.tmp", In.projname, NK, "SiteBetweenness");
  TMP = fopen(tmpfile, "r");
  if(TMP) {
    fscanf(TMP, "# Max Degree %d at index %d\n", &mK, &mKi);
/*     printf("%d-%d %d---%d\n",mK, maxK,mKi,maxKidx); */
  }

  if(!TMP || (mK!=maxK) || (mKi!=maxKidx)) { /* temp file does not exist or the net has changed */

    if(TMP) fclose(TMP);

    printf("Calculating the Site Betweennes Centrality.\n");
    /*   printf("[-------------------------------------------------------------]\n"); */

    sigma =  IntVectorAlloc( NK);/* number of shortest paths between w and s */
    d     =  IntVectorAlloc( NK);/* distance from s */
    delta = RealVectorAlloc( NK);

    P = ListAlloc( NK); /* create and initialize LIST P[w] */
    ListInit( P, NK); /* P[w] = list of predecessor of w coming from s */

    StackInit( &S);

    QueueInit( &Q);

    RealVectorInit( BCi, NK, 0.0);

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
      /*     Dots( '+', s, 1+(NK>>6)); */
      ShowProgress( s, NK);
    }
    printf("  Done.       \n");

    maxBCi=minBCi=BCi[0];
    maxidx=minidx=0;
    Loop(i,NK) {
      if(BCi[i]>maxBCi) { maxBCi=BCi[i]; maxidx=i; }
      if(BCi[i]<minBCi) { minBCi=BCi[i]; minidx=i; }
    }

    printf("Max Site Betweenness value: %g at node number %d\n", maxBCi, maxidx);
/*     printf("Min Site Betweenness value: %g at node number %d\n", minBCi, minidx); */

    IntVectorFree( sigma);
    IntVectorFree(     d);
    RealVectorFree(delta);
    ListFree( P, NK);

    TMP = fopen( tmpfile, "w");
    if(!TMP) FileOpenError(tmpfile);
    fprintf(TMP, "# Max Degree %d at index %d\n", maxK, maxKidx);
    fprintf(TMP, "# Max Betwenness %g at index %d\n", maxBCi, maxidx);
    Loop(i,NK) {
      fprintf(TMP, "%d\t%g\n", i, BCi[i]);
    }
    fclose(TMP);

  } else { /* temp file exists */
    printf("Temporary file exists. Loading site betwenness values.\n");
    fscanf(TMP, "# Max Betwenness %lg at index %d\n", &maxBCi, &maxidx);
/*     printf("Read max degree: %d  --- Read max betwenness %g\n", mK, maxBCi); */
    Loop(i,NK) {
      fscanf(TMP, "%*d\t%lg\n", &BCi[i]);
    }
    fclose(TMP);
  }

}
