#include "main.h"
#include "extern.h"

#define ALLOCSTEP 100

void AddOneWayLink( NODE *nfrom, NODE *nto, Real weight)
{
register int i;
const Int to   =   nto->idx;
const Int from = nfrom->idx;
Int n = nfrom->n; /* get old *links dimension (out-degree) */
Int Kin = nto->Kin;

 if(!In.SelfLoops || !In.weighted) 
   if(to==from) return; /* do not accept self loops */ 

  /* if link exists already, do nothing */
  Loop(i,n)
    if(nfrom->links[i]==to)
      return;

  if( n==0) {
    nfrom->links = IntVectorAlloc( ALLOCSTEP);
  } else if( (n%ALLOCSTEP)==0 ) {
    nfrom->links = IntVectorRealloc( nfrom->links, n+ALLOCSTEP);
  }

  if(In.weighted) {
    if( n==0) {
      nfrom->weights = RealVectorAlloc( ALLOCSTEP);
    } else if( (n%ALLOCSTEP)==0 ) {
      nfrom->weights = RealVectorRealloc( nfrom->weights, n+ALLOCSTEP);
    }
    nfrom->weights[n] = weight;
  }

  if(In.nettype==1) { /* directed */
    if( Kin == 0) { /* first connection */
      nto->inlinks = IntVectorAlloc( ALLOCSTEP);
    } else if( (Kin%ALLOCSTEP)==0 ) {
      nto->inlinks = IntVectorRealloc( nto->inlinks, Kin+ALLOCSTEP);
    }
    nto->inlinks[Kin] = from;
  }

  nfrom->links[n] = to;

  ++(nfrom->n);
  ++(nto->Kin);
}
  
void AddTwoWayLink( NODE *node1, NODE *node2, Real weight)
{
  AddOneWayLink( node1, node2, weight); /* from n1 to n2 */
  AddOneWayLink( node2, node1, weight);
}

#undef ALLOCSTEP

void RemoveLink( NODE *nfrom, NODE *nto)
{
register int i;
Int idx, 
  Kfrom = GetNodeDegree(nfrom),
  Kinto = nto->Kin,
  *lnk = nfrom->links,
  *inlnk = nto->inlinks,
  from = nfrom->idx,
  to   = nto->idx;

  if( to==from || from<0 || to<0 ) {
    printf("Warning: illegal link (from node %d to node %d) to be removed\n",
	   from, to);
    return;
  }

  /* look for node "to" index */     
  for(i=0; i<Kfrom && lnk[i]!=to; i++) ;
  idx = i;
  if(idx==Kfrom) {
    printf("Warning: link (from node %d to node %d) to be removed seems not to exist\n",
	   from, to);
    return;
  }
  /* shift the vector to left erasing "to" index */
  for( i=idx; i<Kfrom-1; i++) {
    lnk[i]=lnk[i+1];
    if(In.weighted) nfrom->weights[i] = nfrom->weights[i+1];
  }

  if(In.nettype==1) { /*directed */
    /* look for node "to" index */     
    for(i=0; i<Kinto && inlnk[i]!=from; i++) ;
    idx = i;
    if(idx==Kinto) {
      printf("Warning: link (from node %d to node %d) to be removed seems not to exist as input\n",
	     from, to);
      return;
    }
    /* shift the vector to left erasing "to" index */
    for( i=idx; i<Kinto-1; i++) {
      inlnk[i]=inlnk[i+1];
    }
  }

  --(nfrom->n);
  --(nto->Kin);
}

void RemoveTwoWayLink( NODE *n1, NODE *n2)
{
  RemoveLink( n1, n2);
  RemoveLink( n2, n1);
}

void DisconnectNode( NODE *node, NODE *n)
{
  register int i;
  const Int K = GetNodeDegree(n);

  if(!In.nettype) {
    for(i=0; i<K; i++)
      RemoveTwoWayLink( n, &node[n->links[0]]); /* removes K time the first index */
  } else {
    for(i=0; i<K; i++)
      RemoveLink( n, &node[n->links[i]]);
  }
}

Bool LinkPresent(NODE *node1, NODE *node2) /* does node1 point to node2 ? */ 
{
  register int i;
  
  Loop(i, node1->n)
    if( node1->links[i] == node2->idx)
      return TRUE;

  return FALSE;
}
