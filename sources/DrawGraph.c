#include "main.h"
#include "extern.h"
#include <time.h>

#define SCALE 400 /* a single node will be placed in a SCALExSCALE pixel box */
#define BORDER 10
#define NODESIZERATIO 80.0 /* max radius of nodes equals max side / NODESIZERATIO */
typedef struct { 
  float x,y; /* coordinates */
  float r; /* radius (size) */
  float cr,cg,cb; /* rgb color */
} Point; /* point in the plane */

static void InitPoints( Point *P, NODE *node, Int NK);
extern void PlacePoints( Point *P, NODE *node, Int NK);
static void PrintEPS( Point *P, NODE *node, Int NK);
static void PrintEPSPreamble(FILE *eps, Point *P, Int NK);
static void PrintEPSNodes(FILE *eps, Point *P, Int NK);
static void PrintEPSLinks(FILE *eps, Point *P, NODE *node, Int NK);

void DrawGraph( NODE *node, Int NK) {

  Point *P;

  P = (Point *) malloc( NK*sizeof(Point) );

  InitPoints( P, node, NK);

  PlacePoints( P, node, NK);

  PrintEPS( P, node, NK);

  free(P);
}

static void InitPoints( Point *P, NODE *node, Int NK) {
  register int i;
  enum {CIRCULAR, RANDOM} DrawType;

  DrawType = CIRCULAR;
/*   DrawType = RANDOM; */

  switch(DrawType) {
  case CIRCULAR: {
    const float radius = 10;
    float angle, r=M_PI*radius/NK *.7;
    Loop(i,NK) {
      angle = 2.* M_PI / NK * i;
      P[i].x = radius * cos(angle);
      P[i].y = radius * sin(angle);
      P[i].r = r;
      P[i].cr = 1.0;
      P[i].cg = 0.0;
      P[i].cb = 0.0;
    }
    break;}
  case RANDOM:
    srand( (unsigned int) time(NULL));
    Loop(i,NK) {
      P[i].x = rand()/(1.+RAND_MAX);
      P[i].y = rand()/(1.+RAND_MAX);
      P[i].r = 1./20;
      P[i].cr = 0.0;
      P[i].cg = 1.0;
      P[i].cb = 0.0;
    }
    break;
  }
}

static void PrintEPS( Point *P, NODE *node, Int NK) {
  FILE *eps;
  char file[128];

  sprintf(file, "=%s.%s.eps", In.projname, "Display");
  eps = fopen( file, "w");
  if( !eps)  FileOpenError(file);
  
  printf("Generating file %s\n", file);

  PrintEPSPreamble(eps, P, NK);

  PrintEPSLinks(eps, P, node, NK);

  PrintEPSNodes(eps, P, NK);

  fclose(eps);
}

