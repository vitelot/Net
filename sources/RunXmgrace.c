#include "main.h"
#include "extern.h"
#include <unistd.h>

void RunXmgrace(void *VectorX, void *VectorY, 
		Field typeX, Field typeY,
		Int NK, 
		const char *title, 
		const char *labelX, const char *labelY)
     /* if VectorX == NULL then an integer vector 0...NK-1 will be used */
{ 
  if(!In.rungrace) return;

{
register int k;
char *datfile="tmp.dat";
char *parfile="tmp.par";
char cmd[128];
FILE *fp;
Int  *intVX  = (Int  *) VectorX;
Int  *intVY  = (Int  *) VectorY;
Real *realVX = (Real *) VectorX;
Real *realVY = (Real *) VectorY;

  if(VectorX==NULL) {
    typeX = INT;
    intVX = IntVectorAlloc(NK);
    Loop(k,NK)
      intVX[k]=k;
  }

  fp = fopen( datfile,"w");
  if(!fp) FileOpenError(datfile);

  if(In.rungrace==2) { /* LIN-LIN axes */

    for( k=0; k<NK; k++) {
      switch( typeX) {
      case INT:
	fprintf( fp, "%8d\t", intVX[k]);
	break;
      default:
      case REAL:
	fprintf( fp, "%12g\t", realVX[k]);
	break;
      }
      switch( typeY) {
      case INT:
	fprintf( fp, "%12d\n", intVY[k]);
	break;
      default:
      case REAL:
	fprintf( fp, "%12g\n", realVY[k]);
	break;
      }
    }

  } else if(In.rungrace==1) { /* Log-Log axes */

    if(typeX==INT && typeY==INT) {
      for( k=0; k<NK; k++)
	if(intVX[k]>0 && intVY[k]>0)
	  fprintf( fp, "%8d\t%8d\n", intVX[k],intVY[k]);

    } else if (typeX==INT && typeY==REAL) {
      for( k=0; k<NK; k++)
	if(intVX[k]>0 && realVY[k]>0)
	  fprintf( fp, "%8d\t%12g\n", intVX[k],realVY[k]);

    } else if (typeX==REAL && typeY==REAL) {
      for( k=0; k<NK; k++)
	if(realVX[k]>0 && realVY[k]>0)
	  fprintf( fp, "%12g\t%12g\n", realVX[k],realVY[k]);

    } else if (typeX==REAL && typeY==INT) {
      for( k=0; k<NK; k++)
	if(realVX[k]>0 && intVY[k]>0)
	  fprintf( fp, "%12g\t%8d\n", realVX[k],intVY[k]);

    }
  }

  fclose(fp);

  fp = fopen( parfile,"w");
  if(!fp) FileOpenError(parfile);

  fprintf(fp,
	  "#Mandatory descriptive comment\n"
	  "s0 line linewidth 3.0\n"
/*  	  "s0.y = s0.y * 1000\n" */
/*  	  "s0 line color 3\n" */
/*  	  "s1 line color 4\n" */
	  "title \"%s\"\n",
	  title
	  );

  if(In.rungrace==1)
    fprintf(fp,
	    "xaxes scale logarithmic\n"
	    "yaxes scale logarithmic\n"
	    );

  fprintf(fp, "xaxis label \"%s\"\nyaxis label \"%s\"\nautoscale \n", labelX, labelY );

  fclose(fp);

/*   sprintf( cmd, "xmgrace -geometry 1150x900 %s -batch %s &\n", */
  sprintf( cmd, "xmgrace -free -geometry 600x600 %s -batch %s &\n",
	   datfile, parfile);
  system(cmd);
  sleep(1);
  remove(datfile);
  remove(parfile);
  if(VectorX==NULL) IntVectorFree( intVX);

}}
