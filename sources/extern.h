#ifndef __EXTERN_H
#  define __EXTERN_H

#include "main.h"

/************************ Global variables ************************/
extern FILE *fperr; /* file pointer for error messages */
extern long RArg; /* random nr gen argument. never modify it! */
extern struct Input In; /* Input parameters */
/******************************************************************/

/*  ran1.c */
extern float URand(long *idum);

/*  RandomInit.c */
extern void RandomInit( long *Seed);

/*  GetRandom.c */
extern Real GetRandom( enum RndDistrib RDType, Real , Real);

/*  IntVector.c */
extern Int *IntVectorAlloc( int dim);
extern Int *IntVectorRealloc( Int *v, int newdim);
extern void IntVectorFree( Int *v);
extern void IntVectorInit( Int *v, Int dim, Int value);
extern Int IntVectorIntersect( Int *a, int dima, Int *b, int dimb);
extern void IntVectorCopy( Int *a, Int *b, int dim);

/*  RealVector.c */
extern Real *RealVectorAlloc( int dim);
extern Real *RealVectorRealloc( Real *v, int newdim);
extern void RealVectorFree( Real *v);
extern void RealVectorInit( Real *v, Int dim, Real value);
extern void RealVectorCopy( Real *a, Real *b, int dim);

/*  Node.c */
extern NODE *NodeAlloc( int dim);
extern NODE *NodeRealloc( NODE *, int dim);
extern void NodeFree( NODE *v, Int NK);
extern void NodeInit(  NODE *node, Int NK);
extern void SetNodeDegree( NODE *Node, Int x);
extern Int GetNodeDegree( NODE *Node);
extern void SetNodeInDegree( NODE *Node, Int x);
extern Int GetNodeInDegree( NODE *Node);
extern void SetNodeOutDegree( NODE *Node, Int x);
extern Int GetNodeOutDegree( NODE *Node);
extern void SetNodeFitness( NODE *Node, Real x);
extern Real ReadNodeFitness( NODE *Node);
extern void SetNodeIndex( NODE *Node, Int x);
extern Int GetNodeIndex( NODE *Node);
extern Int PositionFromIndex( NODE *node, Int NK, Int index);
extern Int NodeIntersect( NODE *k1, NODE *k2);
extern Bool HaveCommonNeighbor( NODE *n1, NODE *n2, Int NK);
extern Bool AreNeighbors( NODE *n1, NODE *n2);

/*  NodeLinks.c */
extern void AddOneWayLink( NODE *nodefrom, NODE *nodeto, Real weight);
extern void AddTwoWayLink( NODE *node1, NODE *node2, Real weight);
extern void RemoveLink( NODE *from, NODE *to);
extern void RemoveTwoWayLink( NODE *n1, NODE *n2);
extern Bool LinkPresent(NODE *n1, NODE *n2);
extern void DisconnectNode( NODE *node, NODE *n);

/* ConnectedComponents.c */
extern Bool IsConnected( NODE *node, Int NK);

/*  InitFitnesses.c */
extern void NodeInitFitnesses( NODE *node, Int NK, enum RndDistrib RDType, Real, Real);

/*  IntStack.c */
extern void StackPush( STACK *stack, Int value);
extern Int StackPop( STACK *stack);
extern Int StackSize( STACK *stack);
extern void StackEmpty( STACK *stack);
extern void StackInit( STACK *stack);

/*  IntQueue.c */
extern void enQueue( QUEUE *queue, Int value);
extern Int QueueSize( QUEUE *q);
extern Int deQueue( QUEUE *queue);
extern void QueueEmpty( QUEUE *q);
extern void QueueInit( QUEUE *q);

/*  IntList.c */
extern LIST * ListAlloc( Int dim);
extern void ListInit(  LIST *l, Int NK);
extern void ListEmpty(  LIST *l, Int NK);
extern void ListFree( LIST *v, Int NK);
extern void IntListAppend( LIST * list, Int value);
extern void IntListAppendList( LIST * L1, LIST * L2);
extern Int IntListSize( LIST * list);
extern void IntListEmpty( LIST * list);

/* Rewiring.c */
extern void Rewiring(NODE *node, Int NK);

/*  perr.c */
extern void perr(const char *fmt, ...);
extern void OpenError(char *errfilename);
extern void CloseError(void);
extern void AllocError( char *s);
extern void FileOpenError( char *s);

/*  DisplayNet.c */
extern void DisplayNet( NODE *node, Int NK);

/*  PrintDat.c */
extern void PrintDat( NODE *node, Int NK);

/*  AssignLinks.c */
extern void AssignLinks( NODE *node, Int NK);

/*  Analyze.c */
extern void Analyze( NODE *node, Int NK);

/*  Input.c */
extern void InputParameters( char *ini_file);

/*  ReadIn.c */
extern NODE * ReadIn( NODE *node, Int *NK);

/*  Dots.c */
extern void Dots(const char c, int i, int step);
/*  ShowProgress.c */
extern void ShowProgress(float fraction, float total);

/* RunXmgrace.c */
extern void RunXmgrace(void *VectorX, void *VectorY, 
		       Field typeX, Field typeY,
		       Int NK, 
		       const char *title, 
		       const char *labelX, const char *labelY);

/* Timer.c */
extern double Timer(void);

/* BA.c */
extern void BarabasiAlbert( NODE *node, Int NK);

/* MinimumGrowth.c */
extern void MinimumGrowth( NODE *node, Int NK);

#endif
