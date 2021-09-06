#include "main.h"
#include "extern.h"

static void StatDegree(Int NK);
static void StatNeighConnect(Int NK);
static void StatClusterCoeff(Int NK);
static void StatClusterCoeff2NN(Int NK);
static void StatClusterCoeff2NNstar(Int NK);
static void StatSiteBetweenness(Int NK);
static void StatClusterSize(Int NK);
static void StatSCCSize(Int NK);

static Real sqm;

void MultiStatistics(Int NK)
{
  sqm = sqrt(In.multi);

  printf("Beginning STATS for %d runs\n", In.multi);
  StatDegree( NK);
  StatNeighConnect( NK);
  StatClusterCoeff( NK);
  StatClusterCoeff2NN( NK);
  StatClusterCoeff2NNstar( NK);
  StatSiteBetweenness( NK);
  StatClusterSize( NK);
  StatSCCSize( NK);
}

static void StatDegree(Int NK)
{
 if(!In.degdistr) return;
 if(In.nettype==0) {/* undirected */
   if(!In.weighted)
     {
       register int i, n;
       Real *Pk, *Ki, *Pk2, *Ki2;
       Int pkcur, kicur;
       char line[128];
       char file[128];
       FILE *in;
       FILE *out;

       Pk  = RealVectorAlloc(NK);
       Ki  = RealVectorAlloc(NK);
       Pk2 = RealVectorAlloc(NK);
       Ki2 = RealVectorAlloc(NK);

       RealVectorInit(Pk, NK, 0.0);
       RealVectorInit(Ki, NK, 0.0);
       RealVectorInit(Pk2,NK, 0.0);
       RealVectorInit(Ki2,NK, 0.0);

       printf("Building statistics for Degree Distribution\n");

       for(i=0; i<In.multi; i++) {
	 sprintf(file, "=%s%04d.DegreeDistribution.dat", In.projname, i);
	 in = fopen( file,"r");
	 if(!in) FileOpenError(file);

	 Dots('.', i, 1+(In.multi>>6));

	 fgets(line, 128, in); /* skip the initial comment */
	 for(n=0; n<NK; n++) {
	   fscanf(in, "%*d %d %*g %d %*g", &pkcur, &kicur);

	   Pk[n] += (Real) pkcur;
	   Pk2[n] += ((Real) pkcur)*pkcur;

	   Ki[n] += (Real) kicur;
	   Ki2[n] += ((Real) kicur)*kicur;
	 }
	 fclose(in);
       }
  
       printf("\n");
  
       sprintf(file, "=%s_STATS.DegreeDistribution.dat", In.projname);
       out = fopen( file,"w");
       if(!out) FileOpenError(file);
  
       fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	       "K,i", "P(K)", "E[P(K)]", "K(i)", "E[K(i)]");

       for(n=0; n<NK; n++) {
	 Pk [n] /= (Real) In.multi;
	 Ki [n] /= (Real) In.multi;
	 Pk2[n] /= (Real) In.multi;
	 Ki2[n] /= (Real) In.multi;
	 fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
		 n,
		 Pk[n], sqrt(Pk2[n]-Pk[n]*Pk[n])/sqm,
		 Ki[n], sqrt(Ki2[n]-Ki[n]*Ki[n])/sqm);
       }
       fclose(out);

       sprintf(line, "MultiStat P(k) [%d runs]", In.multi);
       RunXmgrace(NULL, Pk, INT,REAL, NK, line, "","");

       RealVectorFree(Pk );
       RealVectorFree(Ki );
       RealVectorFree(Pk2);
       RealVectorFree(Ki2);
     } else { /* weighted */

     register int i, k;
     Real *Wk;
     double wkcur;
     Int *Count;
     char line[128];
     char file[128];
     FILE *in;
     FILE *out;

     Wk  = RealVectorAlloc(NK);
     Count = IntVectorAlloc(NK);

     RealVectorInit(Wk,    NK, 0.0);
     IntVectorInit(Count, NK,   0);
  
     printf("Building statistics for Weighted Degree Distribution (Strenght)\n");

     for(i=0; i<In.multi; i++) {
       sprintf(file, "=%s%04d.WDegreeDistribution.dat", In.projname, i);
       in = fopen( file,"r");
       if(!in) FileOpenError(file);
       Dots('.', i, 1+(In.multi>>6));
       fgets(line, 128, in); /* skip the initial comment */
       for(k=0; k<NK; k++) {
	 fscanf(in, "%*d %lg %*g %*g %*g %*g", &wkcur);
	 if(wkcur!=0.0) {
	   Wk[k] += wkcur;
	   Count[k]++;
	 }
       }
       fclose(in);
     }

     printf("\n");

     sprintf(file, "=%s_STATS.WDegreeDistribution.dat", In.projname);
     out = fopen( file,"w");
     if(!out) FileOpenError(file);

     fprintf(out, "#%5s\t%10s\n",
	     "K", "s(K)");

     for(k=0; k<NK; k++) {
       if(Count[k]) {
	 Wk[k] /= (Real) Count[k];
	 fprintf(out, "%6d\t%10g\n",
		 k, Wk[k]);
       }
     }
     fclose(out);

     sprintf(line, "MultiStat S(k) [%d runs]", In.multi);
     RunXmgrace(NULL, Wk, INT,REAL, NK, line, "k","s");

     RealVectorFree(Wk );
     IntVectorFree(Count );

   }
 } else { /* directed */
       register int i, n;
       Real *Pk, *Ki, *Pk2, *Ki2;
       Int pkcur, kicur;
       char line[128];
       char file[128];
       FILE *in;
       FILE *out;

       Pk  = RealVectorAlloc(NK);
       Ki  = RealVectorAlloc(NK);
       Pk2 = RealVectorAlloc(NK);
       Ki2 = RealVectorAlloc(NK);

       /****************************************************/
       /* let's start with Kout statistics */
       RealVectorInit(Pk, NK, 0.0);
       RealVectorInit(Ki, NK, 0.0);
       RealVectorInit(Pk2,NK, 0.0);
       RealVectorInit(Ki2,NK, 0.0);

       printf("Building statistics for Out-Degree Distribution\n");

       for(i=0; i<In.multi; i++) {
	 sprintf(file, "=%s%04d.OutDegreeDistribution.dat", In.projname, i);
	 in = fopen( file,"r");
	 if(!in) FileOpenError(file);

	 Dots('.', i, 1+(In.multi>>6));

	 fgets(line, 128, in); /* skip the initial comment */
	 for(n=0; n<NK; n++) {
	   fscanf(in, "%*d %d %d %*g", &pkcur, &kicur);

	   Pk[n] += (Real) pkcur;
	   Pk2[n] += ((Real) pkcur)*pkcur;

	   Ki[n] += (Real) kicur;
	   Ki2[n] += ((Real) kicur)*kicur;
	 }
	 fclose(in);
       }
  
       printf("\n");
  
       sprintf(file, "=%s_STATS.OutDegreeDistribution.dat", In.projname);
       out = fopen( file,"w");
       if(!out) FileOpenError(file);
  
       fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	       "Kout,i", "P(Kout)", "E[P(Kout)]", "Kout(i)", "E[Kout(i)]");

       for(n=0; n<NK; n++) {
	 Pk [n] /= (Real) In.multi;
	 Ki [n] /= (Real) In.multi;
	 Pk2[n] /= (Real) In.multi;
	 Ki2[n] /= (Real) In.multi;
	 fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
		 n,
		 Pk[n], sqrt(Pk2[n]-Pk[n]*Pk[n])/sqm,
		 Ki[n], sqrt(Ki2[n]-Ki[n]*Ki[n])/sqm);
       }
       fclose(out);

       sprintf(line, "MultiStat P(k\\sout\\N) [%d runs]", In.multi);
       RunXmgrace(NULL, Pk, INT,REAL, NK, line, "","");

       /****************************************************/
       /* and now with Kin statistics */
       RealVectorInit(Pk, NK, 0.0);
       RealVectorInit(Ki, NK, 0.0);
       RealVectorInit(Pk2,NK, 0.0);
       RealVectorInit(Ki2,NK, 0.0);

       printf("Building statistics for In-Degree Distribution\n");

       for(i=0; i<In.multi; i++) {
	 sprintf(file, "=%s%04d.InDegreeDistribution.dat", In.projname, i);
	 in = fopen( file,"r");
	 if(!in) FileOpenError(file);

	 Dots('.', i, 1+(In.multi>>6));

	 fgets(line, 128, in); /* skip the initial comment */
	 for(n=0; n<NK; n++) {
	   fscanf(in, "%*d %d %d %*d %*g", &pkcur, &kicur);

	   Pk[n] += (Real) pkcur;
	   Pk2[n] += ((Real) pkcur)*pkcur;

	   Ki[n] += (Real) kicur;
	   Ki2[n] += ((Real) kicur)*kicur;
	 }
	 fclose(in);
       }
  
       printf("\n");
  
       sprintf(file, "=%s_STATS.InDegreeDistribution.dat", In.projname);
       out = fopen( file,"w");
       if(!out) FileOpenError(file);
  
       fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	       "Kin,i", "P(Kin)", "E[P(Kin)]", "Kin(i)", "E[Kin(i)]");

       for(n=0; n<NK; n++) {
	 Pk [n] /= (Real) In.multi;
	 Ki [n] /= (Real) In.multi;
	 Pk2[n] /= (Real) In.multi;
	 Ki2[n] /= (Real) In.multi;
	 fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
		 n,
		 Pk[n], sqrt(Pk2[n]-Pk[n]*Pk[n])/sqm,
		 Ki[n], sqrt(Ki2[n]-Ki[n]*Ki[n])/sqm);
       }
       fclose(out);

       sprintf(line, "MultiStat P(k\\sin\\N) [%d runs]", In.multi);
       RunXmgrace(NULL, Pk, INT,REAL, NK, line, "","");

       RealVectorFree(Pk );
       RealVectorFree(Ki );
       RealVectorFree(Pk2);
       RealVectorFree(Ki2);

 }
}

