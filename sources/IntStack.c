#include "main.h"
#include "extern.h"

#define ALLOCSTEP 1000

void StackPush( STACK *stack, Int value)
{
  Int d;
  Int *newlist;

  d = stack->d; /* get old *list dimension */
  
  if( d==0) {
    stack->list = IntVectorAlloc( ALLOCSTEP);
  } else if( (d%ALLOCSTEP)==0 ) {
    stack->list = IntVectorRealloc( stack->list, d+ALLOCSTEP);
  }

  stack->list[d] = value;
  ++(stack->d);
}

#undef ALLOCSTEP

Int StackPop( STACK *stack)
{ /*  Pop does not deallocate with ALLOCSTEP yet */
  Int retval;

  if(stack->d == 0) {
    perr("Pop error: stack already empty. Exit.\n");
    exit(1);
  }
  retval = stack->list[--(stack->d)];

  if(stack->d == 0) {
    IntVectorFree( stack->list);
    stack->list = NULL;
  }

  return retval;
}

Int StackSize( STACK *stack)
{ return stack->d; }

void StackInit( STACK *stack)
{
  stack->d = 0;
  stack->list = NULL;
}

void StackEmpty( STACK *stack)
{
  stack->d = 0;
  IntVectorFree( stack->list);
  stack->list = NULL;
}
    
