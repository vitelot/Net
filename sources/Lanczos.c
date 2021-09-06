/*#define LAPACK*/

#include "main.h"
#include "extern.h"

static double GetValue( NODE *ni, NODE *nj)
{
  Int Ki, Kj;

  if(ni!=nj && !AreNeighbors(ni,nj)) return 0.0;

  Ki = GetNodeDegree( ni);
  Kj = GetNodeDegree( nj);
  
  switch(In.amatrix) {
  case 2: /* Laplacian */
    if(ni==nj) return (double)Ki;
    else return -1.0;
    break;
  case 3: /* Normal */
    if( ni!=nj && Ki && Kj)
      return 1.0/sqrt((double)Ki*(double)Kj);
    else return 0.0;
    break;
  default: /* Adjacency */
    if(ni==nj) return 0.0;
    else return 1.0;
  }
}

#ifndef LAPACK

#include <unistd.h>

extern void las1(char *in1, char *in2, char *out1, char *out2);

/*  static double GetValue( NODE *ni, NODE *nj); */
static void CreateLzINI( char ini[128])
{
  FILE *fp;

  fp = fopen( ini, "r");
  if( !fp) {
    printf("Error opening file %s\n", ini);
    printf("Creating a default one. Please edit it. Exit.\n\n");
    
    fp = fopen( ini, "w");
    if( !fp)  FileOpenError(ini);
    fprintf(fp, "NAME LANMAX SINGVALS ENDL      ENDR      AVECT? ACCRCY\n");
    fprintf(fp, "%-4s %6d %8d %8g  %8g  %6s %6g 0 ",
	    In.projname, In.nk/2, 5, -1.0e-30, 1.0e-30, "TRUE", 1.0e-6);
    fclose(fp);
    exit(1);
  }
  fclose(fp);
}

void Lanczos(NODE *node, Int NK)
{
  register long int i,j;
  Int k,Ki, nonconnectednodes=0;
  long *rowind, *pointr;
  double *value;
  long ir,ip,iv;
  short int newcol;
  long nnzero=0, nrow=NK, ncol=NK;
  char lzini[128], mfile[128], eigvalfile[128], eigvectfile[128];
  FILE *o2, *ktmp;

  if(!In.lanczos || !In.amatrix) return;

  printf("Running Lanczos diagonalization routine\n");

  sprintf(mfile, "=%s.%s", In.projname, "HB-Sparse-Matrix");
  sprintf(lzini, "=%s.%s", In.projname, "Lanczos.INI");

  CreateLzINI( lzini);

  ktmp = fopen("Ki.tmp", "w");
  Loop(i,NK) {
    Ki = GetNodeDegree(&node[i]);
    fprintf(ktmp, "%ld %d\n", i,Ki);
    if(Ki==0) nonconnectednodes++;
    nnzero += Ki;
  }
  nnzero += NK; /* only for the laplacian */
  fclose(ktmp);

  if(nonconnectednodes) {
    printf("There are %d isolated nodes in the network.\n", nonconnectednodes);
  }

  pointr = calloc( sizeof(long)  , ncol+1);
  rowind = calloc( sizeof(long)  , nnzero);
  value  = calloc( sizeof(double), nnzero);
  
  /* build Harwell-Boeing sparse matrix format */
  ip=ir=iv=0;
  Loop(j,NK) {
    newcol=1;
    Loop(i,NK) {
      Ki = GetNodeDegree(&node[i]);
      if(i==j ) {
	value[iv++] = GetValue(&node[i], &node[j]); /* 0.0 for isolated nodes */
	rowind[ir++] = i+1;
	if(newcol) {
	  pointr[ip++]=ir;
	  newcol=0;
	  continue;
	}
      }
      Loop(k,Ki) {
	if(j==node[i].links[k]) {
	   value[iv++] = GetValue(&node[i], &node[j]);
	   rowind[ir++] = i+1;
	   if(newcol) {
	     pointr[ip++]=ir;
	     newcol=0;
	   }
	   break;
	}
      }
    }
  }
  pointr[ip++]= nnzero+1;	  

  o2 = fopen( mfile, "w");
  if( !o2)  FileOpenError(mfile);

  fprintf(o2, "%-72s %s\n",In.projname,In.projname);
  fprintf(o2, "#\n");
  fprintf(o2, "%s %ld %ld %ld 0\n",
	  "rsa", nrow, ncol, nnzero);
  fprintf(o2, "(8i6) (8i6) (8f6.2) (8f6.2)\n");

  Loop(i,ip)
    fprintf(o2, "%ld ",pointr[i]);
  fprintf(o2,"\n");

  Loop(i,ir)
    fprintf(o2, "%ld ",rowind[i]);
  fprintf(o2, "\n");

  Loop(i,iv)
    fprintf(o2, "%lf ",value[i]);
  fprintf(o2, "\n");

  free(pointr);
  free(rowind);
  free(value);

  fclose(o2);

 switch(In.amatrix) {
 case 2:
   sprintf(eigvectfile, "=%s.%s", In.projname, "LCZ-Spectrum-Laplacian");
   sprintf(eigvalfile, "=%s.%s.txt", In.projname, "LCZ-EigVals-Laplacian");
   printf("Calculating the Spectrum of the Laplacian matrix.\n Output on files \"%s\" \"%s\".\n\n",eigvectfile,eigvalfile);
   break;
 case 3:
   sprintf(eigvectfile, "=%s.%s", In.projname, "LCZ-Spectrum-Normal");
   sprintf(eigvalfile, "=%s.%s.txt", In.projname, "LCZ-EigVals-Normal");
   printf("Calculating the Spectrum of the Normal matrix.\n Output on files \"%s\" \"%s\".\n\n",eigvectfile,eigvalfile) ;
   break;
 default:
   sprintf(eigvectfile, "=%s.%s", In.projname, "LCZ-Spectrum-Adjacency");
   sprintf(eigvalfile, "=%s.%s.txt", In.projname, "LCZ-EigVals-Adjacency");
   printf("Calculating the Spectrum of the Adjacency matrix.\n Output on files \"%s\" \"%s\".\n\n",eigvectfile,eigvalfile);
 }

  las1( lzini, mfile, eigvalfile, eigvectfile);
  printf("\n");

  sleep(1);
  remove("Ki.tmp");
}

