#include "main.h"
#include "extern.h"

struct EDGE {
  Int From;
  Int To;
};

#ifndef LOW_MEMORY /* run brandes algorithm if there is enough memory */

static void BCEprint( struct EDGE *edge, Int TE, Real *BCE);
static Int FindBCEMax(struct EDGE *edge, Int TE, Real *BCE);

Int EdgeBetweenness( NODE *node, Int NK)
/* Brandes algorithm */
{
  if(!In.edgebetw) return -1;
{
register int s,v,w, i,j;
Int k, e, m, TotEdges, conti, retval;
Int **EdgeIdx; /* like node.link but containing edge indices */
Int *sigma, *d;
Real *BCE; /* Edge BC */
STACK S;
LIST *PE;
QUEUE Q, mode;
struct EDGE *edge;
long int totbytes=0;

  printf("Calculating the Edge Betweennes Centrality (EBC).\n");

  /* EdgeIdx[i][j] = Index of jth edge linked to node i 
     i=0...NK-1, j=0...Degree(node[i])-1                */

  TotEdges=0;
  EdgeIdx = (Int **) malloc( NK * sizeof(Int *) );
  if(!EdgeIdx) AllocError("EdgeBetweenness 1");
  totbytes += NK * sizeof(Int *);

  Loop(i,NK) {
    k = GetNodeDegree(&node[i]);
    EdgeIdx[i] = (Int *) malloc( k* sizeof(Int));
    if(!EdgeIdx[i]) AllocError("EdgeBetweenness 2");
    totbytes += k * sizeof(Int);
    Loop(s,k) {
      v = node[i].links[s];
      EdgeIdx[i][s] = TotEdges++;
      /* assign the old index only in case of undirected nets */
      if(v<i && In.nettype==0) {
	for(j=0; node[v].links[j]!=i; j++) ;
	EdgeIdx[i][s] = EdgeIdx[v][j];
	--TotEdges;
      }
    }
  }

  printf("Total number of edges found while calculating EBC: %d\n",TotEdges);
  printf("Allocated %ld bytes for EdgeIdx[][]\n", totbytes);

  BCE  = RealVectorAlloc( TotEdges);
  totbytes += TotEdges * sizeof(Real);;


  sigma =  IntVectorAlloc( NK);/* number of shortest paths between w and s */
  d     =  IntVectorAlloc( NK);/* distance from s */
  totbytes += NK * sizeof(Int);;

  PE = ListAlloc( NK); /* create and initialize LIST P[w] */
  ListInit( PE, NK);
  totbytes += NK * sizeof(LIST);;

  StackInit( &S);

  QueueInit( &Q);
  QueueInit( &mode);

  RealVectorInit( BCE, TotEdges, 0.0);
  totbytes += TotEdges * sizeof(Real);;

  printf("Allocated total of %ld bytes in EdgeBetweenness\n", totbytes);

  Loop( s, NK) {
    StackEmpty( &S);
    ListEmpty( PE, NK);
    IntVectorInit( sigma, NK, 0); sigma[s] = 1;
    IntVectorInit(     d, NK,-1);     d[s] = 0;
    QueueEmpty( &Q);

    enQueue( &Q, s);
    enQueue( &mode, 1);

    while( QueueSize( &Q)) {
      v = deQueue( &Q);
      m = deQueue( &mode);

      if(m) StackPush( &S, v);

      k = GetNodeDegree( &node[v]);
      for( i=0; i<k; i++) { /* browse v's nearest neighbors */

	w = node[v].links[i];
	e = EdgeIdx[v][i];
	conti = 1;

	if( d[w] < 0 && m ) { /*  w found for the first time? */
	  conti = 0;
	  enQueue( &Q, w);
	  enQueue( &mode, 1);
	  d[w] = d[v] + 1;
	}
	if( d[w] == d[v] + 1) { /* shortest path to v via w? */
	  if(m) {
	    sigma[w] += sigma[v];
	    IntListAppendList( &PE[w], &PE[v]);
	  }
	  IntListAppend( &PE[w], e );
	  if(conti) {
	    enQueue( &Q, w);
	    enQueue( &mode, 0);
	  }
	}
      }
    }

/*      S returns vertices in order of non-increasing distance from s */
    while( StackSize( &S)) {
      w = StackPop( &S);
      k = IntListSize( &PE[w]);

      if(In.nettype==0) {
	if(w>s)
	  for( i=0; i<k; i++) {
	    e = PE[w].list[i];
/*  	    printf("S=%4d W=%4d E=%4d\n",s,w,e); */
	    BCE[e] += 2.0/(Real)sigma[w];
	  }
      } else {
	if(w!=s)
	  for( i=0; i<k; i++) {
	    e = PE[w].list[i];
	    BCE[e] += 1.0/(Real)sigma[w];
	  }
      }
/*        Loop(i,NK) { */
/*  	k = IntListSize( &PE[i]); */
/*  	printf("S=%4d I=%4d: ",s,i); */
/*  	Loop(j,k) */
/*  	  printf("%d ",PE[i].list[j]); */
/*  	printf("\n"); */
/*        } */
    }
    Dots( '+', s, 1+(NK>>6));
  }
  printf("\n");

  IntVectorFree( sigma);
  IntVectorFree(     d);
  ListFree( PE, NK);

  edge = (struct EDGE *) malloc( TotEdges * sizeof(struct EDGE));
  if(!edge) AllocError("EdgeBetweenness 3");
  printf("Allocated %d bytes for struct edge\n", TotEdges * sizeof(struct EDGE));
  /* construct edge table */
  Loop(i,NK) {
    k = GetNodeDegree(&node[i]);
    Loop(s,k) {
      edge[ EdgeIdx[i][s] ].From = i;
      edge[ EdgeIdx[i][s] ].To   = node[i].links[s];
    }
  }

  BCEprint( edge, TotEdges, BCE);
  retval = FindBCEMax( edge, TotEdges, BCE);

  Loop(i,NK) free(EdgeIdx[i]);
  free(EdgeIdx);

  free(edge);

  RealVectorFree( BCE);
  
  return retval;
}}

