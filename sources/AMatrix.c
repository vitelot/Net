/*#define GSL to be commented out if no GSL installed */

#include "main.h"
#include "extern.h"

#ifndef GSL
void AMatrixStuff(NODE * node, Int NK)
{
  if(In.lanczos || !In.amatrix) return;

  printf("Sorry, you do not have the gsl libraries installed.\n");
  printf("You can run the spectral analysis using Lanczos routines only.\n\n");
}
#else


/* Use -lgsl -lgslcblas while linking */
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
/*#include <gsl/gsl_matrix.h>*/

#define  matrix_type In.amatrix

static gsl_matrix * CreateA(NODE * node, Int NK);
static void FreeA(gsl_matrix * A);

void AMatrixStuff(NODE * node, Int NK)
{
 if(In.lanczos || !In.amatrix) return;
{
Int K;
char file[128], eigvalfile[128];
Real *EigenVal = RealVectorAlloc(NK);
gsl_matrix *A = CreateA( node, NK); /* Adjacency matrix */
gsl_vector *eval = gsl_vector_alloc (NK); /* eigenvalues */
gsl_matrix *evec = gsl_matrix_alloc (NK, NK); /*eigenvectors */
gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (NK);


 switch(matrix_type) {
 case 2:
   sprintf(file, "=%s.%s.txt", In.projname, "Spectrum-Laplacian");
   sprintf(eigvalfile, "=%s.%s.dat", In.projname, "EigVals-Laplacian");
   printf("Calculating the Spectrum of the Laplacian matrix.\n Output on files \"%s\" \"%s\".\n\n",file,eigvalfile);
   break;
 case 3:
   sprintf(file, "=%s.%s.txt", In.projname, "Spectrum-Normal");
   sprintf(eigvalfile, "=%s.%s.dat", In.projname, "EigVals-Normal");
   printf("Calculating the Spectrum of the Normal matrix.\n Output on files \"%s\" \"%s\".\n\n",file,eigvalfile) ;
   break;
 default:
   sprintf(file, "=%s.%s.txt", In.projname, "Spectrum-Adjacency");
   sprintf(eigvalfile, "=%s.%s.dat", In.projname, "EigVals-Adjacency");
   printf("Calculating the Spectrum of the Adjacency matrix.\n Output on files \"%s\" \"%s\".\n\n",file,eigvalfile);
 }

   
 gsl_eigen_symmv ( A, eval, evec, w);

 gsl_eigen_symmv_free( w);

 if(matrix_type==2) /* order laplacian's eigvals in ascending order */
   gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_VAL_ASC);
 else
   gsl_eigen_symmv_sort (eval, evec, GSL_EIGEN_SORT_VAL_DESC);

  {
    register int i, j;
    FILE *fp;
    FILE *fp2;

  fp = fopen( file, "w");
  if( !fp)  FileOpenError(file);
  fp2 = fopen( eigvalfile, "w");
  if( !fp2)  FileOpenError(eigvalfile);

    for (i = 0; i < NK; i++)
      {
        double eval_i = gsl_vector_get (eval, i);
	double comp;
/*          gsl_vector_view evec_i = gsl_matrix_column (evec, i); */

        EigenVal[i] = eval_i;
        fprintf (fp2, "%6d %10g\n", i, eval_i);
        fprintf (fp, "EIGENVALUE  = %10g\n", eval_i);
        fprintf (fp, "EIGENVECTOR = \n");
	for(j=0;j<NK;j++) {
	  comp = gsl_matrix_get(evec, j,i);
	  if( fabs(comp)<1e-10 ) comp=0.0;
	  else if( matrix_type==3) { /* to recover the eigvects of D^-1 A */
	    K = GetNodeDegree(&node[j]);
	    if( K!=0) comp /= sqrt(K);
	  }
	  fprintf(fp, "%5d      %+-16g\n", j, comp);
/*          gsl_vector_fprintf (fp, &evec_i.vector, "%16g"); */
	}
      }
  fclose(fp);
  fclose(fp2);
  }

 gsl_vector_free( eval);
 gsl_matrix_free( evec);
 FreeA( A);

 switch(matrix_type) {
 case 2:
   RunXmgrace(NULL, EigenVal, INT, REAL, NK, "Spectrum of the Laplacian [D-A]", "","");
   break;
 case 3:
   RunXmgrace(NULL, EigenVal, INT, REAL, NK, "Spectrum of the Normal matrix [D\\S-1\\N A]", "","");
   break;
 default:
   RunXmgrace(NULL, EigenVal, INT, REAL, NK, "Spectrum of the Adjacency matrix [A]", "","");
 }
 RealVectorFree( EigenVal);
}
}

