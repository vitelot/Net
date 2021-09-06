#ifndef __MAIN_H
# define __MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Version.h"

#define Loop(i,N) for( (i)=0; (i)<(N); ++(i))
#define URand ran1 /* random nr generator, uniform distribution */

typedef double Real; /* Change float to what you want, if needed */
typedef int   Int ; /* Change   int to what you want, if needed */

struct sNode {
  Int idx;
  Real fitness;
  Int Kin; /* in-degree */
  Int n; /* total nr of links (dim of *links = out-degree) */
  Int *links; /* idx of pointed nodes */
  Int *inlinks; /* idx of nodes pointing to this node */
  Real *weights;
};

typedef struct sNode NODE;

struct IntStack {
  Int d; /* stack dimension */
  Int *list; /* stack element list */
};

typedef struct IntStack STACK;

struct IntQueue {
  Int p; /* queue pointer */
  Int d; /* queue dimension */
  Int *list; /* queue element list */
};

typedef struct IntQueue QUEUE;

struct IntList {
  Int Dim; /* Allocated dimension of the list */
  Int n; /* total nr of elements in the list */
  Int *list; /* element list */
};

typedef struct IntList LIST;

enum RndDistrib { UNIF, EXP, GAUSS, POWER, USER }; /* type of fitness random distribution */

enum Generator { FITNESS, BA, MINIMUM_GROWTH, GEO_NET }; /* type of algorithm to generate nets */

enum GeoNetRadiusDistr { RADIUS, RADII, RUNIF, RCEXP, RBPL };

typedef enum {FALSE, TRUE} Bool;
typedef enum {INT, REAL} Field;

struct Input {
  Int nk;
  enum RndDistrib distrib;
  float Aparam;
  float Bparam;
  int linktype;
  float cutoff;
  float E;
  float m;
  Int BAcominglinks;
  Int BAstartnodes;
  float BAMemoryA;
  float BAMemoryB;
  enum GeoNetRadiusDistr GNradiusdistr;
  float GNrmin;
  float GNrmax;
  float GNprmin;
  /*****************************************/
  char projname[128];
  int nettype;    /* 1 = directed */
  enum Generator netgenerator;
  int weighted;
  int TASRW;
  int TAS;
  int SelfLoops;
  int readin;
  int multi;
  int tree;
  int acyclic;
  int printnet;
  int printdat;
  int rungrace;
  int TASreshuf;
  int degdistr;
  int knn;
  int clcoeff;
  int cl2coeff;
  int scc;
  int communities;
  int reduction;
  int rewiring;
  int lanczos;
  int amatrix;
  int edgebetw;
  int sitebetw;
  int rwsitebetw;
  int printcluster;
  int splitcluster;
  int printpairdist;
};

#endif