static void StatNeighConnect(Int NK)
{
  register int i, n;
  Real *Knnk, *Knni, *Knnk2, *Knni2;
  Int *Count;
  double knnkcur, knnicur;
  char line[128];
  char file[128];
  FILE *in;
  FILE *out;

  if(!In.knn) return;

  Knnk = RealVectorAlloc( NK);
  Knni = RealVectorAlloc( NK);
  Knnk2= RealVectorAlloc( NK);
  Knni2= RealVectorAlloc( NK);
  Count = IntVectorAlloc( NK);

  IntVectorInit(Count, NK, 0);
  RealVectorInit(Knnk, NK, 0.0);
  RealVectorInit(Knni, NK, 0.0);
  RealVectorInit(Knnk2,NK, 0.0);
  RealVectorInit(Knni2,NK, 0.0);

  printf("Building statistics for the Nearest Neighbour Connectivity\n");

  for(i=0; i<In.multi; i++) {
    sprintf(file, "=%s%04d.NeighbourConnectivity.dat", In.projname, i);
    in = fopen( file,"r");
    if(!in) FileOpenError(file);

    Dots('.', i, 1+(In.multi>>6));

    fgets(line, 128, in); /* skip the initial comment */
    for(n=0; n<NK; n++) {
      fgets(line, 128, in);
      sscanf(line, "%*d %lg %*g %lg %*g", &knnkcur, &knnicur);

      if(knnkcur > 1e-6) {
	Knnk [n] += knnkcur;
	Knnk2[n] += knnkcur*knnkcur;
	Count[n]++;
      }

      Knni [n] += knnicur;
      Knni2[n] += knnicur*knnicur;
    }
    fclose(in);
  }
  printf("\n");
  
  sprintf(file, "=%s_STATS.NeighbourConnectivity.dat", In.projname);
  out = fopen( file,"w");
  if(!out) FileOpenError(file);
  
  fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	  "k,i", "Knn(k)", "E[Knn(k)]", "Knn(i)", "E[Knn(i)]");

  for(n=0; n<NK; n++) {
    if(Count[n]>0) {
      Knnk [n] /= (Real) Count[n];
      Knnk2[n] /= (Real) Count[n];
    }
    Knni [n] /= (Real) In.multi;
    Knni2[n] /= (Real) In.multi;
    fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
	    n, Knnk[n], (Count[n]>0)?sqrt(Knnk2[n]-Knnk[n]*Knnk[n])/sqrt(Count[n]):0.0,
	       Knni[n], sqrt(Knni2[n]-Knni[n]*Knni[n])/sqm);
  }
  fclose(out);

  RunXmgrace(NULL, Knnk, INT,REAL, NK,"MultiStat K\\snn\\N(k)","k","nearest neighbor connectivity");


  IntVectorFree(Count);
  RealVectorFree(Knnk );
  RealVectorFree(Knni );
  RealVectorFree(Knnk2);
  RealVectorFree(Knni2);
}

