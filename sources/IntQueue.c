#include "main.h"
#include "extern.h"

#define ALLOCSTEP 1000

void enQueue( QUEUE *queue, Int value)
{
  Int d;
  Int *newlist;

  d = queue->d; /* get old *list dimension */
  
  if( d==0) {
    queue->list = IntVectorAlloc( ALLOCSTEP);
    queue->p = 0;
  } else if( (d%ALLOCSTEP)==0 ) {
    queue->list = IntVectorRealloc(queue->list, d+ALLOCSTEP);
  }

  queue->list[d] = value;
  ++(queue->d);
}
#undef ALLOCSTEP

Int QueueSize( QUEUE *q)
{ return (q->d - q->p); }

Int deQueue( QUEUE *queue)
{
  Int size;
  Int retval;

  size = QueueSize( queue);

  if(size==0) {
    perr("Error: dequeueing from an empty queue. Exit.\n");
    exit(1);
  }
  retval = queue->list[queue->p];

  ++(queue->p);

  if(size==1) { /* last element has been fetched */
    queue->d = 0;
    queue->p = 0;
    IntVectorFree( queue->list);
    queue->list = NULL;
  }

  return retval;
}

void QueueInit( QUEUE *q)
{
  q->d = 0;
  q->p = 0;
  q->list = NULL;
}

void QueueEmpty( QUEUE *q)
{
  q->d = 0;
  q->p = 0;
  IntVectorFree( q->list);
  q->list = NULL;
}
