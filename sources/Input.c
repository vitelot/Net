#include "main.h"
#include "extern.h"

static void create_ini( char *);
static void printinfo(Bool);
static void PrintLinkType(void);

void InputParameters( char *ini_file)
{
FILE *fp;
char line[128], *p;
int totlin=48;
double version;

    fp = fopen( ini_file, "r");
    if( !fp) {
      printf("Error opening file %s\n", ini_file);
      printf("Creating a default one.\n\n");
      create_ini( ini_file);
    }

    while( !feof(fp)) {
      fgets( line, 126, fp);
      if( line[0] == '#') continue; /* lines starting with # are comments */
      /* read up to # or line end */
      for( p=line; *p!='#' && *p!='\0'; p++) ;
      *p = '\0'; /* skip inline comments */

      if(sscanf(line, " VERSION %lf", &version)           ==1) {
	totlin--;
	if(version != VERSION) {
	  perr("The initialization file \"%s\" belongs to an old release %.2lf.\n", ini_file, version);
	  perr("Please delete it and rerun the program to create its new version.\n");
	  exit(1);
	}
	continue;
      }
      /*###################################################################*/
      if(sscanf(line, " NK         =   %d", &In.nk)      ==1) {totlin--; continue;}

      if(sscanf(line, " DISTRIB    =   %d", &In.distrib) ==1) {totlin--; continue;}
      if(sscanf(line, "   A        =   %f", &In.Aparam)  ==1) {totlin--; continue;}
      if(sscanf(line, "   B        =   %f", &In.Bparam)  ==1) {totlin--; continue;}
      if(sscanf(line, " LINKTYPE   =   %d", &In.linktype)==1) {totlin--; continue;}
      if(sscanf(line, "   Z        =   %f", &In.cutoff)  ==1) {totlin--; continue;}
      if(sscanf(line, "   M        =   %f", &In.m)       ==1) {totlin--; continue;}
      if(sscanf(line, "   E        =   %f", &In.E)       ==1) {totlin--; continue;}
      if(sscanf(line, " TREE       =   %d", &In.tree)    ==1) {totlin--; continue;}
      if(sscanf(line, " ACYCLIC    =   %d", &In.acyclic) ==1) {totlin--; continue;}

      if(sscanf(line, " BA_N0      =   %d", &In.BAstartnodes) ==1) {totlin--; continue;}
      if(sscanf(line, " BA_M       =   %d", &In.BAcominglinks) ==1) {totlin--; continue;}
      if(sscanf(line, " BA_MEM_A   =   %f", &In.BAMemoryA) ==1) {totlin--; continue;}
      if(sscanf(line, " BA_MEM_B   =   %f", &In.BAMemoryB) ==1) {totlin--; continue;}

      if(sscanf(line, " GN_RDISTR  =   %d", &In.GNradiusdistr) ==1) {totlin--; continue;}
      if(sscanf(line, " GN_RMIN    =   %f", &In.GNrmin) ==1) {totlin--; continue;}
      if(sscanf(line, " GN_RMAX    =   %f", &In.GNrmax) ==1) {totlin--; continue;}
      if(sscanf(line, " GN_P_RMIN  =   %f", &In.GNprmin) ==1) {totlin--; continue;}

      if(sscanf(line, " PROJNAME   =   %s", In.projname) ==1) {totlin--; continue;}
      if(sscanf(line, " NET_GENR   =   %d", &In.netgenerator) ==1) {totlin--; continue;}
      if(sscanf(line, " NET_TYPE   =   %d", &In.nettype) ==1) {totlin--; continue;}
      if(sscanf(line, " WEIGHTED   =   %d", &In.weighted)==1) {totlin--; continue;}
      if(sscanf(line, " TASRW      =   %d", &In.TASRW)==1) {totlin--; continue;}
      if(sscanf(line, " TAS        =   %d", &In.TAS)==1) {totlin--; continue;}
      if(sscanf(line, " SELFLOOPS  =   %d", &In.SelfLoops)==1) {totlin--; continue;}
      if(sscanf(line, " MULTI      =   %d", &In.multi)   ==1) {totlin--; continue;}
      if(sscanf(line, " READ_IN    =   %d", &In.readin)  ==1) {totlin--; continue;}

      if(sscanf(line, " SAVE_NET   =   %d", &In.printdat)==1) {totlin--; continue;}
      if(sscanf(line, " SHOW_NET   =   %d", &In.printnet)==1) {totlin--; continue;}
      if(sscanf(line, " RUN_GRACE  =   %d", &In.rungrace)==1) {totlin--; continue;}
      if(sscanf(line, " TAS_RESHUF =   %d", &In.TASreshuf)     ==1) {totlin--; continue;}
      if(sscanf(line, " DEGREE_DISTRIB =   %d", &In.degdistr)     ==1) {totlin--; continue;}
      if(sscanf(line, " KNN            =   %d", &In.knn)          ==1) {totlin--; continue;}
      if(sscanf(line, " CLUSTER_COEFF  =   %d", &In.clcoeff)      ==1) {totlin--; continue;}
      if(sscanf(line, " CLUSTER_COEFF2 =   %d", &In.cl2coeff)     ==1) {totlin--; continue;}
      if(sscanf(line, " SCC            =   %d", &In.scc)          ==1) {totlin--; continue;}
      if(sscanf(line, " COMMUNITIES    =   %d", &In.communities)  ==1) {totlin--; continue;}
      if(sscanf(line, " REDUCTION      =   %d", &In.reduction)    ==1) {totlin--; continue;}
      if(sscanf(line, " REWIRING       =   %d", &In.rewiring)     ==1) {totlin--; continue;}
      if(sscanf(line, " LANCZOS        =   %d", &In.lanczos)      ==1) {totlin--; continue;}
      if(sscanf(line, " AMATRIX        =   %d", &In.amatrix)      ==1) {totlin--; continue;}
      if(sscanf(line, " EDGE_BETWEEN   =   %d", &In.edgebetw)     ==1) {totlin--; continue;}
      if(sscanf(line, " SITE_BETWEEN   =   %d", &In.sitebetw)     ==1) {totlin--; continue;}
      if(sscanf(line, " RW_SITE_BETW   =   %d", &In.rwsitebetw)   ==1) {totlin--; continue;}
      if(sscanf(line, " PAIR_DISTANCE  =   %d", &In.printpairdist)==1) {totlin--; continue;}
      if(sscanf(line, " SAVE_CLUSTER   =   %d", &In.printcluster) ==1) {totlin--; continue;}
      if(sscanf(line, " SPLIT_CLUSTER  =   %d", &In.splitcluster) ==1) {totlin--; continue;}
      /* if you reach here, the line is not recognized */
      perr("The following line in %s was not recognized:\n%s\n"
	   "Exiting.\n", ini_file, line);
      exit(1);
    }
     fclose(fp);

     if(totlin > 0) {
       printf("There are %d lines less in your %s file. Check for missing ones. Exiting.\n",
	      totlin, ini_file);
       exit(1);
     }
     if(totlin < 0) {
       printf("There are %d lines more in your %s file. Check for duplicates. Exiting.\n",
	      -totlin, ini_file);
       exit(1);
     }

     if(In.multi<1) In.multi=1;

     printinfo(FALSE);
     printinfo( TRUE);
}

