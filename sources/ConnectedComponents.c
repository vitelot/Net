#include "main.h"
#include "extern.h"

static void ClusterFind( NODE *node, Int * CS, Int *d, Int nrcl, Int NK);
static void ClusterSave( NODE *node, Int NK, Int *d, Int nc, Int size);
static void PrintCluster( Int *CS, Int NK);

void ConnectedComponents( NODE *node, Int NK)
/* BFS extracted from Brandes betweenness algorithm */
{
register Int s,v,w, i;
Int k, concompnr;
Int *d, *ClusterSize;
QUEUE Q;

/*    if(!In.conncomp) return; */
  if( !In.splitcluster) return;

/*    if(In.nettype==1) { */
/*      printf("Split Cluster has not yet been implemented for directed nets. Sorry.\n"); */
/*      exit(1); */
/*    } */

  printf("\nFinding the Connected Components of the net.\n");

  QueueInit( &Q);

  d     =  IntVectorAlloc( NK);/* visited node */
  IntVectorInit(     d, NK, -1);

  concompnr = 1; /* sequential number of connected component found */

  Loop( s, NK) { /* BFS */

    if(d[s]>0) continue; /* ignore s if already visited */

    d[s] = concompnr;

    QueueEmpty( &Q);
    enQueue( &Q, s);

    while( QueueSize( &Q)) {
      v = deQueue( &Q);
      k = GetNodeDegree( &node[v]);
      for( i=0; i<k; i++) { /* browse v's nearest neighbors */
	w = node[v].links[i];
	if( d[w] < 0) { /*  w found for the first time? */
	  enQueue( &Q, w);
	  d[w] = concompnr;
	}
      }
      if(In.nettype==1) {
	k = GetNodeInDegree( &node[v]);
	for( i=0; i<k; i++) { /* browse v's uphill nearest neighbors */
	  w = node[v].inlinks[i];
	  if( d[w] < 0) { /*  w found for the first time? */
	    enQueue( &Q, w);
	    d[w] = concompnr;
	  }
	}
      }
    }
    concompnr++;
  }

  ClusterSize = IntVectorAlloc( NK);/* number of nodes of the belonging cluster */
  IntVectorInit( ClusterSize, NK, 0);

  ClusterFind( node, ClusterSize, d, concompnr, NK);
  printf("\n");

  PrintCluster( ClusterSize, NK);

  IntVectorFree( ClusterSize);
  IntVectorFree(     d);
}

#define VISITED 1

Bool IsConnected( NODE *node, Int NK)
/* Determines whether the undirected network is connected */ 
/* BFS extracted from Brandes betweenness algorithm */
{
   register Int s,v,w, i;
   Int k, nrofvisited=0;
   Int *d;
   QUEUE Q;
      
   if(In.nettype==1) {
      printf("IsConnected has not yet been implemented for directed nets. Sorry.\n"); 
      exit(1);
   }
      
   QueueInit( &Q);
   
   d = IntVectorAlloc( NK); /* visited node */
   IntVectorInit( d, NK, 0);
         
   s=0; /* start BFS from node 0 */
   d[s] = VISITED; nrofvisited++;

   QueueEmpty( &Q);
   enQueue( &Q, s);

   while( QueueSize( &Q)) {
      v = deQueue( &Q);
      k = GetNodeDegree( &node[v]);
      for( i=0; i<k; i++) { /* browse v's nearest neighbors */
         w = node[v].links[i];
         if( d[w] != VISITED) { /*  w found for the first time? */
            enQueue( &Q, w);
            d[w] = VISITED; nrofvisited++;
         }
      }
   }

   IntVectorFree( d);
   
   if(nrofvisited==NK) return TRUE;
   
   return FALSE;
}
               
#undef VISITED

static void ClusterFind( NODE *node, Int * CS, Int *d, Int nrcl, Int NK)
{
  register int i, c;
  Int size;

  for(c=1; c<nrcl; c++) { /* for any cluster found */
    size = 0;
    Loop(i,NK) if(d[i]==c) size++; /* find its size */
    Loop(i,NK) if(d[i]==c) CS[i]=size; /* assign it as CS value */

    if( size>2)
      ClusterSave( node, NK, d, c, size);
  }

}