#else /* LAPACK defined */

#define Diag sspevx_

static void CreateLzINI( char ini[128])
{
  FILE *fp;

  fp = fopen( ini, "r");
  if( !fp) {
    printf("Error opening file %s\n", ini);
    printf("Creating a default one. Please edit it. Exit.\n\n");
    
    fp = fopen( ini, "w");
    if( !fp)  FileOpenError(ini);
    fprintf(fp, "%8s %5s %5s %6s %8s\n",
	    "NAME","IL","IU","AVECT?","ABSTOL");
    fprintf(fp, "%-8s %5d %5d %6s %8g\n",
	    In.projname, 1, In.nk/10, "TRUE", 1e-6);
    fclose(fp);
    exit(1);
  }
  fclose(fp);
}

extern void Diag( char *JOBZ, char *RANGE, char *UPLO, 
		  int *N, float *AP, 
		  float *VL, float *VU, int *IL, int *IU,
		  float *ABSTOL, 
		  int *M, float *W, float *Z, int *LDZ,
		  float *WORK, int *IWORK, 
		  int *IFAIL, int *INFO );

void Lanczos(NODE *node, Int NK)
{
  if(!In.lanczos || !In.amatrix) return;
{
  /* input params */
  char  jobz = 'N';
  char  range= 'I';
  char  uplo = 'U';
  int   n=NK;
  float *ap;
  float vl=0;
  float vu=0;
  int   il=1;
  int   iu=4; /* 1 <= IL <= IU <= N, if N > 0; IL = 1 and IU = 0 if N = 0 */
  float abstol=1e-6;
  int   ldz=n;

  /* output params */
  int   m;
  float *w = calloc(sizeof(float), 1+n);
  float *z;
  int   *ifail = calloc(sizeof(int), n+1);
  int   info;
  
  /* workspace */
  float *work  = calloc(sizeof(float), 8*n+1);
  int   *iwork = calloc(sizeof(  int), 5*n+1);
  /*********************************************/

  register int i,j;
  char lzini[128], eigvalfile[128], eigvectfile[128], line[256], v[6];
  FILE *fin, *fout;

  printf("Going to calculate partial spectrum using SSPEVX lapack routine\n");

  sprintf(lzini, "=%s.%s", In.projname, "Lapack.INI");

  CreateLzINI( lzini);

  switch(In.amatrix) {
  case 2:
    sprintf(eigvectfile, "=%s.%s.txt", In.projname, "Lapack-Spectrum-Laplacian");
    sprintf(eigvalfile, "=%s.%s.dat", In.projname, "Lapack-EigVals-Laplacian");
    printf("Calculating the Spectrum of the Laplacian matrix.\n Output on files \"%s\" \"%s\".\n\n",eigvectfile,eigvalfile);
    break;
  case 3:
    sprintf(eigvectfile, "=%s.%s.txt", In.projname, "Lapack-Spectrum-Normal");
    sprintf(eigvalfile, "=%s.%s.dat", In.projname, "Lapack-EigVals-Normal");
    printf("Calculating the Spectrum of the Normal matrix.\n Output on files \"%s\" \"%s\".\n\n",eigvectfile,eigvalfile) ;
    break;
  default:
    sprintf(eigvectfile, "=%s.%s.txt", In.projname, "Lapack-Spectrum-Adjacency");
    sprintf(eigvalfile, "=%s.%s.dat", In.projname, "Lapack-EigVals-Adjacency");
    printf("Calculating the Spectrum of the Adjacency matrix.\n Output on files \"%s\" \"%s\".\n\n",eigvectfile,eigvalfile);
  }

  if (!(fin = fopen(lzini, "r"))) { 
       printf("cannot open file %s for reading\n", lzini);
       exit(-1);
    }

  fgets( line, 255, fin); /* skip first line of comment */
  fscanf (fin,"%*s %d %d %s %f ", &il,&iu, v, &abstol);

  fclose(fin);

  if (!(strcmp(v, "TRUE"))) jobz = 'V';

  z = calloc(sizeof(float), ldz*(iu-il+1));
  ap = calloc(sizeof(float), 1+(n*(n+1))/2);

  Loop(j,NK) { /* column index */
    for(i=0; i<=j; i++) {
      ap[i+(j*(j+1))/2] = GetValue(&node[i], &node[j]);
    }
  }

  Diag(&jobz, &range, &uplo, 
       &n, ap, 
       &vl, &vu, &il, &iu,
       &abstol, 
       &m, w, z, &ldz, 
       work, iwork, 
       ifail, &info);

  if(info>=0) {
    Int K;
    float comp;

    printf("SSPEVX routine returned without errors\n");
    
    if (!(fout = fopen(eigvalfile, "w"))) { 
      printf("cannot open output file %s \n", eigvalfile);
      exit(-1);
    }

    Loop(i,m)
      fprintf(fout, "%6d  %16f\n", i,w[i]);
    
    fclose(fout);

    if(jobz=='V') {
      if(info>0) {
	printf("BUT %d EIGENVECTORS DID NOT CONVERGE. Look at file IFAIL.\n",info);
	if (!(fout = fopen("IFAIL", "w"))) { 
	  printf("cannot open output file %s \n", "IFAIL");
	  exit(-1);
	}
	fprintf(fout, "Index of non converged eigenvectors\n");
	Loop(i,n)
	  fprintf(fout, "%6d\n", ifail[i]);
	fclose(fout);
      }
    
      if (!(fout = fopen(eigvectfile, "w"))) { 
	printf("cannot open output file %s \n", eigvectfile);
	exit(-1);
      }
    
      Loop(i,m) {
	fprintf (fout, "EIGENVALUE  = %10g\n", w[i]);
	fprintf (fout, "EIGENVECTOR = \n");
	for(j=0;j<n;j++) {
	  comp = z[j+n*i];
	  if( fabs(comp)<1e-10 ) comp=0.0;
	  else if( In.amatrix==3) { /* to recover the eigvects of D^-1 A */
	    K = GetNodeDegree(&node[j]);
	    if( K!=0) comp /= sqrt(K);
	  }
	  fprintf(fout, "%5d      %+-16g\n", j, comp);
	}
      }
      fclose(fout);
    }
    
  }
}
}
#undef Diag