static void StatClusterCoeff(Int NK)
{
  register int i, n;
  Int *Count;
  Real *CCk, *CCi, *CCk2, *CCi2;
  double cckcur, ccicur;
  char line[128];
  char file[128];
  FILE *in;
  FILE *out;

  if(!In.clcoeff) return;

  printf("Building statistics for Cluster Coefficient\n");

  Count = IntVectorAlloc( NK);
  CCk = RealVectorAlloc( NK);
  CCi = RealVectorAlloc( NK);
  CCk2= RealVectorAlloc( NK);
  CCi2= RealVectorAlloc( NK);

  IntVectorInit(Count, NK, 0);
  RealVectorInit(CCk, NK, 0.0);
  RealVectorInit(CCi, NK, 0.0);
  RealVectorInit(CCk2,NK, 0.0);
  RealVectorInit(CCi2,NK, 0.0);

  for(i=0; i<In.multi; i++) {
    sprintf(file, "=%s%04d.ClusterCoefficient.dat", In.projname, i);
    in = fopen( file,"r");
    if(!in) FileOpenError(file);
/*      printf("Reading file %s\n", file); */
    Dots('.', i, 1+(In.multi>>6));
    fgets(line, 128, in); /* skip the initial comment */
    for(n=0; n<NK; n++) {
      fgets(line, 128, in);
      sscanf(line, "%*d %lg %lg %*g", &cckcur, &ccicur);

      if(cckcur > 1e-6) {
	CCk [n] += cckcur;
	CCk2[n] += cckcur*cckcur;
	Count[n]++;
      }

      CCi [n] += ccicur;
      CCi2[n] += ccicur*ccicur;
    }
    fclose(in);
  }
  printf("\n");

  sprintf(file, "=%s_STATS.ClusterCoefficient.dat", In.projname);
  out = fopen( file,"w");
  if(!out) FileOpenError(file);
  
  fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	  "k,i", "CC(k)", "E[CC(k)]", "CC(i)", "E[CC(i)]");

  for(n=0; n<NK; n++) {
    if(Count[n]>0) {
      CCk [n] /= (Real) Count[n];
      CCk2[n] /= (Real) Count[n];
    }

    CCi [n] /= (Real) In.multi;
    CCi2[n] /= (Real) In.multi;
    fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
	    n, CCk[n], (Count[n]>0)?sqrt(CCk2[n]-CCk[n]*CCk[n])/sqrt(Count[n]):0.0,
	       CCi[n], sqrt(CCi2[n]-CCi[n]*CCi[n])/sqm);
  }
  fclose(out);

  RunXmgrace(NULL, CCk, INT,REAL, NK,"MultiStat C(k)","","");

  IntVectorFree(Count);
  RealVectorFree(CCk );
  RealVectorFree(CCi );
  RealVectorFree(CCk2);
  RealVectorFree(CCi2);
}