static void ClusterSave( NODE *node, Int NK, Int *d, Int nc, Int size)
{
  if(!In.printdat) return;
{
    
  register Int i,j;
  Int *nodelist;
  FILE * out;
  Int newid, newjd, *L, K;
  Real *W, xi,xj;
  char filename[128];
  static Int clusteridx=0;

  nodelist=IntVectorAlloc( NK);
  IntVectorInit( nodelist, NK, -1);

  sprintf( filename, "%s_C%04d_S%d.net", In.projname, ++clusteridx, size);
  printf("Saving file %s\n", filename);

  out = fopen( filename, "w");
  if( !out)  FileOpenError(filename);

  fprintf(out, "# Cluster number %d\n", clusteridx);
  fprintf(out, "# %d nodes\n", size);
  fprintf(out, "# old index mapping at end file\n");
  fprintf(out, "#\n");

  j=0;
  Loop(i,NK)
    if( d[i]==nc) /* node i belongs to cluster nc */
      nodelist[i] = j++; /* create a new label table */

  Loop(i,NK) {
    newid = nodelist[i];
    if( newid>=0) {
      xi = ReadNodeFitness( &node[i]);
      K = GetNodeDegree( &node[i]);
      L = node[i].links;
      W = node[i].weights;
      Loop(j,K) {
	xj = ReadNodeFitness( &node[j]);
	newjd = nodelist[ L[j] ];
	if(In.weighted) {  /* if weighted net */
	  if(In.nettype) { /* directed */
	    if(In.readin)
	      fprintf(out, "%4d\t%4d\t%12.6g\n", newid,newjd, W[j]);
	    else
	      fprintf(out, "%4d\t%4d\t%12.6g\t\t#(%10.4f,%10.4f)\n", newid,newjd, W[j], xi,xj);
	  } else {         /* undirected */
	    if(newjd>newid) {
	      if(In.readin)
		fprintf(out, "%4d\t%4d\t%12.6g\n", newid,newjd, W[j]);
	      else
		fprintf(out, "%4d\t%4d\t%12.6g\t\t#(%10.4f,%10.4f)\n", newid,newjd, W[j], xi,xj);
	    }
	  }
	} else {
	  if(In.nettype) {
	    if(In.readin)
	      fprintf(out, "%4d\t%4d\n", newid,newjd);
	    else
	      fprintf(out, "%4d\t%4d\t\t#(%10.4f,%10.4f)\n", newid,newjd, xi,xj);
	  } else {
	    if(newjd>newid) {
	      if(In.readin)
		fprintf(out, "%4d\t%4d\n", newid,newjd);
	      else
		fprintf(out, "%4d\t%4d\t\t#(%10.4f,%10.4f)\n", newid,newjd, xi,xj);
	    }
	  }
	}
      }
    }
  }

  fprintf(out, "#\n#\n#\n");
  fprintf(out, "# old index mapping #\n");
  fprintf(out, "# OLDIDX NEWIDX\n");
  Loop(i,NK)
    if(nodelist[i]!=-1)
      fprintf(out, "# %6d %6d\n",i, nodelist[i]);

  fclose(out);
/*      printf("Cluster %d containing %4d nodes saved on file \"%s\"\n", */
/*  	   nc, size, filename); */

  IntVectorFree( nodelist);

}
}

static void PrintCluster( Int *CS, Int NK)
{
  register Int i;
  char file[128];
  Int *Pcs; /* Distrib of CS: P(CS) */
  Real average=0;
  Int TotalCluster=0, MaxClustDim;
  FILE *fp;

  if(!In.printcluster) return;

  Pcs = IntVectorAlloc( NK+1);
  IntVectorInit( Pcs, NK+1, 0);

  Loop(i,NK)
    ++Pcs[CS[i]];

  for(i=1;i<=NK;i++) {
    if(Pcs[i] != 0) {
      TotalCluster += (Pcs[i] /= i);
      MaxClustDim = i;
    }
  }

  sprintf(file, "=%s.%s.dat", In.projname, "ClusterSize");
  printf("Saving the Cluster Size. Output on file \"%s\".\n",file);
  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%6s\t%6s\n", "i,CS", "CS(i)", "P(CS)");
  Loop(i,NK) {
    average += CS[i];
    fprintf(fp, "%6d\t%6d\t%6d\n", i, CS[i], Pcs[i]);
  }
  fclose(fp);

  printf("Found %d Clusters", TotalCluster);
  if(Pcs[1]>0)
    printf(", %d of which are isolated nodes", Pcs[1]);
  printf(".\n");

  printf("Average Cluster Size: %g\t", average / NK);
  printf("Size of Maximum Cluster: %d\n\n", MaxClustDim);

  IntVectorFree( Pcs);
}
