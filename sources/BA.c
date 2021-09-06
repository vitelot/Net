#include "main.h"
#include "extern.h"

#define STARTNODES  In.BAstartnodes
#define COMINGLINKS In.BAcominglinks
#define REALLOCSTEP 1000

extern Real UniformDistribution( Real min, Real max);
static void MemoryBarabasiAlbert( NODE *node, Int NK);

void BarabasiAlbert( NODE *node, Int NK)
{
register int i,j,l, idx;
struct {Int *pool; Int dim;} degree_pool;

 if(In.BAMemoryB && In.BAMemoryA) {
   MemoryBarabasiAlbert( node, NK);
   return;
 }

 if(In.nettype==1) {
   perr("BA net only undirected for the moment\n");
   exit(1);
 }

  printf("Constructing the net based on the Barabasi-Albert model:\n");

  if(COMINGLINKS>STARTNODES) {
    printf("ERROR: incoming link number (BA_M) cannot exceede\n"
	   "the starting clique order (BA_N0). Abort.\n");
    exit(1);
  }

  degree_pool.dim = 1 + STARTNODES * (STARTNODES-1) + 2 * COMINGLINKS * (NK-STARTNODES);
  degree_pool.pool = IntVectorAlloc( degree_pool.dim );

  /* place starting clique */
  idx = 0;
  Loop(i, STARTNODES) {
    Dots( '.', i, 1+(NK>>6));
    for(j=0; j<i; j++) {
      AddTwoWayLink( &node[i], &node[j], 0.0/* no weight */);

      if(degree_pool.dim < idx+2)
	degree_pool.pool = IntVectorRealloc( degree_pool.pool, degree_pool.dim += REALLOCSTEP);

      /* both i and j get degree increased */
      degree_pool.pool[idx++] = i;
      degree_pool.pool[idx++] = j;
    }
  }

  /* nodes begin to enter the net */
  for(i=STARTNODES; i<NK; i++) {
    ShowProgress(i,NK);

    for(l=0;l<COMINGLINKS;l++) {
/*    for(l=0;l<i/5;l++) { for BA with increasing numb of links vvvvv*/
      /* extract random integer 0 <= j < idx */
      j = (int) UniformDistribution(0.0, (Real) idx);

      j = degree_pool.pool[j]; /* that's the node we r going to link */

/*       if(i==j) {--l;continue;}  multi choice permitted vvvvv */
      if(i==j || LinkPresent(&node[j], &node[i])) {--l;continue;}
      AddTwoWayLink( &node[i], &node[j], 0.0/* no weight */);

      if(degree_pool.dim < idx+2) {
	degree_pool.pool = IntVectorRealloc( degree_pool.pool, degree_pool.dim += REALLOCSTEP);
/*  	printf("REALLOC %d\n", degree_pool.dim); */
      }

      /* both i and j got degree increased */
      degree_pool.pool[idx++] = i;
      degree_pool.pool[idx++] = j;
    }

#if 0
    do {
      j = (int) UniformDistribution(0.0, (Real) idx);
      l = (int) UniformDistribution(0.0, (Real) idx);
      j = degree_pool.pool[j]; /* that's the node we r going to link */
      l = degree_pool.pool[l]; /* that's the node we r going to link */
    } while(l==j || LinkPresent(&node[j], &node[l]));
    AddTwoWayLink( &node[j], &node[l], 0.0/* no weight */);
    if(degree_pool.dim < idx+2) {
      degree_pool.pool = IntVectorRealloc( degree_pool.pool, degree_pool.dim += REALLOCSTEP);
      /*  	printf("REALLOC %d\n", degree_pool.dim); */
    }
    degree_pool.pool[idx++] = j;
    degree_pool.pool[idx++] = l;
#endif

  }
  printf("\n");

  IntVectorFree( degree_pool.pool);
}

static Real MemoryKernel(int t);
static Int MemoryGetOldNode(Int *pool, Real *prob, Int dim);

