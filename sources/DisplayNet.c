#include "main.h"
#include "extern.h"

#include <string.h>
#include <unistd.h>

#define DOTNOLBL 200
#define DOTSIZEX 9
#define DOTSIZEY 9


static void PrintNet( NODE *node, Int NK);
static void PrintDiNet( NODE *node, Int NK);
static void PrintGML( NODE *node, Int NK);
extern void DrawGraph( NODE *node, Int NK);

void DisplayNet( NODE *node, Int NK)
{

  /*  DrawGraph( node, NK);  TEST */

  if(In.nettype) {
    switch (In.printnet) {
    case 1: PrintDiNet(node,NK); break;
    case 2: break;
    }
  } else {
    switch (In.printnet) {
    case 1: PrintNet(node,NK); break;
    case 2: PrintGML(node,NK); break;
    }
  }
}

static void PrintNet( NODE *node, Int NK)
{
  register Int i,j, nj;
  Int *lnk, n;
  char filename[128], basename[128];
  char epsfile[128];
  char command[128];
  FILE *out;

  strcpy( basename, In.projname);
  if(In.reduction>0)
    sprintf(basename, "%s_R%d", In.projname, In.reduction);

  sprintf(filename, "%s.dot", basename);
  sprintf(epsfile,  "%s.eps", basename);

  out = fopen( filename, "w");

  fprintf(out, "// Total number of nodes: %d\n", NK);
  fprintf(out, "graph %s {\n", basename);
  fprintf(out, " size=\"%d,%d\"\n", DOTSIZEX, DOTSIZEY);
  fprintf(out, " ratio=fill\n");
  fprintf(out, " start=rand\n");
  if(NK>DOTNOLBL)
    fprintf(out, "  node [shape=point,label=\"\",color=\"red\"]\n");
  else
    fprintf(out, "  node [shape=circle,color=\"red\"]\n");

  Loop(i,NK) {
    n = GetNodeDegree( &node[i]);
    fprintf(out, "\t\t//node %4d: degree %4d\n ", i, n);
    if(n) {
      lnk = node[i].links;
      Loop(nj,n) {
	j = lnk[nj];
	if( j>i)
	  fprintf(out, "  %4d -- %4d\n ", i,j);
      }
    }
  }
  fprintf(out, "}\n");

  fclose(out);
  printf("File \"%s\" saved.\n", filename);

  sprintf( command, "neato -Tps %s -o %s && gv %s &\n", filename, epsfile, epsfile);

  printf("Invoking the external program \"neato\"\n");
  system( command);
  if(In.multi != 1) sleep(1);
}

static void PrintDiNet( NODE *node, Int NK)
{
register Int i,j, nj;
Int *lnk, n;
char filename[128];
char epsfile[128];
char command[128];
FILE *out;

  strcpy( filename, In.projname);
  strcat( filename, "-d.dot");
  strcpy( epsfile, In.projname);
  strcat( epsfile, "-d.eps");

  out = fopen( filename, "w");

  fprintf(out, "// Total number of nodes: %d\n", NK);
  fprintf(out, "digraph %s {\n", In.projname);
  fprintf(out, " size=\"7,9\"\n");
  fprintf(out, " ratio=fill\n");
  fprintf(out, " start=rand\n");
  if(NK>100)
    fprintf(out, "  node [shape=point,label=\"\",color=\"red\"]\n");
  else
    fprintf(out, "  node [shape=circle,color=\"red\"]\n");

  fprintf(out, "\t\t//Node: Kout\n ");
  Loop(i,NK) {
/*      xi = ReadNodeFitness( &node[i]); */
    n = GetNodeDegree( &node[i]);
    fprintf(out, "\t\t//%4d: %4d\n ", i, n);
/*      fprintf(out, "\t\t//%4d: %4d (%8f)\n ", i, n, xi); */
    if(n) {
      lnk = node[i].links;
      Loop(nj,n) {
	j = lnk[nj];
/*  	xj = ReadNodeFitness( &node[j]); */
	fprintf(out, "  %4d -> %4d\n ", i,j);
/*  	  fprintf(out, "  %4d -> %4d\t\t//(%f -- %f)\n ", i,j, xi,xj); */
      }
    }
  }
  fprintf(out, "}\n");

  fclose(out);
  printf("File \"%s\" saved.\n", filename);

  sprintf( command, "/usr/bin/neato -Tps %s -o %s && /usr/bin/X11/gv %s &\n", filename, epsfile, epsfile);

  printf("Invoking the external program \"neato\"\n");
  system( command);
  if(In.multi != 1) sleep(1);
}

static void PrintGML( NODE *node, Int NK)
{
  register Int i,j, nj;
  Int *lnk, n;
  char basename[128], filename[128];
  char command[128];
  FILE *out;

  if( In.printnet != 2) return;

  strcpy( basename, In.projname);
  if(In.reduction>0)
    sprintf(basename, "%s_R%d", In.projname, In.reduction);

  sprintf(filename, "%s.gml", basename);

  out = fopen( filename, "w");

  fprintf(out, "# Total number of nodes: %d\n", NK);
  fprintf(out, "# graph %s \n", basename);
  fprintf(out, "graph [\n", basename);
  fprintf(out, "####### NODES #######\n", NK);
  Loop(i,NK) {
    if(GetNodeDegree( &node[i])>0)
      fprintf(out, " node [ id %4d ]\n",i);
  }
  fprintf(out, "####### EDGES #######\n", NK);

  Loop(i,NK) {
    n = GetNodeDegree( &node[i]);
    if(n) {
      lnk = node[i].links;
      Loop(nj,n) {
	j = lnk[nj];
	if( j>i) {
	  fprintf(out, " edge [ source %4d target %4d ]\n",i,j);
	}
      }
    }
  }
  fprintf(out, "]\n");

  fclose(out);
  printf("File \"%s\" saved.\n", filename);

  printf("Invoking the external program \"Guide\"\n");

  sprintf( command, "Guide -# 5 -d 3 -g %s -i 4 -T 4 -l 1 -b 1 -s 0 -r 20 -R 20 -1 0 -2 0 -C 0 -S 3.0 -h 0.17 -D 0 &\n", filename); 

  system( command);
  if(In.multi != 1) sleep(1);
}

static void ListNet( NODE *node, Int NK)
{
  register Int i,j;
  Int *lnk, n;
  Real xi;

  Loop(i,NK) {
    xi = ReadNodeFitness( &node[i]);
    n = GetNodeDegree( &node[i]);
    lnk = node[i].links;
    printf("#%4d\t%8f\t%4d:\t", i, xi, n);
    Loop(j,n)
      printf("%4d ", lnk[j]);
    printf("\n");
  }
}
#undef DOTNOLBL
#undef DOTSIZEX
#undef DOTSIZEY
