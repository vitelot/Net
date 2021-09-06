#include "main.h"
#include "extern.h"

extern Real UniformDistribution( Real min, Real max);

static int STEPS = 1000;
static int CHECK_CONNECTION = 0;
static int CHECK_KNN = 0;
static double BETA = 99999;

static int rejected_connection=0;
static int rejected_common_neighbor=0;
static int rejected_knn=0;

static void Create_Rewiring_INI( char ini[128])
{
   FILE *fp;
   
   fp = fopen( ini, "r");
   if( !fp) {
      printf("Error opening file %s\n", ini);
      printf("Creating a default one. Please edit it. Exit.\n\n");
      
      fp = fopen( ini, "w");
      if( !fp)  FileOpenError(ini);
      fprintf(fp, "NAME STEPS CONNECTED? KNN? BETA\n");
      fprintf(fp, "%-4s %8d %6d %6d  %6g\n",
              In.projname, In.rewiring, 0, 0, 1.0);
              fclose(fp);
              exit(1);
   }
     fclose(fp);
}


static void PairRewiring(NODE *x, NODE *lx, NODE *y, NODE *ly)
{
   /* lx is a node linked to x, ly is linked to y;
      this function swaps lx with ly thus preserving node degrees */

   Int K, *lnk, i;

   /* debug */
   /* printf("DBG x:%d lx:%d y:%d ly:%d\n", x->idx,lx->idx, y->idx,ly->idx); */
   /*********/
   
   K = GetNodeDegree(x);
   for(i=0; i<K && x->links[i]!= lx->idx; i++) ;
   x->links[i] = ly->idx;

   K = GetNodeDegree(y);
   for(i=0; i<K && y->links[i]!= ly->idx; i++) ;
   y->links[i] = lx->idx;

   /* now we change the x in the nn list of lx, into y */
   K = GetNodeDegree(lx);
   if(!In.nettype) {lnk = lx->links;} /* if undirected */
   else {lnk = lx->inlinks;}
   for(i=0; i<K && lnk[i]!= x->idx; i++) ;
   lnk[i] = y->idx;

   /* same for y and ly */
   K = GetNodeDegree(ly);
   if(!In.nettype) {lnk = ly->links;} /* if undirected */
   else {lnk = ly->inlinks;}
   for(i=0; i<K && lnk[i]!= y->idx; i++) ;
   lnk[i] = x->idx;
}

static void RewiringStep(NODE *node, Int NK)
{
   Int x, y, lx, ly, rx,ry, K;

   /* Pick two random nodes */
   x = (Int) UniformDistribution( 0.0, NK);
   do {
      y = (Int) UniformDistribution( 0.0, NK);
   } while(y==x);

   /* Get one nearest neighbor of x */
   K = GetNodeDegree(&node[x]);
   rx = (Int) UniformDistribution( 0.0, K);
   lx = node[x].links[rx];

   /* Get one nearest neighbor of y */
   K = GetNodeDegree(&node[y]);
   ry = (Int) UniformDistribution( 0.0, K);
   ly = node[y].links[ry];

   /* lx and ly are the idx of the nodes not their position in the node[] vector */
   ly = PositionFromIndex(node, NK, ly); /* now ly is the position in the node[] */
   lx = PositionFromIndex(node, NK, lx); /* now lx is the position in the node[] */

   if(x==ly || y==lx || AreNeighbors(&node[x], &node[ly]) || AreNeighbors(&node[y], &node[lx])) {
      rejected_common_neighbor++;
      return;
   }
   
   if(CHECK_KNN) {
      if( BETA*(GetNodeDegree(&node[x]) - GetNodeDegree(&node[y])) *
          (GetNodeDegree(&node[ly]) - GetNodeDegree(&node[lx])) 
           <= 0) {
         rejected_knn++;
         return;
      }
   }

   PairRewiring(&node[x], &node[lx], &node[y], &node[ly]);

   if(CHECK_CONNECTION) {
      if(!IsConnected(node, NK)) { 
         /* if the resulting network is not connected any more, undo the rewiring */
         PairRewiring(&node[x], &node[ly], &node[y], &node[lx]);
         ++rejected_connection;
      }
   }
}

void Rewiring(NODE *node, Int NK) 
{
   if(!In.rewiring) return;
   if(In.weighted) {
      printf("WARNING: Rewiring with weighted nets is not implemented yet. Sorry.\n\n");
      return;
   }
   if(CHECK_CONNECTION && !IsConnected(node, NK)) {
      printf("WARNING: Cannot perform rewiring keeping the graph connected since it is disconnected already!\n\n");
      return;
   }
{
   Int i;
   char rewiring_ini[128];
   char line[255];
   FILE *fin;

   sprintf(rewiring_ini, "=%s.%s", In.projname, "Rewiring.INI");
   Create_Rewiring_INI(rewiring_ini);

   if (!(fin = fopen(rewiring_ini, "r"))) { 
      printf("cannot open file %s for reading\n", rewiring_ini);
      exit(-1);
   }
   
   /*   fprintf(fp, "NAME STEPS CONNECTED? KNN? BETA\n");   */
   fgets( line, 255, fin); /* skip first line of comment */
     fscanf (fin,"%*s %d %d %d %lg ",
             &STEPS , &CHECK_CONNECTION, &CHECK_KNN, &BETA);
     
     fclose(fin);

     
   printf("Going to perform %d rewirings preserving node degrees.\n", STEPS);
   if(CHECK_CONNECTION) printf("Keeping the graph connected.\n");
   if(CHECK_KNN) printf("Maximizing the assortativity.\n");
   fflush(stdout);
   Loop(i, STEPS) {
      ShowProgress( i, STEPS);
      RewiringStep(node, NK);
   }
   printf(" Done.\n");
   printf("Rejected rewirings because of common neighbors: %d\n", rejected_common_neighbor);
   if(CHECK_KNN)
      printf("Rejected rewirings because of assortativity: %d\n",
             rejected_knn);
   if(CHECK_CONNECTION)
      printf("Rejected rewirings because of graph disconnections: %d\n",
             rejected_connection);

   printf("Total nr of accepted rewirings: %d\n",
          STEPS-rejected_common_neighbor-rejected_connection-rejected_knn);

   printf("\n");
}
}