static int sortfn( const Real * a, const Real * b);

static Int FindBCEMax(struct EDGE *edge, Int TE, Real *BCE)
{
register int i;
Real average=0, max=-1, bce;
Int maxe;

 Loop(i,TE) {
   if( (bce = BCE[i])> max) {max=bce; maxe=i;}
   average += bce;
 }
 average /= TE;

 printf("Average Edge Betweenness Centrality: %g\n", average);
 printf("Max Edge Betweenness Centrality %g on Edge #%d from Node %d to Node %d\n\n",
	max, maxe, edge[maxe].From, edge[maxe].To);

 /* returns an int value embedding the from and to node indexes: RETVAL=From*NK+To
    Conversely, From=RETVAL/NK and To=RETVAL%NK                 */
 return edge[maxe].From * In.nk + edge[maxe].To;
}

static void BCEprint( struct EDGE *edge, Int TE, Real *BCE)
{
register int i;
Real *BCESorted;
char file[128];
FILE *fp;

 sprintf(file, "=%s.%s.dat", In.projname, "EdgeBetweenness");
 printf("Output on file \"%s\".\n", file);

 FindBCEMax( edge, TE, BCE);

 BCESorted = RealVectorAlloc( TE);
 RealVectorCopy( BCESorted, BCE, TE);
 qsort( &BCESorted[0], TE, sizeof(Real),
	(int (*)(const void *, const void *)) sortfn);

 fp = fopen( file, "w");
 if( !fp)  FileOpenError(file);

 fprintf(fp, "#%5s\t%6s\t%10s\t%10s\t\n", "FROM", "TO", "BCE", "BCE[Sorted]");
 Loop(i,TE)
   fprintf(fp, "%6d\t%6d\t%10g\t%10g\n", edge[i].From, edge[i].To, BCE[i], BCESorted[i]);
 
 fclose(fp);
 
 RealVectorFree( BCESorted);
}

static int sortfn( const Real * a, const Real * b)
{ /* sorts in descending order */
  if(*a==*b) return 0;
  return ((*a>*b)?-1:1);
}

#else /* LOW_MEMORY true */

Int EdgeBetweenness( NODE *node, Int NK)
/* plain idiot algorithm */
{ if(!In.edgebetw) return -1; {
  return -1;
}}

#endif   /* LOW_MEMORY */
