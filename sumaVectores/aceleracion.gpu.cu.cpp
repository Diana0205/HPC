#include <cuda.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>


//programa que sume dos vectores. Utilizar macros para definir tamano del vector. Malloc para asignacion de memoria.
// dos funciones : llenarVector, sumarVector
// kala8ss


#define N 100

__global__ void add(int *a, int *b, int *c)
{
    int i=blockDim.x*blockIdx.x + threadIdx.x;
    
    c[i] = a[i]+b[i] ;    
     
    

}



int llenarVector(int *V)
{
    int i;
    
    V=(int*)malloc(sizeof(int)*N);
    //srand (time(NULL));
    for(i= 0; i < N; i++)
    {    
        
        V[i]=i;
        
        //printf("Vector %d \n",V[i]);        
    }
    
    
    return 0;
     
    
}


int sumarVectores(int *v1, int *v2,int *V3)
{
    int i;
    int *V1,*V2;
    
    V1=(int*)malloc(sizeof(int));
    V2=(int*)malloc(sizeof(int));    
    V3=(int*)malloc(sizeof(int));
    
    llenarVector(V1);
    llenarVector(V2);
    
    for(i=0;i<N;i++)
    {
        V3[i]=V1[i]+V2[i];
 
        
 
    }
    printf("La suma de los dos vectores da como resultado el vector c : %d",V3[i]);
    return 0;
    
}
//max 1024




int main()
{
    int *a;
    int *b;
    int *c;
    //int i = blockDim.x*blockIdx.x + threadIdx.x;
    
    a=(int*)malloc(sizeof(int));
    b=(int*)malloc(sizeof(int));
    c=(int*)malloc(sizeof(int));
    
    
    int *d_a;
    int *d_b;
    int *d_c;
    
    
    cudaMalloc((void **) &d_a, (sizeof(int)*N));
    cudaMalloc((void **) &d_b, (sizeof(int)*N));
    cudaMalloc((void **) &d_c, (sizeof(int)*N));

    float blockSize=32.0;
    float threadSize = ceil(N/blockSize);
    

    clock_t start = clock();

    cudaMemcpy(a, d_a, N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b, d_b, N*sizeof(int), cudaMemcpyHostToDevice);
    
    llenarVector(a);
    llenarVector(b);
    
    sumarVectores(a,b,c);
    
    add<<<blockSize,threadSize>>>(d_a,d_b,d_c);
    
    cudaMemcpy(d_c, c, N, cudaMemcpyDeviceToHost);
    
    
    
    printf(" \n Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC) ; 


    free(a);
    free(b);
    free(c);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);


    return 0;

}