static void MemoryBarabasiAlbert( NODE *node, Int NK) {

  register int i,j,l, idx;
  struct {
    Int *pool;  /* sequence of linked nodes in time */
    Real *prob; /* cumulative sum of memory kernel */
    Int dim;    /* max dimension of vectors */
  } degree_pool;

  if(In.nettype==1) {
    perr("BA net only undirected for the moment\n");
    exit(1);
  }

  printf("Constructing the net based on the Barabasi-Albert model with memory:\n");

  if(COMINGLINKS>STARTNODES) {
    printf("ERROR: incoming link number (BA_M) cannot exceede\n"
	   "the starting clique order (BA_N0). Abort.\n");
    exit(1);
  }

  degree_pool.dim = 1 + STARTNODES * (STARTNODES-1) + 2 * COMINGLINKS * (NK-STARTNODES);
  degree_pool.pool =  IntVectorAlloc( degree_pool.dim );
  degree_pool.prob = RealVectorAlloc( degree_pool.dim );

  /* place starting clique */
  idx = 0;
  Loop(i, STARTNODES) {
    Dots( '.', i, 1+(NK>>6));
    for(j=0; j<i; j++) {
      AddTwoWayLink( &node[i], &node[j], 0.0/* no weight */);

      if(degree_pool.dim < idx+2) {
	degree_pool.pool =  IntVectorRealloc( degree_pool.pool, degree_pool.dim += REALLOCSTEP);
	degree_pool.prob = RealVectorRealloc( degree_pool.prob, degree_pool.dim += REALLOCSTEP);
      }

      /* both i and j get degree increased */
      if(idx) degree_pool.prob[idx] = MemoryKernel(idx) + degree_pool.prob[idx-1];
      else    degree_pool.prob[idx] = MemoryKernel(idx);
      degree_pool.pool[idx++] = i;
      degree_pool.prob[idx] = MemoryKernel(idx) + degree_pool.prob[idx-1];
      degree_pool.pool[idx++] = j;
    }
  }

  /* nodes begin to enter the net */
  for(i=STARTNODES; i<NK; i++) {
    ShowProgress(i,NK);

    for(l=0;l<COMINGLINKS;l++) {
/*    for(l=0;l<i/5;l++) { for BA with increasing numb of links vvvvv*/

      j = MemoryGetOldNode( degree_pool.pool, degree_pool.prob, idx);/* that's the node we r going to link */
/*       if(i==j) {--l;continue;}  multi choice permitted vvvvv */
      if(i==j || LinkPresent(&node[j], &node[i])) {--l;continue;}
      AddTwoWayLink( &node[i], &node[j], 0.0/* no weight */);

      if(degree_pool.dim < idx+2) {
	degree_pool.pool =  IntVectorRealloc( degree_pool.pool, degree_pool.dim += REALLOCSTEP);
	degree_pool.prob = RealVectorRealloc( degree_pool.prob, degree_pool.dim += REALLOCSTEP);
      }

      /* both i and j got degree increased */
      degree_pool.prob[idx] = MemoryKernel(idx) + degree_pool.prob[idx-1];
      degree_pool.pool[idx++] = i;
      degree_pool.prob[idx] = MemoryKernel(idx) + degree_pool.prob[idx-1];
      degree_pool.pool[idx++] = j;
    }      
  }
  printf("\n");

   IntVectorFree( degree_pool.pool);
  RealVectorFree( degree_pool.prob);
}

static Int MemoryGetOldNode(Int *pool, Real *prob, Int dim) {
  register int i;
  Real random = UniformDistribution( 0.0, prob[dim-1]);

  for(i=0; prob[i]<random; i++) ;
  return pool[dim-1-i];
}

static Real MemoryKernel(int t) {
  if(In.BAMemoryB>=0)
    return pow(In.BAMemoryA+t, -In.BAMemoryB);
  else
    return exp(-t/In.BAMemoryA);
}

#undef STARTNODES
#undef COMINGLINKS
#undef REALLOCSTEP
