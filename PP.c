#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>


#define N 4


int llenarMatriz(int **matriz){
	int i,j;
	
	for(i=0;i<N;i=i+1){
		for(j=0;j<N;j=j+1){
			matriz[i][j]=rand() % N;
		}
	}
	
	
	return 0;
}


void matrixMultCPU(int **a, int **b, int **c) {
	 int i,j,k;
	 
	 //int col=N,fil=N;
	 
	/* a=(int **)malloc(N*sizeof(int*));
	 b=(int **)malloc(N*sizeof(int*));
	 c=(int **)malloc(N*sizeof(int*));*/
	 
	 for (i=0;i<N;i++) {
	 	for(j=0;j<N;j++){
		 	c[i][j]=0;
		 	for(k=0;k<N;k++){
			 	c[i][j]	= c[i][j]+a[i][j]*b[i][j];
			 }
			 
		 
		 }
		 
	}  	
	   
	
}


int main()
{
	int i,j;
	
	int** a;
	a = (int**)malloc(N*sizeof(int*));
	for(i=0;i<N;i=i+1){
		a[i]=(int*)malloc(N*sizeof(int));
	}
	
	int** b;
	b = (int**)malloc(N*sizeof(int*));
	for(i=0;i<N;i=i+1){
		b[i]=(int*)malloc(N*sizeof(int));
		
	}
	
	
	int** c;
	c = (int**)malloc(N*sizeof(int*));
	for(i=0;i<N;i=i+1){
		c[i]=(int*)malloc(N*sizeof(int));
	}
	
	clock_t start = clock();
	
	
	llenarMatriz(a);
	llenarMatriz(b);
	matrixMultCPU(a,b,c);
	
	printf("\nesta es la matriz 1") ;
	for (i=0;i<N;i=i+1) 
	{ 
		printf("\n"); 
		for (j=0;j<N;j=j+1) 
			
			printf("\t%d", a[i][j] ); 
			
	} 
	
	printf("\nesta es la matriz 2") ;
	printf("\n"); 
	for (i=0;i<N;i=i+1) 
	{ 
		printf("\n"); 
		for (j=0;j<N;j=j+1) 
			printf("\t%d", b[i][j] ); 
	} 
	
	printf("\nesta es la matriz resultado") ;
	printf("\n"); 
	for (i=0;i<N;i=i+1) 
	{ 
		printf("\n"); 
		for (j=0;j<N;j=j+1) 
			printf("\t%d", c[i][j] ); 
	} 
	
	printf(" \n Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC) ; 
	// liberamos memoria
	free (a);
	free (b);
	free (c);
	
	return 0;
}
