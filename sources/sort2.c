#include <stdio.h>
#include <stdlib.h>

#include "main.h" /* for the typedef Real */
#define NRANSI

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;

#define M 7
#define NSTACK 50
#define NR_END 1

static void nrerror(const char *msg)
{
  fprintf(stderr, msg);
  exit(1);
}

#define FREE_ARG char*
static void free_ivector(int *v, long nl, long nh)
/* free an int vector allocated with ivector() */
{
        free((FREE_ARG) (v+nl-NR_END));
}

static int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
        int *v;

        v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
        if (!v) nrerror("allocation failure in ivector()::sort2.c");
        return v-nl+NR_END;
}

void sort2(unsigned long n, Real *arr, Real *brr)
{
  /* Sorts an array arr[1..n] into ascending order using Quicksort,
     while making the corresponding rearrangement of the array brr[1..n] */

  /* NOW: arr[0...n-1], brr[0...n-1] as usual. VITUS */

	unsigned long i,ir=n,j,k,l=1;
	int *istack,jstack=0;
	Real a,b,temp;

	--arr; --brr; /* VITUS: Arrays adjusted */

	istack=ivector(1,NSTACK);
	for (;;) {
		if (ir-l < M) {
			for (j=l+1;j<=ir;j++) {
				a=arr[j];
				b=brr[j];
				for (i=j-1;i>=l;i--) {
					if (arr[i] <= a) break;
					arr[i+1]=arr[i];
					brr[i+1]=brr[i];
				}
				arr[i+1]=a;
				brr[i+1]=b;
			}
			if (!jstack) {
				free_ivector(istack,1,NSTACK);
				return;
			}
			ir=istack[jstack];
			l=istack[jstack-1];
			jstack -= 2;
		} else {
			k=(l+ir) >> 1;
			SWAP(arr[k],arr[l+1])
			SWAP(brr[k],brr[l+1])
			if (arr[l] > arr[ir]) {
				SWAP(arr[l],arr[ir])
				SWAP(brr[l],brr[ir])
			}
			if (arr[l+1] > arr[ir]) {
				SWAP(arr[l+1],arr[ir])
				SWAP(brr[l+1],brr[ir])
			}
			if (arr[l] > arr[l+1]) {
				SWAP(arr[l],arr[l+1])
				SWAP(brr[l],brr[l+1])
			}
			i=l+1;
			j=ir;
			a=arr[l+1];
			b=brr[l+1];
			for (;;) {
				do i++; while (arr[i] < a);
				do j--; while (arr[j] > a);
				if (j < i) break;
				SWAP(arr[i],arr[j])
				SWAP(brr[i],brr[j])
			}
			arr[l+1]=arr[j];
			arr[j]=a;
			brr[l+1]=brr[j];
			brr[j]=b;
			jstack += 2;
			if (jstack > NSTACK) nrerror("NSTACK too small in sort2.");
			if (ir-i+1 >= j-l) {
				istack[jstack]=ir;
				istack[jstack-1]=i;
				ir=j-1;
			} else {
				istack[jstack]=j-1;
				istack[jstack-1]=l;
				l=i;
			}
		}
	}
}
#undef M
#undef NSTACK
#undef SWAP
#undef NRANSI
#undef NR_END
#undef FREE_ARG
/* (C) Copr. 1986-92 Numerical Recipes Software ^. */
