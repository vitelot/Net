#include "main.h"
#include "extern.h"

LIST * ListAlloc( Int dim)
{
  LIST *out;

  out = (LIST *) malloc( (size_t) dim*sizeof(LIST));

  if(!out) {
    perr("Allocation error in ListAlloc. Exit.\n");
    exit(1);
  }

  return out;
}

void ListInit(  LIST *l, Int NK)
{
  register Int i;

   Loop(i,NK) {
     l[i].n = 0; /* initialize n */
     l[i].Dim = 0;
     l[i].list = NULL;
   }    
}

void ListEmpty(  LIST *l, Int NK)
{
  register Int i;

   Loop(i,NK) {
     IntListEmpty( &l[i]);
   }    
}

void ListFree( LIST *v, Int NK)
{ 
  ListEmpty( v, NK);
  free( (LIST *) v);
}

#define ALLOCSTEP 100

void IntListAppend( LIST * list, Int value)
{
  Int n, dim;

  n = list->n;
  dim = list->Dim;
  if( n == 0) {
    list->list = IntVectorAlloc( ALLOCSTEP);
    list->Dim = ALLOCSTEP;
  } else if( n >= dim-1 ) {
    list->list = IntVectorRealloc( list->list, dim+ALLOCSTEP);
    list->Dim += ALLOCSTEP;
  }

  list->list[n] = value;
  ++(list->n);
}

void IntListAppendList( LIST * L1, LIST * L2)
     /* append List L2 into List L1 */
{
  register int i;
  Int n1,n2;
  Int d1, newd1;

  n2 = L2->n;
  if(n2==0) return;

  n1 = L1->n;
  d1 = L1->Dim;
  
  if( n1+n2 > d1) {
    newd1 = ALLOCSTEP * ((n1+n2)/ALLOCSTEP) + ALLOCSTEP;
    L1->list = IntVectorRealloc( L1->list, newd1);
    L1->Dim = newd1;
  }

  for( i=0; i<n2; i++) 
    L1->list[n1+i] = L2->list[i];
  L1->n += n2;
}

#undef ALLOCSTEP

Int IntListSize( LIST * list)
{ return list->n; }

void IntListEmpty( LIST * list)
{
  list->n=0;
  list->Dim=0;
  IntVectorFree( list->list);
  list->list = NULL;
}
