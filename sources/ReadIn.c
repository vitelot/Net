#include "main.h"
#include "extern.h"

static Int FindMaxMinIndex( FILE *in);

NODE * ReadIn( NODE *node, Int *NK)
{
register int linecount=0, linkcount=0;
FILE *in;
char line[128], infile[128], *p;
 Int n1, n2, loopcount=0;
double w;

  sprintf(infile, "%s.in", In.projname);

  if(In.TASreshuf) { /* assume it is a TAS list (folksonomy) to reshuffle */
    sprintf(line, "perl ./TAS_shuffler.pl %s", infile);
    system(line);
    printf("Please rerun with suggested project name. Exiting.\n");
    exit(1);
  }
  if(In.TAS) { /* assume it is a TAS list (folksonomy) */
    sprintf(line, "perl ./TAS_parser.pl %s", infile);
    system(line);
    printf("Please rerun with suggested project name. Exiting.\n");
    exit(1);
  }

  in = fopen( infile, "r");
  if( !in) {
    printf("Error opening file %s\n. Exit.\n", infile);
    exit(1);
  }

  In.nk = *NK = 1 + FindMaxMinIndex( in);

  node = NodeAlloc( *NK);
  printf("Number of nodes set to %d according to input file %s\n",
	 *NK, infile);
  NodeInit( node, *NK);

  while( !feof(in)) {
    fgets( line, 126, in); linecount++;
    if( line[0] == '#') continue; /* lines starting with # are comments */
    /* read up to # or line end */
    for( p=line; *p!='#' && *p!='\0'; p++) ;
    *p = '\0'; /* skip inline comments */

    if(sscanf( line, "%d %d %lf", &n1, &n2, &w)<2) /* fetch link and weight */
      continue; /* to cure empty lines */

    if(n1>=*NK || n2>=*NK) {
      perr("Error reading file \"%s\" on line <%d>: Node number overflow.\n",
	   infile, linecount);
      exit(1);
    }
    if(n1<0 || n2<0) {
      perr("Error reading file \"%s\" on line <%d>: negative node number.\n",
	   infile, linecount);
      exit(1);
    }

    if(n1==n2) loopcount++;

    if(In.nettype)
      AddOneWayLink( &node[n1], &node[n2],  w);
    else
      AddTwoWayLink( &node[n1], &node[n2],  w);
    ++linkcount;

    line[0] = '\0'; /* reset the line read; reads the last link twice otherwise */
  }

  fclose( in);

  printf("File \"%s\": total lines read %d, total %s links set %d.\n\n",
	 infile, linecount, (In.nettype)?"directed":"undirected",linkcount);

  if(loopcount)  printf("Found %d self loops.\n", loopcount);

  return node;
}

static Int FindMaxMinIndex( FILE *in)
{
char line[128], *p;
Int n1, n2, maxidx, minidx;
double w;
int fields, weighted=0, cline=0;

  printf("Scanning network input file looking for maximum node index\n");

  maxidx=-1; minidx=1e8;
  while( !feof(in)) {
    fgets( line, 126, in);
    if( line[0] == '#') continue; /* lines starting with # are comments */
    /* read up to # or line end */
    for( p=line; *p!='#' && *p!='\0'; p++) ;
    *p = '\0'; /* skip inline comments */

    fields=sscanf( line, "%d %d %lf", &n1, &n2, &w); /* fetch links */
    if(fields<2) continue; /* to cure empty lines */
    if(fields==3) ++weighted; /* Probably a weighted graph */

    ++cline;

    if(minidx>n1) minidx=n1;
    if(minidx>n2) minidx=n2;
    if(maxidx<n1) maxidx=n1;
    if(maxidx<n2) maxidx=n2;
  }

  if(weighted) {
    if(cline==weighted) {
      printf("The network read seems to be a weighted graph");
      if(!In.weighted)
	printf(", but the WEIGHTED flag is not set.\n  Continuing as unweighted.\n");
      else printf(".\n");
    } else {
      printf("%d of %d lines contain edge weights.\n",weighted,cline);
      if(In.weighted) {
	printf("ERROR: WEIGHTED flag was set. Exit.\n");
	exit(1);
      } else 
	printf("Weights are ignored.\n");
    }
  }
  if(weighted==0 && In.weighted) {
    printf("ERROR: WEIGHTED flag is set, but no weights found.\n");
    exit(1);
  }

  printf("Node index running from %d to %d\n", minidx, maxidx);
  if(minidx==1)
    printf("Node number 0 will exist and will be disconnected from the rest\n");
  else if(minidx>1)
    printf("Nodes from 0 to %d will exist and will be disconnected from the rest\n",
	   minidx-1);

  rewind(in);

  return maxidx;
}