static void StatClusterCoeff2NN(Int NK)
{
  register int i, n;
  Real *CCk, *CCi, *CCk2, *CCi2;
  double cckcur, ccicur;
  char line[128];
  char file[128];
  FILE *in;
  FILE *out;

  if(!In.cl2coeff) return;

  printf("Building statistics for Cluster Coefficient2\n");

  CCk = RealVectorAlloc( NK);
  CCi = RealVectorAlloc( NK);
  CCk2= RealVectorAlloc( NK);
  CCi2= RealVectorAlloc( NK);

  RealVectorInit(CCk, NK, 0.0);
  RealVectorInit(CCi, NK, 0.0);
  RealVectorInit(CCk2,NK, 0.0);
  RealVectorInit(CCi2,NK, 0.0);

  for(i=0; i<In.multi; i++) {
    sprintf(file, "=%s%04d.ClusterCoefficient2NN.dat", In.projname, i);
    in = fopen( file,"r");
    if(!in) FileOpenError(file);
/*      printf("Reading file %s\n", file); */
    Dots('.', i, 1+(In.multi>>6));
    fgets(line, 128, in); /* skip the initial comment */
    for(n=0; n<NK; n++) {
      fscanf(in, "%*d %lg %lg %*g %*d %*d", &cckcur, &ccicur);
/*        printf("%d %g %g\n", n,cckcur,ccicur); */
      CCk [n] += cckcur;
      CCi [n] += ccicur;
      CCk2[n] += cckcur*cckcur;
      CCi2[n] += ccicur*ccicur;
    }
    fclose(in);
  }
  printf("\n");

  sprintf(file, "=%s_STATS.ClusterCoefficient2NN.dat", In.projname);
  out = fopen( file,"w");
  if(!out) FileOpenError(file);
  
  fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	  "k,i", "CC2(k)", "E[CC2(k)]", "CC2(i)", "E[CC2(i)]");

  for(n=0; n<NK; n++) {
    CCk [n] /= (Real) In.multi;
    CCi [n] /= (Real) In.multi;
    CCk2[n] /= (Real) In.multi;
    CCi2[n] /= (Real) In.multi;
    fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
	    n, CCk[n], sqrt(CCk2[n]-CCk[n]*CCk[n])/sqm,
	       CCi[n], sqrt(CCi2[n]-CCi[n]*CCi[n])/sqm);
  }
  fclose(out);

  RunXmgrace(NULL, CCk, INT,REAL, NK,"MultiStat C\\s2\\N(k)","","");

  RealVectorFree(CCk );
  RealVectorFree(CCi );
  RealVectorFree(CCk2);
  RealVectorFree(CCi2);
}

