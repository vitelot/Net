#include "main.h"
#include "extern.h"

#define STARTING_NODE 0

static Int RandomSteps(void);

void TASRandomWalk( NODE *node, Int NK)
{
  if(!In.TASRW) return;
{
  char file[128];
  Int postnumber = In.TASRW;
  Int steps, k, n, rn;
  Int starting_node = STARTING_NODE;
  FILE *out;
  register int i,j,p;
  Int visited, new;
  Int *Visited =  IntVectorAlloc( NK);

  sprintf(file, "%s.tas", In.projname);
  printf("Generating the folksonomy. Output on file \"%s\".\n",file);

  out = fopen( file, "w");
  if( !out)  FileOpenError(file);

  fprintf(out, "#post_id tag_id user_id resource_id\n");

  IntVectorInit(Visited, NK, 0);

  for(p=1; p<=postnumber; p++) {
    steps = RandomSteps();
    n = starting_node;
    Loop(i,steps) {
      Visited[n] = p;
      fprintf(out, "%d %d 0 0\n", p, n);
      k = GetNodeDegree(&node[n]);
      visited = 0;
      Loop(j,k) {
	if(Visited[node[n].links[j]]==p) visited++;
      }
      if(visited==k) break; /* dead end */
      do {
	rn = (int) GetRandom(UNIF, 0 ,k);
	new = node[n].links[rn];
      } while(Visited[new]==p);
      n = new;
    }
  }
  fclose(out);
  printf("\n");

}
}

static Int RandomSteps(void) {

  return (int) GetRandom(EXP, .33, 0) + 1; /* .33 = 1/3 */
}
