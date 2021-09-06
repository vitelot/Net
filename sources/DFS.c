/* 
   Depth First Search (DFS) algorithm.
   Use of recursion: be carefull that the STACK will not overflow
   when lot of nodes are present. In this unfortunate case try
   to use the LINUX bash command "ulimit -s unlimited" to get unlimited
   STACK size.
*/

#include "main.h"
#include "extern.h"

static Int c1, c2;
static Int *Delta; /* DFS number of node x */
static Int *Gamma; /* completion number of node x */
static Bool *marked;

static void NodeDFS(NODE *node, Int idx);

void DFS(NODE *node, Int NK) {
  register Int i;

  marked = (Bool *) malloc( NK * sizeof(Bool));
  if(!marked) { perr("Alloc error in DFS.\n"); exit(1); }
  Loop(i, NK) marked[i] = FALSE;

  Delta = IntVectorAlloc(NK);
  Gamma = IntVectorAlloc(NK);
  IntVectorInit(Delta, NK, 0);
  IntVectorInit(Gamma, NK, 0);
  c1 = c2 = 0;

  Loop(i,NK)
    if(!marked[i]) NodeDFS(node, i);

  IntVectorFree(Delta);
  IntVectorFree(Gamma);
  free(marked);
}

static void NodeDFS(NODE *node, Int idx) {

register Int i;
Int nnidx; /* nearest neigh index */
Int K = GetNodeDegree(&node[idx]);

  marked[idx] = TRUE;
  Delta[idx] = ++c1;
  Loop(i,K)
    if( !marked[ (nnidx = node[idx].links[i]) ] ) NodeDFS(node, nnidx);
  Gamma[idx] = ++c2;
}