static void StatClusterCoeff2NNstar(Int NK)
{
  register int i, n;
  Real *CCk, *CCi, *CCk2, *CCi2;
  double cckcur, ccicur;
  char line[128];
  char file[128];
  FILE *in;
  FILE *out;

  if(!In.cl2coeff) return;

  printf("Building statistics for Cluster Coefficient2star\n");

  CCk = RealVectorAlloc( NK);
  CCi = RealVectorAlloc( NK);
  CCk2= RealVectorAlloc( NK);
  CCi2= RealVectorAlloc( NK);

  RealVectorInit(CCk, NK, 0.0);
  RealVectorInit(CCi, NK, 0.0);
  RealVectorInit(CCk2,NK, 0.0);
  RealVectorInit(CCi2,NK, 0.0);

  for(i=0; i<In.multi; i++) {
    sprintf(file, "=%s%04d.ClusterCoefficient2NNs.dat", In.projname, i);
    in = fopen( file,"r");
    if(!in) FileOpenError(file);
/*      printf("Reading file %s\n", file); */
    Dots('.', i, 1+(In.multi>>6));
    fgets(line, 128, in); /* skip the initial comment */
    for(n=0; n<NK; n++) {
      fscanf(in, "%*d %lg %lg %*g %*d %*d", &cckcur, &ccicur);
/*        printf("%d %g %g\n", n,cckcur,ccicur); */
      CCk [n] += cckcur;
      CCi [n] += ccicur;
      CCk2[n] += cckcur*cckcur;
      CCi2[n] += ccicur*ccicur;
    }
    fclose(in);
  }
  printf("\n");

  sprintf(file, "=%s_STATS.ClusterCoefficient2NNs.dat", In.projname);
  out = fopen( file,"w");
  if(!out) FileOpenError(file);
  
  fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	  "k,i", "CC2s(k)", "E[CC2s(k)]", "CC2s(i)", "E[CC2s(i)]");

  for(n=0; n<NK; n++) {
    CCk [n] /= (Real) In.multi;
    CCi [n] /= (Real) In.multi;
    CCk2[n] /= (Real) In.multi;
    CCi2[n] /= (Real) In.multi;
    fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
	    n, CCk[n], sqrt(CCk2[n]-CCk[n]*CCk[n])/sqm,
	       CCi[n], sqrt(CCi2[n]-CCi[n]*CCi[n])/sqm);
  }
  fclose(out);

  RunXmgrace(NULL, CCk, INT, REAL, NK,"MultiStat C\\s2\\N\\S*\\N(k)","","");

  RealVectorFree(CCk );
  RealVectorFree(CCi );
  RealVectorFree(CCk2);
  RealVectorFree(CCi2);
}