#endif /* LAPACK */

/*   SSPEVX usage:
*     ..
*
*  Purpose
*  =======
*
*  SSPEVX computes selected eigenvalues and, optionally, eigenvectors
*  of a real symmetric matrix A in packed storage.  Eigenvalues/vectors
*  can be selected by specifying either a range of values or a range of
*  indices for the desired eigenvalues.
*
*  Arguments
*  =========
*
*  JOBZ    (input) CHARACTER*1
*          = 'N':  Compute eigenvalues only;
*          = 'V':  Compute eigenvalues and eigenvectors.
*
*  RANGE   (input) CHARACTER*1
*          = 'A': all eigenvalues will be found;
*          = 'V': all eigenvalues in the half-open interval (VL,VU]
*                 will be found;
*          = 'I': the IL-th through IU-th eigenvalues will be found.
*
*  UPLO    (input) CHARACTER*1
*          = 'U':  Upper triangle of A is stored;
*          = 'L':  Lower triangle of A is stored.
*
*  N       (input) INTEGER
*          The order of the matrix A.  N >= 0.
*
*  AP      (input/output) REAL array, dimension (N*(N+1)/2)
*          On entry, the upper or lower triangle of the symmetric matrix
*          A, packed columnwise in a linear array.  The j-th column of A
*          is stored in the array AP as follows:
*          if UPLO = 'U', AP(i + (j-1)*j/2) = A(i,j) for 1<=i<=j;
*          if UPLO = 'L', AP(i + (j-1)*(2*n-j)/2) = A(i,j) for j<=i<=n.
*
*          On exit, AP is overwritten by values generated during the
*          reduction to tridiagonal form.  If UPLO = 'U', the diagonal
*          and first superdiagonal of the tridiagonal matrix T overwrite
*          the corresponding elements of A, and if UPLO = 'L', the
*          diagonal and first subdiagonal of T overwrite the
*          corresponding elements of A.
*
*  VL      (input) REAL
*  VU      (input) REAL
*          If RANGE='V', the lower and upper bounds of the interval to
*          be searched for eigenvalues. VL < VU.
*          Not referenced if RANGE = 'A' or 'I'.
*
*  IL      (input) INTEGER
*  IU      (input) INTEGER
*          If RANGE='I', the indices (in ascending order) of the
*          smallest and largest eigenvalues to be returned.
*          1 <= IL <= IU <= N, if N > 0; IL = 1 and IU = 0 if N = 0.
*          Not referenced if RANGE = 'A' or 'V'.
*
*  ABSTOL  (input) REAL
*          The absolute error tolerance for the eigenvalues.
*          An approximate eigenvalue is accepted as converged
*          when it is determined to lie in an interval [a,b]
*          of width less than or equal to
*
*                  ABSTOL + EPS *   max( |a|,|b| ) ,
*
*          where EPS is the machine precision.  If ABSTOL is less than
*          or equal to zero, then  EPS*|T|  will be used in its place,
*          where |T| is the 1-norm of the tridiagonal matrix obtained
*          by reducing AP to tridiagonal form.
*
*          Eigenvalues will be computed most accurately when ABSTOL is
*          set to twice the underflow threshold 2*SLAMCH('S'), not zero.
*          If this routine returns with INFO>0, indicating that some
*          eigenvectors did not converge, try setting ABSTOL to
*          2*SLAMCH('S').
*
*          See "Computing Small Singular Values of Bidiagonal Matrices
*          with Guaranteed High Relative Accuracy," by Demmel and
*          Kahan, LAPACK Working Note #3.
*
*  M       (output) INTEGER
*          The total number of eigenvalues found.  0 <= M <= N.
*          If RANGE = 'A', M = N, and if RANGE = 'I', M = IU-IL+1.
*
*  W       (output) REAL array, dimension (N)
*          If INFO = 0, the selected eigenvalues in ascending order.
*
*  Z       (output) REAL array, dimension (LDZ, max(1,M))
*          If JOBZ = 'V', then if INFO = 0, the first M columns of Z
*          contain the orthonormal eigenvectors of the matrix A
*          corresponding to the selected eigenvalues, with the i-th
*          column of Z holding the eigenvector associated with W(i).
*          If an eigenvector fails to converge, then that column of Z
*          contains the latest approximation to the eigenvector, and the
*          index of the eigenvector is returned in IFAIL.
*          If JOBZ = 'N', then Z is not referenced.
*          Note: the user must ensure that at least max(1,M) columns are
*          supplied in the array Z; if RANGE = 'V', the exact value of M
*          is not known in advance and an upper bound must be used.
*
*  LDZ     (input) INTEGER
*          The leading dimension of the array Z.  LDZ >= 1, and if
*          JOBZ = 'V', LDZ >= max(1,N).
*
*  WORK    (workspace) REAL array, dimension (8*N)
*
*  IWORK   (workspace) INTEGER array, dimension (5*N)
*
*  IFAIL   (output) INTEGER array, dimension (N)
*          If JOBZ = 'V', then if INFO = 0, the first M elements of
*          IFAIL are zero.  If INFO > 0, then IFAIL contains the
*          indices of the eigenvectors that failed to converge.
*          If JOBZ = 'N', then IFAIL is not referenced.
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*          > 0:  if INFO = i, then i eigenvectors failed to converge.
*                Their indices are stored in array IFAIL.
*
*  =====================================================================
*/
