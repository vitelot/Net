#include "main.h"
#include "extern.h"

extern void ScanCommandLineParams( int argc, char *argv[], char *name);
extern void MultiStatistics( Int NK);
extern void Reduction(NODE *, Int);
extern void TASRandomWalk( NODE *, Int);

FILE *fperr;
long RArg;
struct Input In;

int main( int argc, char *argv[])
{
NODE *node=NULL;
enum RndDistrib RDType;
register int i = 0;
Int NK; /*  Total nr of nodes */
char ProjName[128];
char inifile[128]="NET.INI";

 printf("\nProgram Net.Linux Version %4.2f is running.\n\n",VERSION); 
 fperr = stderr;

 ScanCommandLineParams( argc, argv, inifile);
 InputParameters(inifile);

 NK = In.nk;
 RDType = In.distrib;
 sprintf(ProjName, "%s", In.projname);

 RandomInit( &RArg); /* Initialise the random number generator */

/*   i=97; */
 do {

   if( In.multi>1) {
     sprintf(In.projname, "%s%04d", ProjName, i);
     printf("\n$$$$$$$$$$$$$$$$$$$$$$ %03d $$$$$$$$$$$$$$$$$$$$$$\n",i);
   }

   if( In.readin) /* read net from file */
     node = ReadIn( node, &NK);
   else {
     node = NodeAlloc( NK);
     NodeInit( node, NK);
     switch(In.netgenerator) {
     case FITNESS:
       NodeInitFitnesses( node, NK, RDType, In.Aparam, In.Bparam);
       AssignLinks( node, NK);
       break;
     case BA:  /* Barabasi-Albert */
       BarabasiAlbert( node, NK);
       break;
     case MINIMUM_GROWTH:  /* Minimum Growth */
       MinimumGrowth( node, NK);
       break;
     case GEO_NET:  /* 2D Geogr network */
       GeoNet( node, NK);
       break;
     default:
       printf("No net generation algorithm chosen. Exit.\n");
     }
   }

   TASRandomWalk( node, NK);

   Reduction( node, NK);

   Rewiring( node, NK);

   PrintDat( node, NK);

   Analyze( node, NK);

   DisplayNet( node, NK);

   NodeFree( node, NK);
 } while(++i < In.multi && In.multi > 1);

 sprintf(In.projname, "%s", ProjName);
 if( In.multi>1) MultiStatistics(NK);

 printf("\n------------------ END -----------------\n\n");
 return 0;
}