static void StatSiteBetweenness(Int NK)
{
  register int i, n;
  Real *BCk, *BCi, *BCk2, *BCi2;
  Int *Count;
  double bckcur, bcicur;
  char line[128];
  char file[128];
  FILE *in;
  FILE *out;

  if(!In.sitebetw) return;

  printf("Building statistics for Site Betweenness\n");

  BCk = RealVectorAlloc( NK);
  BCi = RealVectorAlloc( NK);
  BCk2= RealVectorAlloc( NK);
  BCi2= RealVectorAlloc( NK);
  Count = IntVectorAlloc( NK);

  IntVectorInit(Count, NK, 0);
  RealVectorInit(BCk, NK, 0.0);
  RealVectorInit(BCi, NK, 0.0);
  RealVectorInit(BCk2,NK, 0.0);
  RealVectorInit(BCi2,NK, 0.0);

  for(i=0; i<In.multi; i++) {
    sprintf(file, "=%s%04d.SiteBetweenness.dat", In.projname, i);
    in = fopen( file,"r");
    if(!in) FileOpenError(file);
/*      printf("Reading file %s\n", file); */
    Dots('.', i, 1+(In.multi>>6));
    fgets(line, 128, in); /* skip the initial comment */
    for(n=0; n<NK; n++) {
      fscanf(in, "%*d %lg %lg %*g %*g", &bckcur, &bcicur);
/*        printf("%d %g %g\n", n,bckcur,bcicur); */
      if(bckcur > 1e-6) {      
	BCk [n] += bckcur;
	BCk2[n] += bckcur*bckcur;
	Count[n]++;
      }

      BCi [n] += bcicur;
      BCi2[n] += bcicur*bcicur;
    }
    fclose(in);
  }
  printf("\n");

  sprintf(file, "=%s_STATS.SiteBetweenness.dat", In.projname);
  out = fopen( file,"w");
  if(!out) FileOpenError(file);
  
  fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	  "k,i", "BC(k)", "E[BC(k)]", "BC(i)", "E[BC(i)]");

  for(n=0; n<NK; n++) {
    if(Count[n]>0) {
      BCk [n] /= (Real) Count[n];
      BCk2[n] /= (Real) Count[n];
/*       tmp = sqrt((BCk2[n]-BCk[n]*BCk[n])/Count[n]); */
/*       printf("##### %f\n",tmp); */
    }
    BCi [n] /= (Real) In.multi;
    BCi2[n] /= (Real) In.multi;


    fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
	    n, BCk[n], (Count[n]>1)?sqrt((BCk2[n]-BCk[n]*BCk[n])/Count[n]):0.0,
	       BCi[n], sqrt(BCi2[n]-BCi[n]*BCi[n])/sqm);
  }
  fclose(out);

  RunXmgrace(NULL, BCk, INT,REAL, NK,"MultiStat B\\ssite\\N(k)","","");

  IntVectorFree(Count);
  RealVectorFree(BCk );
  RealVectorFree(BCi );
  RealVectorFree(BCk2);
  RealVectorFree(BCi2);
}

