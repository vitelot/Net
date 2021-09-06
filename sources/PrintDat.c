#include "main.h"
#include "extern.h"

#define PAJEK 2

void PrintDat( NODE *node, Int NK)
{
  register Int i,j, nj;
  Bool isolated_exist = FALSE;
  Int *lnk, n, *nonemptytbl;
  Real xi, xj, wij=0.0;
  char filename[128], basename[128];
  FILE *out;

  if( !In.printdat) return;

  if( In.reduction>0)
    sprintf(basename, "%s_R%d", In.projname, In.reduction);
  else
    sprintf(basename, "%s", In.projname);

  if(In.printdat==PAJEK)
    sprintf( filename, "%s.paj", basename);
  else
    sprintf( filename, "%s.net", basename);

  out = fopen( filename, "w");
  if( !out)  FileOpenError(filename);

  nonemptytbl = IntVectorAlloc(NK);
  IntVectorInit( nonemptytbl, NK, -1);

  if(!In.nettype) { /* if undirected */
    for(n=i=0; i<NK; i++) {
      if(GetNodeDegree( &node[i])) {
	nonemptytbl[i] = n++;
      }}
  } else {
    for(n=i=0; i<NK; i++)
      if(GetNodeOutDegree( &node[i]) || GetNodeInDegree( &node[i]))
	nonemptytbl[i]=n++; /* directed case */
  }

  Loop(i,NK)
    if(nonemptytbl[i]<0) {
      isolated_exist = TRUE;
      break;
    }

  if(In.printdat==PAJEK) {
    fprintf(out, "*Network %s\r\n", In.projname);
    fprintf(out, "*Vertices %d\r\n",n);
    if( In.nettype==0 ) /* net is undirected? */
      fprintf(out, "*Edges\r\n");
    else
      fprintf(out, "*Arcs\r\n");
  } else {
    fprintf(out, "# Network: %s\n", In.projname);
    fprintf(out, "# Total number of nodes: %d\n", n);
    if(isolated_exist || In.reduction>0)
      fprintf(out, "# old index mapping at end of file\n");
    fprintf(out, "# Links follow:\n");
  }

  Loop(i,NK) {
    if(nonemptytbl[i]<0) continue; /* discard isolated nodes */
    xi = ReadNodeFitness( &node[i]);
    n = GetNodeDegree( &node[i]);
/*      fprintf(out, "\t\t//%4d: %4d (%8f)\n ", i, n, xi); */
    if(n) {
      lnk = node[i].links;
      Loop(nj,n) {
	j = lnk[nj];
        if(i==j) printf("WARNING: self loop found on node %d\n",j);
	xj = ReadNodeFitness( &node[j]);
	if(In.weighted) wij = node[i].weights[nj];

	if(In.printdat==PAJEK) {
	  if( In.nettype==0 ) { /* net is undirected? */
	    if(j>i) {
	      if(In.weighted)
		fprintf(out, "%d %d %g\r\n ", 
			1+nonemptytbl[i],1+nonemptytbl[j], wij);
	      else
		fprintf(out, "%d %d\r\n ", 
			1+nonemptytbl[i],1+nonemptytbl[j]);
	    }
	  } else {
	    if(In.weighted)
	      fprintf(out, "%d %d %g\r\n ", 
		      1+nonemptytbl[i],1+nonemptytbl[j], wij);
	    else
	      fprintf(out, "%d %d\r\n ", 
		      1+nonemptytbl[i],1+nonemptytbl[j]);
	  }

	} else {
	  if( In.nettype==0 ) { /* net is undirected? */
	    if(j>i) {
	      if(In.weighted) {
		if(In.readin || In.netgenerator!=FITNESS)
		  fprintf(out, "%4d\t%4d\t%10g\n ", 
			  nonemptytbl[i],nonemptytbl[j], wij);
		else
		  fprintf(out, "%4d\t%4d\t%10g\t\t#(%10.4f,%10.4f)\n ", 
			  nonemptytbl[i],nonemptytbl[j], wij, xi,xj);
	      }
	      else {
		if(In.readin || In.netgenerator!=FITNESS)
		  fprintf(out, "%4d\t%4d\n ", 
			  nonemptytbl[i],nonemptytbl[j]);
		else
		  fprintf(out, "%4d\t%4d\t\t#(%10.4f,%10.4f)\n ", 
			  nonemptytbl[i],nonemptytbl[j], xi,xj);
	      }
	    }
	  } else {
	    if(In.weighted)
	      fprintf(out, "%4d\t%4d\t%10g\n ", 
		      nonemptytbl[i],nonemptytbl[j], wij);
	    else {
	      if(In.readin || In.netgenerator!=FITNESS)
		fprintf(out, "%4d\t%4d\n ", 
		      nonemptytbl[i],nonemptytbl[j]);
	      else
		fprintf(out, "%4d\t%4d\t\t#(%10.4f,%10.4f)\n ", 
			nonemptytbl[i],nonemptytbl[j], xi,xj);
	    }
	  }

	}
      }
    }
  }

  if(isolated_exist || In.reduction>0) {
    fprintf(out, "#\n#\n#\n");
    fprintf(out, "# old index mapping #\n");
    fprintf(out, "# OLDIDX NEWIDX\n");
    Loop(i,NK)
      if(nonemptytbl[i]!=-1)
	fprintf(out, "# %6d %6d\n",i, nonemptytbl[i]);
  }

  fclose(out);
  printf("File \"%s\" saved.\n", filename);
  IntVectorFree( nonemptytbl);
}

#undef PAJEK
