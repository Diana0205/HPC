#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>


#define N 1024


int llenarMatriz(int *matriz){
	int i,j;
	int fil=N,col=N;
	
	for(i=0;i<fil;i=i+1){
		for(j=0;j<col;j=j+1){
			matriz[i*col+j]=rand() % fil;
		}
	}
	
	
	return 0;
}


void matrixMultCPU(int *a, int *b, int *c) {
	int i,j,k;
	 
	int col=N,fil=N;
	 
	for (i=0;i<fil;i++) {
	 	for(j=0;j<col;j++){
		 	c[i*col+j]=0;
		 	for(k=0;k<col;k++){
			 	c[i*col+j]	= c[i*col+j]+a[i*col+k]*b[k*col+j];
			 }
			 
		 
		 }
		 
	}  	
	   
	
}


int main()
{
	int i,j;
	int* x;
	int* y;
	int* z;
	int fil=N,col=N;
	
	x = (int*)malloc(fil*col*sizeof(int*));
	y = (int*)malloc(fil*col*sizeof(int*));
	z = (int*)malloc(fil*col*sizeof(int*));
	
	
	llenarMatriz(x);
	llenarMatriz(y);
	
	
	/*for(i=0;i<fil;i=i+1){
		a[i]=(int*)malloc(col*sizeof(int));
	}
	
	
	for(i=0;i<fil;i=i+1){
		b[i]=(int*)malloc(col*sizeof(int));
		
	}
	
	
	
	for(i=0;i<fil;i=i+1){
		c[i]=(int*)malloc(col*sizeof(int));
	}*/
	
	clock_t start = clock();
	
	matrixMultCPU(x,y,z);
	
	/*
	printf("\nesta es la matriz 1") ;
	for (i=0;i<fil;i=i+1) 
	{ 
		printf("\n"); 
		for (j=0;j<col;j=j+1) 
			
			printf("\t%d", x[i*col+j] ); 
			
	} 
	
	printf("\nesta es la matriz 2") ;
	printf("\n"); 
	for (i=0;i<fil;i=i+1) 
	{ 
		printf("\n"); 
		for (j=0;j<col;j=j+1) 
			printf("\t%d", y[i*col+j] ); 
	} 
	
	printf("\nesta es la matriz resultado") ;
	printf("\n"); 
	for (i=0;i<fil;i=i+1) 
	{ 
		printf("\n"); 
		for (j=0;j<col;j=j+1) 
			printf("\t%d", z[i*col+j] ); 
	} 
	*/

	printf(" \n Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC) ; 
		

	
	// liberamos memoria
	free (x);
	free (y);
	free (z);
	
	return 0;
}
