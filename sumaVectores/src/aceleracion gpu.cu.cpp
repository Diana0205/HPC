#include <cuda.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>


//programa que sume dos vectores. Utilizar macros para definir tamano del vector. Malloc para asignacion de memoria.
// dos funciones : llenarVector, sumarVector
// kala8ss


#define N 1000000

void llenarVector(int *V)
{
    int i;
    for(i= 0; i < N; i++)
    {            
        V[i]=rand()%N;         
    }  
      
   
}

__global__ void add(int *a, int *b, int *c)
{
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<N){
    	c[i] = a[i]+b[i] ;
	}
           

}


int main()
{
	//valores CPU
    int *a;
    int *b;
    int *c;
    
    a=(int*)malloc(sizeof(int)*N);
    b=(int*)malloc(sizeof(int)*N);
    c=(int*)malloc(sizeof(int)*N);
    
     llenarVector(a);
    llenarVector(b);
    
    //valores de GPU
    int *d_a;
    int *d_b;
    int *d_c;   
    
    cudaMalloc((void **) &d_a, (sizeof(int)*N));
    cudaMalloc((void **) &d_b, (sizeof(int)*N));
    cudaMalloc((void **) &d_c, (sizeof(int)*N));

    float blockSize=1024.0;
    float grid = ceil(N/blockSize);
    

    clock_t start = clock();

    cudaMemcpy(d_a, a, N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*sizeof(int), cudaMemcpyHostToDevice);
    
   
    add<<<grid,blockSize>>>(d_a,d_b,d_c);
    
    cudaMemcpy(c, d_c, N*sizeof(int), cudaMemcpyDeviceToHost);
    
      
    printf(" \n Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC) ; 


    free(a);
    free(b);
    free(c);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);


    return 0;

}