static gsl_matrix * CreateA(NODE * node, Int NK)
{
register Int i, j;
Int K, K2, *L;
gsl_matrix *A = gsl_matrix_calloc (NK, NK); /* connectivity matrix, initialized to 0 already */

 if(!In.weighted) {
   switch( matrix_type) {
   case 2: /* Laplacian: D-A */
     printf("Building the Laplacian matrix of the graph: D - A\n");
     Loop(i,NK) {
       K = GetNodeDegree( &node[i]);
       L = node[i].links;
       gsl_matrix_set( A, i,i, K);
       Loop(j,K) {
	 K2 = GetNodeDegree( &node[L[j]]);
	 gsl_matrix_set( A, i,L[j], -1.0);
       }
     }
     break;

   case 3: /* Normal: D^(-1/2) A D^(-1/2) */
     /* Eigenvals of case 3 are same of D^(-1)A */
     /* Eigvectors of D^(-1)A are D^(-1/2) times eigvectors of case 3 */
     printf("Building the Normal matrix of the graph: D^(-1/2) A D^(-1/2)\n");
     Loop(i,NK) {
       K = GetNodeDegree( &node[i]);
       L = node[i].links;
       Loop(j,K) {
	 K2 = GetNodeDegree( &node[L[j]]);
	 gsl_matrix_set( A, i,L[j], 1.0/sqrt(K*K2));
       }
     }
     break;    
   default: /* Adjacency matrix: A */
     printf("Building the Adjacency matrix of the graph: A\n");
     Loop(i,NK) {
       K = GetNodeDegree( &node[i]);
       L = node[i].links;
       Loop(j,K) {
	 gsl_matrix_set( A, i,L[j], 1.0);
       }
     }
   }
 } else {
   Real W;
   switch( matrix_type) {
   case 2: /* Laplacian: S-W */
     printf("Building the Weighted Laplacian matrix of the graph: S - W\n");
     Loop(i,NK) {
       K = GetNodeDegree( &node[i]);
       L = node[i].links;
       W = 0.0;
       Loop(j,K) {
	 W += node[i].weights[j]; /* strenght is the sum of link weights */
       }
       gsl_matrix_set( A, i,i, W);
       Loop(j,K) {
	 W = node[i].weights[j];
	 if(i==L[j])  gsl_matrix_set(A,i,i,gsl_matrix_get(A,i,i)-W); /*self loops?*/
	 else gsl_matrix_set( A, i,L[j], -W);
       }
     }
/*      gsl_matrix_fprintf(stdout, A, "%g"); */
     break;

   case 3: /* Normal: D^(-1/2) A D^(-1/2) */
     /* Eigenvals of case 3 are same of D^(-1)A */
     /* Eigvectors of D^(-1)A are D^(-1/2) times eigvectors of case 3 */
     printf("Weighted Normal matrix not yet implemented.\n\n");
     break;
     printf("Building the Normal matrix of the graph: D^(-1/2) A D^(-1/2)\n");
     Loop(i,NK) {
       K = GetNodeDegree( &node[i]);
       L = node[i].links;
       Loop(j,K) {
	 K2 = GetNodeDegree( &node[L[j]]);
	 gsl_matrix_set( A, i,L[j], 1.0/sqrt(K*K2));
       }
     }
     break;    
   default: /* Adjacency matrix: A */
     printf("Building the Weighted Adjacency matrix of the graph: W\n");
     Loop(i,NK) {
       K = GetNodeDegree( &node[i]);
       L = node[i].links;
       Loop(j,K) {
	 W = node[i].weights[j];
	 gsl_matrix_set( A, i,L[j], W);
       }
     }
   }
 }
  
 return A;
}

static void FreeA(gsl_matrix * A)
{ gsl_matrix_free( A); }

#endif /* GSL */
