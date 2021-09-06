#include "main.h"
#include "extern.h"

void DistanceDistrib( Int s, Int *d, Int NK)
{
  register Int i;
  char file[128];
  static FILE * fp;

  if(!In.printpairdist) return;

  sprintf(file, "=%s.%s.dat", In.projname, "PairDistance");

  if( s==0) { /* open the file at the very beginning */
    printf("\tSaving the Pair Distance. Output on file \"%s\".\n",file);
    fp = fopen( file, "w");
    if( !fp)  FileOpenError(file);
    fprintf(fp, "#%5s\t%6s\t%6s\n", "from", "to", "dist");
  }
  
  for( i=s+1; i<NK; i++)
    fprintf(fp, "%6d\t%6d\t%6d\n", s, i, d[i]);
    
  if( s==NK-1) /* close the file at the very end */
    fclose(fp);
}
    
