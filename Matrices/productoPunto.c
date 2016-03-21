#include <stdio.h>
#define N 16

void matrixMultCPU(int **a, int **b, int **c) {
 int n,m;
 
 int col=N,fil=N;
 
 a=(int **)malloc(N*sizeof(int*));
 b=(int **)malloc(N*sizeof(int*));
 c=(int **)malloc(N*sizeof(int*));
 
 if (col<N && fil<N) {
 	for(n=0;n<N;n++){
	 m+= a[fil*N*n]*b[n*N+col];
	 
	 }
	 c[fil*N+col]=m;
	 }  	
   
   printf("Esta es la matriz resultado",**c);
  }
 

