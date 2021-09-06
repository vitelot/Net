#include "main.h"
#include "extern.h"

struct MinList { Real value; Int from; Int to; };

static Real Function( Real x, Real y) {return (x*y);}
static int sortfn( const struct MinList * , const struct MinList *);

void MinimumGrowth( NODE *node, Int NK)
{
register int i,n;
struct MinList *minlist, *start_ptr, *end_ptr;

 start_ptr = end_ptr = minlist = 
   (struct MinList *) malloc( (size_t) (NK+NK)*sizeof(struct MinList));
 if(!minlist) AllocError( "MinimumGrowth.c");

 if(In.nettype==1) {
   perr("Minimum Growth net only undirected for the moment. Sorry.\n");
   exit(1);
 }

  printf("Constructing the net based on the Minimum Growth model:\n");

  NodeInitFitnesses( node, NK, UNIF, 0.0, 1.0);

  /* second node links to the first mandatorily */
  start_ptr->value = Function( ReadNodeFitness(&node[0]), ReadNodeFitness(&node[1]));
  start_ptr->from  = 0;
  start_ptr->to    = 1;

  ++start_ptr;
  ++end_ptr;

  /* nodes enter one by one */
  for( i=2; i<NK; i++) {
    Dots( '.', i, 1+(NK>>6));

    /* at maximum NK links will be turned on.
       second part of minlist is for incoming links only */
    if(end_ptr - minlist > NK) end_ptr = minlist+NK;
    /* append i values into the array */
    for( n=0; n<i; n++) {
      end_ptr->value = Function( ReadNodeFitness(&node[i]), ReadNodeFitness(&node[n]));
      end_ptr->from  = i;
      end_ptr->to    = n;
      ++end_ptr;
    }
    qsort( (void *)start_ptr,
	   (size_t)(end_ptr-start_ptr), sizeof(struct MinList),
	   (int (*)(const void *, const void *))sortfn);
    /* save the min value from successive minimizations */
    ++start_ptr;
  }

  /* finally add the found NK-1 links to the net */
  Loop(i, NK-1) {
    AddTwoWayLink( &node[minlist[i].from], &node[minlist[i].to], minlist[i].value);
  }

  free( (void *) minlist);

  printf("\n\n");
}

static int sortfn( const struct MinList *a , const struct MinList *b)
{ /* sorts in ascending order */
  if(a->value == b->value) return 0;
  return ((a->value < b->value)? -1: 1);
}
