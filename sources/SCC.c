/* 
   Strong Connected Component (SCC) finder algorithm (Tarjan 1972).
   Use of recursion: be carefull that the STACK will not overflow
   when lot of nodes are present. In this unfortunate case try
   to use the LINUX bash command "ulimit -s unlimited" to get unlimited
   STACK size.
*/

#include "main.h"
#include "extern.h"

static Int c, *Delta; /* DFS number of node x */
static Int *Root;
static Bool *marked; /* already visited? */
static Bool *InComp; /* is it in a component? */
static STACK stack;
static Int *Size;

static void NodeSCC(NODE *node, Int idx);

void SCC(NODE *node, Int NK) {

  if(!In.scc) return;
  if(!In.nettype) {
    perr(
	 "No SCC calculation for undirected graphs possible.\n"
	 "Skipping SCC calculations.\n");
    return;
  }
{
  register Int i;
  Real avrgSize=0.0;
  Int norm=0, maxSize;
  char file[128];
  FILE *fp;

  printf("Finding the Strongly Connected Components (SCC).\n");
  sprintf(file, "=%s.%s.dat", In.projname, "SCCSizeDistribution");
  printf("The SCC size distribution will be output on file \"%s\".\n",file);

  marked = (Bool *) malloc( NK * sizeof(Bool));
  InComp = (Bool *) malloc( NK * sizeof(Bool));
  if(!marked || !InComp) { perr("Alloc error in SCC.\n"); exit(1); }
  Loop(i, NK) marked[i] = InComp[i] = FALSE;

  Size = IntVectorAlloc(NK+1);
  IntVectorInit(Size, NK+1, 0);

  StackInit(&stack);

  Delta = IntVectorAlloc(NK);
  Root  = IntVectorAlloc(NK);
  IntVectorInit(Delta, NK, 0);
  IntVectorInit(Root , NK, 0);
  c = 0;

  Loop(i,NK)
    if(!marked[i]) NodeSCC(node, i);


  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%8s\n",
	  "Size", "P(Size)");
  Loop(i,NK+1)
    if(Size[i]) {
      fprintf(fp, "%6d\t%8d\n", i, Size[i]);
      norm += Size[i];
      avrgSize += (Real) i * Size[i];
      maxSize = i;
    }

  fclose(fp);
  printf("Number of distinct Strongly Connected Components: %d\n",norm);
  printf("Average Strongly Connected Component Size: %g\n", avrgSize / norm);
  printf("Size of Maximum Strongly Connected Component: %d\n\n", maxSize);

  if(In.multi==1)
    RunXmgrace(NULL, Size, INT, INT, NK,
	       "Distribution of SCC Sizes",
	       "SCC Size", "P(Size)");

  StackEmpty(&stack);
  IntVectorFree( Size);
  IntVectorFree(Delta);
  IntVectorFree( Root);
  free(marked);
  free(InComp);

}}

static void NodeSCC(NODE *node, Int v)
{
register Int i;
Int w; /* nearest neigh index */
Int Kv = GetNodeDegree(&node[v]);

  Root[v] = v;
  marked[v] = TRUE;
  StackPush( &stack, v);
  InComp[v] = FALSE;
  
  Delta[v] = ++c;

/*    printf("VISITING %d, DELTA %d\n",v, Delta[v]); */

  Loop(i, Kv) {
    w = node[v].links[i];
    if(!marked[w]) {
      NodeSCC( node, w);
    }
    if(!InComp[w]) {
/*        printf("Root[%d]=%d, Root[%d]=%d\n", v,Root[v], w,Root[w]); */
      Root[v] = (Delta[Root[v]]<Delta[Root[w]])? Root[v]: Root[w];
    }
  }
  
  i=0;
  if(Root[v]==v) {
    do {
      ++i; /* size of SCC found */
      w = StackPop(&stack);
      InComp[w] = TRUE;
/*        printf("***** REMOVED: %d Root: %d\n",w, Root[w]); */
    } while(w!=v);
    Size[i]++;
/*      puts(""); */
  }
	
}
