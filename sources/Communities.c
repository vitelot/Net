#include "main.h"
#include "extern.h"

/*  #include <unistd.h> */

extern Int EdgeBetweenness( NODE * node, Int NK);

static Int CountCommunities( NODE *node, Int NK, Int oldCN);
static Int EdgeBetwAlgorithm( NODE *node, Int NK);
static Int FindCommunitySize(NODE * node, Int NK, Int s);

FILE *fp;

void Communities( NODE *node, Int NK)
{
register int i=0;
Int FNKT, From, To, FromSize, ToSize;
Int CN=0, oldCN=1;
char file[128];

 if(!In.communities) return; 
  
  sprintf(file, "=%s.%s.txt", In.projname, "Communities");
  printf("Output on file \"%s\".\n", file);
  fp = fopen(file,"w");
  fprintf(fp, "# Sizes of Communities\n");

  oldCN = CN = CountCommunities( node, NK, CN);
  while( CN<NK) {
    FNKT = EdgeBetwAlgorithm(node, NK);
    CN = CountCommunities( node, NK, oldCN);
    if(CN>oldCN) { /* there was a split */
      From = FNKT / NK;
      To   = FNKT % NK;
      FromSize = FindCommunitySize( node, NK, From);
      ToSize   = FindCommunitySize( node, NK,   To);
      fprintf(fp, "%6d\n%6d\n", FromSize, ToSize);
      fflush(fp);
    }
    oldCN = CN;
    ++i;
  }
  fclose(fp);
}

static Int CountCommunities( NODE *node, Int NK, Int oldCN)
{
register Int s, i, CN;
Int k, v, w;
Int * Visited, * CSize;
QUEUE Q;

 QueueInit( &Q);

 CSize = IntVectorAlloc( NK); /* Size of cluster */
 Visited = IntVectorAlloc( NK); /* says if node i was already visited */
 IntVectorInit( Visited, NK, 0);

 CN = 0; /* nr of communities */
 Loop(s,NK) {
   if( !Visited[s] ) { /*  do nothing if S belongs already to a community found before */
     Visited[s]++;
     QueueEmpty( &Q);
     enQueue( &Q, s);
     CSize[CN] = 1;
     while( QueueSize( &Q)) {
       v = deQueue( &Q);
       k = GetNodeDegree( &node[v]);
       for( i=0; i<k; i++) { /* browse v's nearest neighbors */
	 w = node[v].links[i];
	 if( !Visited[w] ) { /*  w found for the first time? */
	   enQueue( &Q, w);
	   Visited[w]++;
	   ++CSize[CN];
	 }
       }
     }
     CN++; /* another community found */
   }
 }

 if(CN>oldCN) { /* there was a split */
/*     DisplayNet( node, NK); sleep(2); */
   printf("Found %d communities with size:\n", CN);
   Loop(s,CN) {
     printf("CCC\t\t %6d\n", CSize[s]);
   }
 }
 else printf("Found %d communities again.\n", CN);
 printf("\n");
 
 IntVectorFree(Visited);
 IntVectorFree(CSize);

 return CN;
}

static Int EdgeBetwAlgorithm(NODE * node, Int NK)
{
  Int FNKT, From, To;

  if(In.edgebetw==0) {
    In.edgebetw=1;
    printf("*** Option EDGE_BETW activated for the community finding algorithm ***\n\n");
  }

  FNKT = EdgeBetweenness(node, NK); /* FNKT = From*NK+To , From->To = Link with max edgebetw */
  From = FNKT / NK;
  To   = FNKT % NK;
/*    printf("Removing link: %d %d\n", From,To); */
  RemoveTwoWayLink( &node[From], &node[To]);

  return FNKT;
}

static Int FindCommunitySize(NODE * node, Int NK, Int s)
     /* find the size of the cluster to which s is belonging */
{
register int i;
Int k, v, w;
Int * Visited, CSize;
QUEUE Q;

 Visited = IntVectorAlloc( NK); /* says if node i was already visited */
 IntVectorInit( Visited, NK, 0);

 QueueInit( &Q);
 Visited[s]++;
 enQueue( &Q, s);
 CSize = 1;
 while( QueueSize( &Q)) {
   v = deQueue( &Q);
   k = GetNodeDegree( &node[v]);
   for( i=0; i<k; i++) { /* browse v's nearest neighbors */
     w = node[v].links[i];
     if( !Visited[w] ) { /*  w found for the first time? */
       enQueue( &Q, w);
       Visited[w]++;
       ++CSize;
     }
   }
 }
 IntVectorFree(Visited);

 return CSize;
}