static void PrintEPSPreamble(FILE *eps, Point *P, Int NK) {

  register int i;
  int llx, lly, urx, ury;
  int xedge, yedge;
  float xmax, ymax, xmin, ymin, rmax;
  float dx,dy, scale;

  xmax=xmin=P[0].x;
  ymax=ymin=P[0].y;
  rmax=P[0].r;
  Loop(i,NK) {
    if(rmax<P[i].r) rmax=P[i].r;
    if(xmax<P[i].x) xmax=P[i].x;
    if(ymax<P[i].y) ymax=P[i].y;
    if(xmin>P[i].x) xmin=P[i].x;
    if(ymin>P[i].y) ymin=P[i].y;
  }
  xmax += rmax;
  xmin -= rmax;
  ymax += rmax;
  ymin -= rmax;

  dx = (xmax-xmin);
  dy = (ymax-ymin);
  if(dx>dy) scale = SCALE/dx;
  else scale = SCALE/dy;

  xedge = scale*dx;
  yedge = scale*dy;

  llx = -BORDER;
  lly = -BORDER;
  urx = xedge+BORDER;
  ury = yedge+BORDER;

  fprintf( eps, "%%!PS-Adobe-2.0 EPSF-3.0\n");
  fprintf( eps, "%%%%Title: Draw Graph\n");
  fprintf( eps, "%%%%Creator: Net (by V.D.P. Servedio)\n");

  fprintf(eps, "%%%%BoundingBox: %d %d %d %d\n\n",llx,lly, urx,ury);
  fprintf(eps, "%% useful shortcuts\n");
  fprintf(eps, "/D {def} bind def\n");
  fprintf(eps, "/B {bind def} bind def\n");
  fprintf(eps, "/l {lineto} B\n");
  fprintf(eps, "/rl {rlineto} B\n");
  fprintf(eps, "/m {moveto} B\n");
  fprintf(eps, "/rm {rmoveto} B\n");
  fprintf(eps, "/tr {translate} B\n");
  fprintf(eps, "/gs {gsave} B\n");
  fprintf(eps, "/gr {grestore} B\n");
  fprintf(eps, "/x {exch} B\n");
  fprintf(eps, "/w {setlinewidth} B\n");
  fprintf(eps, "/q {setrgbcolor} B\n");
  fprintf(eps, "\n");

  fprintf(eps, "%% NODE shape\n");
  fprintf(eps, "%% r g b x y radius NODE\n");
  fprintf(eps, "/NODE {\n");
  fprintf(eps, "  gs\n");
  fprintf(eps, "  /RADIUS x D\n");
  fprintf(eps, "  tr\n");
  fprintf(eps, "  0 0 RADIUS 0 360 arc\n");
  fprintf(eps, "  gs q fill gr\n");
  fprintf(eps, "  stroke\n");
  fprintf(eps, "  gr\n");
  fprintf(eps, "} B\n");
  fprintf(eps, "\n");

  fprintf(eps, "%% LINK shape\n");
  fprintf(eps, "%% x1 y1 x2 y2 LINK\n");
  fprintf(eps, "/LINK {\n");
  fprintf(eps, "  gs\n");
  fprintf(eps, "  m\n");
  fprintf(eps, "  l\n");
  fprintf(eps, "  stroke\n");
  fprintf(eps, "  gr\n");
  fprintf(eps, "} B\n");
  fprintf(eps, "\n");


  fprintf(eps, "%% A4 paper format is 595x842 pts\n\n");
  /* print "% set the line style\n"; */
  /* print "1 setlinecap $thick w\n"; */
  fprintf(eps, "%% set new scale\n");
  fprintf(eps, "%f %f scale\n\n", scale,scale);
  fprintf(eps, "%% set new origin\n");
  fprintf(eps, "%f %f tr\n",-xmin,-ymin);
  fprintf(eps, "%% set new line width\n");
  fprintf(eps, "%f w\n\n", 2./scale);/* 2 px */

}

static void PrintEPSNodes(FILE *eps, Point *P, Int NK) {
  register int i;
  float rmax, xmax,ymax, xmin,ymin;
  float scale, dx,dy;

  xmax=xmin=P[0].x;
  ymax=ymin=P[0].y;
  rmax=P[0].r;
  Loop(i,NK) {
    if(rmax<P[i].r) rmax=P[i].r;
    if(xmax<P[i].x) xmax=P[i].x;
    if(ymax<P[i].y) ymax=P[i].y;
    if(xmin>P[i].x) xmin=P[i].x;
    if(ymin>P[i].y) ymin=P[i].y;
  }

  dx = (xmax-xmin);
  dy = (ymax-ymin);
  if(dx<dy) scale = dx/NODESIZERATIO/rmax;
  else scale = dy/NODESIZERATIO/rmax;;

  Loop(i,NK) { P[i].r *= scale; }

  Loop(i,NK) {
    fprintf(eps, "%f %f %f %f %f %f NODE\n", 
	    P[i].cr, P[i].cg,P[i].cb,
	    P[i].x, P[i].y, P[i].r);
  }

  fprintf(eps, "\n");

}  

static void PrintEPSLinks(FILE *eps, Point *P, NODE *node, Int NK) {
  register int i,j;
  int Nn, K;

  Loop(i,NK) {
    K = GetNodeDegree(&node[i]);
    Loop(j,K) {
      Nn = node[i].links[j];
      fprintf(eps, "%f %f %f %f LINK\n",
	     P[i].x,P[i].y, P[Nn].x,P[Nn].y);
    }
  }

}
