#include "main.h"
#include "extern.h"

void SiteTraffic( NODE *node, Int NK)
{
register int i,j,n;
Int K;
Int nloops = 10;/*In.traffic;*/
Real *Traffic, *OldTraffic;
char file[128];
FILE *fp;

/*      if(!In.traffic) return; */

  printf("\nCalculating the Site Traffic.\n");
  sprintf(file, "=%s.%s.dat", In.projname, "SiteTraffic");
  printf("Output on file \"%s\".\n", file);

  Traffic    = RealVectorAlloc( NK);
  OldTraffic = RealVectorAlloc( NK);

  RealVectorInit( Traffic, NK, 1.0);

/*    Loop(n,nloops) { */
/*      RealVectorCopy( OldTraffic, Traffic, NK); */
/*      Loop(i,NK) { */
/*        K = GetNodeDegree(&node[i]); */
/*        Loop(j, K) { */
/*  	Traffic[i] += OldTraffic[node[i].links[j]]; */
/*        } */
/*      } */
/*    } */

  Loop(n,nloops) {
    RealVectorCopy( OldTraffic, Traffic, NK);
    Loop(i,NK) {
      K = GetNodeDegree(&node[i]);
      Traffic[i] = 0.0;
      Loop(j, K) {
	Traffic[i] += 
	  OldTraffic[node[i].links[j]]/GetNodeDegree(&node[node[i].links[j]]);
      }
    }
  }

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fprintf(fp, "#%5s\t%13s\n",
	  "i", "Traffic(i)");
  Loop(i,NK) {
    fprintf(fp, "%6d\t%13g\n",
	    i, Traffic[i]);
  }
  fclose(fp);

  puts("");

  RealVectorFree(Traffic);
  RealVectorFree(OldTraffic);
}