static void StatClusterSize(Int NK)
{
  register int i, n;
  Real *CS, *Pcs, *CS2, *Pcs2;
  Int cscur, pcscur;
  char line[128];
  char file[128];
  FILE *in;
  FILE *out;

  if(!In.printcluster) return;

  CS  = RealVectorAlloc(NK);
  Pcs  = RealVectorAlloc(NK);
  CS2 = RealVectorAlloc(NK);
  Pcs2 = RealVectorAlloc(NK);

  RealVectorInit(CS, NK, 0.0);
  RealVectorInit(Pcs, NK, 0.0);
  RealVectorInit(CS2,NK, 0.0);
  RealVectorInit(Pcs2,NK, 0.0);

  printf("Building statistics for Cluster Size\n");

  for(i=0; i<In.multi; i++) {
    sprintf(file, "=%s%04d.ClusterSize.dat", In.projname, i);
    in = fopen( file,"r");
    if(!in) FileOpenError(file);
/*      printf("Reading file %s\n", file); */
    Dots('.', i, 1+(In.multi>>6));
    fgets(line, 128, in); /* skip the initial comment */
    for(n=0; n<NK; n++) {
      fscanf(in, "%*d %d %d", &cscur, &pcscur);
/*        printf("%d %d %d\n", n,cscur,pcscur); */
      CS[n] += (Real) cscur;
      Pcs[n] += (Real) pcscur;
      CS2[n] += ((Real) cscur)*cscur;
      Pcs2[n] += ((Real) pcscur)*pcscur;
    }
    fclose(in);
  }
  
  printf("\n");
  
  sprintf(file, "=%s_STATS.ClusterSize.dat", In.projname);
  out = fopen( file,"w");
  if(!out) FileOpenError(file);
  
  fprintf(out, "#%5s\t%10s\t%10s\t%10s\t%10s\n",
	  "i,CS", "CS(i)", "E[CS(i)]", "P(CS)", "E[P(CS)]");

  for(n=0; n<NK; n++) {
    CS [n] /= (Real) In.multi;
    Pcs [n] /= (Real) In.multi;
    CS2[n] /= (Real) In.multi;
    Pcs2[n] /= (Real) In.multi;
    fprintf(out, "%6d\t%10g\t%10g\t%10g\t%10g\n",
	    n,
	    CS[n], sqrt(CS2[n]-CS[n]*CS[n])/sqm,
	    Pcs[n], sqrt(Pcs2[n]-Pcs[n]*Pcs[n])/sqm);
  }
  fclose(out);

  RealVectorFree(CS );
  RealVectorFree(Pcs );
  RealVectorFree(CS2);
  RealVectorFree(Pcs2);
}

static void StatSCCSize(Int NK)
{
  register int i;
  Int n;
  Real *PS, *PS2;
/*    Int *Count; */
  Int psize;
  char line[128];
  char file[128];
  FILE *in;
  FILE *out;

  if(!In.scc) return;

  PS  = RealVectorAlloc(NK);
  PS2 = RealVectorAlloc(NK);
/*    Count = IntVectorAlloc(NK); */

  RealVectorInit(PS, NK, 0.0);
  RealVectorInit(PS2,NK, 0.0);
/*    IntVectorInit(Count,NK, 0.0); */

  printf("Building statistics for SCC Size\n");

  for(i=0; i<In.multi; i++) {
    sprintf(file, "=%s%04d.SCCSizeDistribution.dat", In.projname, i);
    in = fopen( file,"r");
    if(!in) FileOpenError(file);
    Dots('.', i, 1+(In.multi>>6));
    fgets(line, 128, in); /* skip the initial comment */
    while(!feof(in)) {
      fscanf(in, "%d %d", &n, &psize);
      if(psize>0) {  
/*  	++Count[n]; */
	PS[n] += (Real) psize;
	PS2[n] += ((Real) psize)*psize;
      }
    }
    fclose(in);
  }
  
  printf("\n");
  
  sprintf(file, "=%s_STATS.SCCSize.dat", In.projname);
  out = fopen( file,"w");
  if(!out) FileOpenError(file);
  
  fprintf(out, "#%5s\t%10s\t%10s\n",
	  "Size", "P(Size)", "E[P(Size)]");

  for(n=0; n<NK; n++) {
    if(PS[n]) {
      PS [n] /= (Real) In.multi;
      PS2[n] /= (Real) In.multi;
      fprintf(out, "%6d\t%10g\t%10g\n",
	      n,
	      PS[n], sqrt(PS2[n]-PS[n]*PS[n])/sqm);
    }
  }
  fclose(out);

  sprintf(line, "MultiStat P(SCC Size) [%d runs]", In.multi);
  RunXmgrace(NULL, PS, INT,REAL, NK, line, "SCC Size", "P(Size)");

  RealVectorFree(PS );
  RealVectorFree(PS2);
/*    IntVectorFree(Count); */
}