#define  prbool(x) ((x)? "TRUE": "FALSE")
#define  prnettype(x) ((x)? "DIRECTED": "UNDIRECTED")
#define  prnetgentype(x) ((x==0)? "FITNESS": "BA")

static void printinfo(Bool tofile)
{
FILE *fp=stdout;

  if(tofile) {
    char file[128];
    sprintf( file, "+%s.init", In.projname);
    fp = fopen( file, "w");
    if(!fp) FileOpenError( file);
  }

  fprintf(fp, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
  fprintf(fp, "IIIIIIII Main computational parameters IIIIIIIIIII\n");
  fprintf(fp, " NK        = %d\n",                           In.nk);
  fprintf(fp, "  IIIIIIIIIIII  FITNESS parameters  IIIIIIIIIIIIII\n");
  fprintf(fp, "   DISTRIB   = %d\n",                      In.distrib);
  fprintf(fp, "     A       = %f\n",                       In.Aparam);
  fprintf(fp, "     B       = %f\n",                       In.Bparam);
  fprintf(fp, "   LINKTYPE  = %d\n",                     In.linktype);
  fprintf(fp, "     Z       = %f\n",                       In.cutoff);
  fprintf(fp, "     M       = %f\n",                            In.m);
  fprintf(fp, "     E       = %f\n",                            In.E);
  fprintf(fp, "   TREE      = %s\n",                  prbool(In.tree  ));
  fprintf(fp, "   ACYCLIC   = %s\n",                  prbool(In.acyclic ));
  fprintf(fp, "  IIIIIIIIII  Barabasi-Albert parameters  IIIIIIIII\n");
  fprintf(fp, "   BA_N0     = %d\n",                In.BAstartnodes);
  fprintf(fp, "   BA_M      = %d\n",                In.BAcominglinks);
  fprintf(fp, "   BA_MEM_A  = %f\n",                In.BAMemoryA);
  fprintf(fp, "   BA_MEM_B  = %f\n",                In.BAMemoryB);
  fprintf(fp, "  IIIIIIII  2D Geographical Network params  IIIIIII\n");
  fprintf(fp, "   GN_RDISTR = %d\n",                In.GNradiusdistr);
  fprintf(fp, "   GN_RMIN   = %f\n",                In.GNrmin);
  fprintf(fp, "   GN_RMAX   = %f\n",                In.GNrmax);
  fprintf(fp, "   GN_P_RMIN = %f\n",                In.GNprmin);
  fprintf(fp, "IIIIIIII Basic control  IIIIIIIIIIIIIIIIIIIIIIIIIII\n");
  fprintf(fp, " PROJNAME  = \"%s\"\n",                 In.projname);
  fprintf(fp, " NET_GENR  = %d\n",                     In.netgenerator);
  fprintf(fp, " NET_TYPE  = %s\n",                  prnettype(In.nettype));
  fprintf(fp, " WEIGHTED  = %s\n",                  prbool(In.weighted  ));
  fprintf(fp, " TASRW     = %s\n",                  prbool(In.TASRW));
  fprintf(fp, " TAS       = %s\n",                  prbool(In.TAS  ));
  fprintf(fp, " SELFLOOPS = %s\n",                  prbool(In.SelfLoops  ));
  fprintf(fp, " MULTI     = %d\n",                       In.multi  );
  fprintf(fp, " READ_IN   = %s\n",                  prbool(In.readin  ));
  fprintf(fp, "IIIIIIII Output control IIIIIIIIIIIIIIIIIIIIIIIIIII\n");
  fprintf(fp, " SAVE_NET  = %s\n",                  prbool(In.printdat));
  fprintf(fp, " SHOW_NET  = %s\n",                  prbool(In.printnet));
  fprintf(fp, " RUN_GRACE = %s\n",                  prbool(In.rungrace));
  fprintf(fp, " TAS_RESHUF = %s\n",                 prbool(In.TASreshuf));
  fprintf(fp, " DEGREE_DISTRIB = %s\n",             prbool(In.degdistr));
  fprintf(fp, " KNN            = %s\n",             prbool(In.knn));
  fprintf(fp, " CLUSTER_COEFF  = %s\n",             prbool(In.clcoeff));
  fprintf(fp, " CLUSTER_COEFF2 = %s\n",             prbool(In.cl2coeff));
  fprintf(fp, " REDUCTION      = %d\n",             In.reduction);
  fprintf(fp, " REWIRING       = %d\n",             In.rewiring);
  fprintf(fp, " COMMUNITIES    = %s\n",             prbool(In.communities));
  fprintf(fp, " SCC            = %s\n",             prbool(In.scc));
  fprintf(fp, " LANCZOS        = %s\n",             prbool(In.lanczos));
  fprintf(fp, " AMATRIX        = %d\n",                  In.amatrix);
  fprintf(fp, " SAVE_CLUSTER   = %s\n",             prbool(In.printcluster));
  fprintf(fp, " SPLIT_CLUSTER  = %s\n",             prbool(In.splitcluster));
  fprintf(fp, " EDGE_BETWEEN   = %s\n",             prbool(In.edgebetw));
  fprintf(fp, " SITE_BETWEEN   = %s\n",             prbool(In.sitebetw));
  fprintf(fp, " RW_SITE_BETW   = %s\n",             prbool(In.rwsitebetw));
  fprintf(fp, " PAIR_DISTANCE  = %s\n",             prbool(In.printpairdist));
  fprintf(fp, "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n\n");

  if(tofile) {
    fclose( fp);
    return;
  }

  if(In.netgenerator==FITNESS) PrintLinkType();
  if(In.tree)
    printf("A TREE will be created.\n\n");
  if(In.acyclic)
    printf("An ACYCLIC graph will be created.\n\n");

  fflush(stdout);
} 

static void create_ini( char *file)
{
  FILE *fel;

    fel = fopen( file, "w");
    if( !fel) {
      perr("Cannot create default %s ini-file. Aborting.\n", file);
      exit(1);
    }
    fprintf( fel, 
     "############################################################################\n"
     "### NET's default initialization file ######################################\n"
     "############################################################################\n");
    fprintf( fel, 
     " VERSION %4.2f                         ######################################\n", VERSION);
    fprintf( fel, 
     "############################################################################\n"
     "# Use the flag -h to have a list of command line options\n"
     "################### Master parameters ######################################\n"
     "#\n"
     " NK         =   50		# Number of nodes\n"
     "#\n");
    fprintf( fel, 
     "# The following three fields select the random distribution of fitnesses:\n"
     "#   0: Uniform [ x in (A,B) ]\n"
     "#   1: Exponential [ A*exp(-A*x), x>0 ]\n"
     "#   2: Gaussian [ (2*Pi*A^2)^-0.5*exp(-x^2/2A^2), x>0 ]\n"
     "#   3: Power [ c*x^-A if x>B,  0.0 if x<=B ]\n"
     "#\n"
     " DISTRIB    =   0                 # See comment lines above\n"
     "   A        =   0.0		# Parameter for the distribution above\n"
     "   B        =   1.0		# Another parameter for the distribution above\n");
    fprintf( fel, 
     " LINKTYPE   =   0 		# Type of function to use as linking probability\n"
     "   Z        =   0.0		# Cutoff in the linking probability\n"
     "   M        =   0.03 	        # Probability of successfull connections per node\n"
     "   E        =   0.0 	        # Parameter in the linking prob (similar to kT in Fermi distr.)\n"
     " TREE       =   0 	        # Force the generation of a tree\n"
     " ACYCLIC    =   0 	        # Force the generation of acyclic graphs\n"
     "#\n");
    fprintf( fel, 
     "# The following two fields define Barabasi-Albert parameters:\n"
     " BA_N0      =   2                 # Starting clique order\n"
     " BA_M       =   1                 # Links entering at each step\n"
     " BA_MEM_A   =   0                 # Memory kernel parameter: if <=0 plain B-A\n"
     " BA_MEM_B   =   0                 # Memory kernel = pow(t+A,-B) if B==0 plain B-A, if B<0 exp(-t/a)\n"
     "#\n");
    fprintf( fel, 
     "# The following 4 lines define 2D Geog. Netw. parameters:\n"
     "#   0: fixed radius = GN_RMIN\n"
     "#   1: two radii GN_RMIN (with probability GN_P_RMIN) and GN_RMAX\n"
     "#   2: radii uniform distr between GN_RMIN and GN_RMAX\n"
     "#   3: radii centered exponential distr A*exp(-|x-b|/a)/a with a=GN_RMIN and b=GN_RMAX\n"
     "#   4: radii bounded power-law distr between GN_RMIN and GN_RMAX\n"
     "#\n");
    fprintf( fel, 
     " GN_RDISTR  =   0                 # Distrib of radii as above explained\n"
     " GN_RMIN    =   0.01              # Minimum radius\n"
     " GN_RMAX    =   0.011             # Maximum radius\n"
     " GN_P_RMIN  =   0.5               # Prob. of GN_RMIN for case nr.1\n"
     "#\n");
    fprintf( fel, 
     "################### Basic control  #########################################\n"
     "#\n"
     " PROJNAME   =   %s		# Project name\n"
     " NET_GENR   =   0  		# 0=FITNESS, 1=BA, 2=MG, 3=GN\n"
     " NET_TYPE   =   0  		# 0=undirected, 1=directed\n"
     " WEIGHTED   =   0  		# 0=unweighted, 1=weighted edges (only with READ_IN=1)\n"
     " TASRW      =   0  		# number of posts to generate with the RW.\n"
     " TAS        =   0  		# 1=read data is a folksonomy: list of TAS.\n"
     " SELFLOOPS  =   0  		# 1=Allow self-loops. useful in spectral analysis\n"
     " MULTI      =   1  		# If>1 do multiple runs\n"
     " READ_IN    =   0  		# Read net from file PROJNAME.in\n"
     "#\n", In.projname);
    fprintf( fel, 
     "################### Output control #########################################\n"
     "#\n"
     " SAVE_NET       =   1  		# Save the resulting net on file 1=.net 2=.paj for pajek\n"
     " SHOW_NET       =   0  		# Display the resulting net on screen 1=dot 2=guide\n"
     " RUN_GRACE      =   0  		# Run xmgrace at the end: 1=log-log 2=lin-lin\n"
     " TAS_RESHUF     =   0  		# 1=Reshuffle Tag ASignments and exits\n"
     " DEGREE_DISTRIB =   1  		# Calculates and saves the degree distrib\n"
     " KNN            =   0  		# Calculates and saves the nearest neigh connectivity\n");
    fprintf( fel, 
     " CLUSTER_COEFF  =   0  		# Calculates and saves the clustering coeff\n"
     " CLUSTER_COEFF2 =   0  		# Calculates and saves the clustering coeff up to 2nd neighs\n"
     " REDUCTION      =   0  		# Reduces the net to that nr of nodes. 0=do nothing.\n");
    fprintf( fel, 	     
     " REWIRING       =   0             # Nr of rewirings, 0 for none.\n"
     " SCC            =   0  		# Finds the Strongly Connected Components of a directed graph.\n"
     " COMMUNITIES    =   0  		# Calculates the community size distribution\n"
     " AMATRIX        =   0  		# Calc eigvals and eigvects of graph matrices: 1=A 2=L 3=N\n"
     " LANCZOS        =   0  		# Calculates eigvals and eigvects using lanczos routines\n");
    fprintf( fel, 
     " SAVE_CLUSTER   =   0  		# Save the node cluster sizes\n"
     " SPLIT_CLUSTER  =   0  		# Save found clusters onto separate files\n"
     " EDGE_BETWEEN   =   0  		# Calculates and saves the edge betweenness\n"
     " SITE_BETWEEN   =   0  		# Calculates and saves the site betweenness\n"
     " RW_SITE_BETW   =   0  		# Calculates and saves the random walk site betweenness\n"
     " PAIR_DISTANCE  =   0  		# Save list of pairs and relative distance\n"
     "#\n"
     "######################## END ###############################################\n"
     );
    fclose( fel);
    printf("Default \"%s\" initialization file created. You might edit it.\n", file);
    printf("Exiting...\n");
    exit(1);
}

static void PrintLinkType(void)
{
  if(In.readin) return;

  printf("Linking function F(x,y) = ");

  switch( In.linktype) {
  case 1:
    if(In.E==0) printf("m*THETA(Z-|x-y|)\n\n");
    else printf(" m/(1 + EXP( (|x-y|-Z)/E) )\n\n");
    break;
  case 2:
    printf("m*(x*y)/Z^2 \n\n");
    break;
  case 3:
    printf("User defined 1. Look at source file 'LinkProbability.c'\n\n");
    break;
  case 4:
    printf("User defined 2. Look at source file 'LinkProbability.c'\n\n");
    break;
  case 5:
    printf("User defined 3. Look at source file 'LinkProbability.c'\n\n");
    break;
  default:
    if(In.E==0) printf("m*THETA(x+y-Z)\n\n");
    else printf("m/(1 + EXP( (Z-x-y)/E) )\n\n");
  }
}
