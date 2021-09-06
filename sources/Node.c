#include "main.h"
#include "extern.h"

NODE *NodeAlloc( int dim)
{
  NODE *out;

  out = (NODE *) malloc( (size_t) dim*sizeof(NODE));

  if(!out) {
    perr("Allocation error in NodeAlloc. Exit.\n");
    exit(1);
  }

  return out;
}

NODE *NodeRealloc( NODE *node, int dim)
{
  NODE *out;

  out = (NODE *) realloc( (void *)node, (size_t) dim*sizeof(NODE));

  if(!out) {
    perr("Allocation error in NodeRealloc. Exit.\n");
    exit(1);
  }

  return out;
}

void NodeFree( NODE *v, Int NK)
{ 
  register int i;
  Loop(i,NK) {
     IntVectorFree( v[i].links);
     IntVectorFree( v[i].inlinks);
    RealVectorFree( v[i].weights);
  }
    
  free( (NODE *) v);
}

void SetNodeDegree( NODE *Node, Int x)
{
  Node->n = x;
}

Int GetNodeDegree( NODE *Node)
{
  return Node->n;
}

void SetNodeInDegree( NODE *Node, Int x)
{
  Node->Kin = x;
}

Int GetNodeInDegree( NODE *Node)
{
  return Node->Kin;
}

void SetNodeOutDegree( NODE *Node, Int x)
{
  SetNodeDegree(Node,x);
}

Int GetNodeOutDegree( NODE *Node)
{
  return GetNodeDegree(Node);
}

void SetNodeFitness( NODE *Node, Real x)
{
  Node->fitness = x;
}

Real ReadNodeFitness( NODE *Node)
{
  return Node->fitness;
}

void SetNodeIndex( NODE *Node, Int x)
{
  Node->idx = x;
}

Int GetNodeIndex( NODE *Node)
{
  return Node->idx;
}

Int PositionFromIndex( NODE *node, Int NK, Int index)
{
   Int i;
   Loop(i,NK) {
      if(node[i].idx == index)
         return i;
   }
   return (-1);
}

void NodeInit(  NODE *node, Int NK)
{
  register Int i;

   Loop(i,NK) {
     node[i].idx = i;
     node[i].fitness = 0.0;
     node[i].Kin = 0; /* initialize in-degree */
     node[i].n = 0; /* initialize n = out-degree */
     node[i].links   = NULL;
     node[i].inlinks = NULL;
     node[i].weights = NULL;
   }    
}

Int NodeIntersect( NODE *k1, NODE *k2)
{ /*  Returns the number of nodes linked both in k1 and k2 */
  return IntVectorIntersect( k1->links, k1->n,  k2->links, k2->n);
}

Bool HaveCommonNeighbor( NODE *n1, NODE *n2, Int NK)
{
Int k1      = GetNodeDegree( n1);
Int k2      = GetNodeDegree( n2);
Int *nlist1 = n1->links;
Int *nlist2 = n2->links;
Int *pool   = IntVectorAlloc( NK);
Bool status = FALSE;
register int i;

 Loop( i, k1) pool[ nlist1[i] ] = 0;
 Loop( i, k2) ++pool[ nlist2[i] ];
 Loop( i, k1) {
   if( pool[ nlist1[i] ] ) {
     status = TRUE;
     break;
   }
 }

free((Int *) pool);
return status;

}

Bool AreNeighbors( NODE *n1, NODE *n2)
     /* returns true if n1-->n2 (n1 direct-linked to n2) */
{
Int k1      = GetNodeDegree( n1);
Int *nlist1 = n1->links;
register int i;

 Loop( i, k1) {
   if( nlist1[i] == GetNodeIndex(n2) ) {
     return TRUE;
     break;
   }
 }

return FALSE;

}
