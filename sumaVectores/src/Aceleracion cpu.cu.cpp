#include <cuda.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>


//programa que sume dos vectores. Utilizar macros para definir tamano del vector. Malloc para asignacion de memoria.
// dos funciones : llenarVector, sumarVector
// kala8ss


#define N 6000000

/*__global__ void add(int *a, int *b, int *c)
{
    int i=blockDim.x*blockIdx.x + threadIdx.x;
    
    c[i] = a[i]+b[i] ;    
     
    

}*/



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


int sumarVectores(int *v1, int *v2,int *v3)
{
    int i;
    
    
   
    
    for(i=0;i<N;i++)
    {
        v3[i]=v1[i]+v2[i];
 
        
 
    }
    //printf("La suma de los dos vectores da como resultado el vector c : %d",V3[i]);
    return 0;
    
}
//max 1024




int main()
{
    int *a;
    int *b;
    int *c;
    //int i = blockDim.x*blockIdx.x + threadIdx.x;
    
    a=(int*)malloc(sizeof(int)*N);
    b=(int*)malloc(sizeof(int)*N);
    c=(int*)malloc(sizeof(int)*N);
    
  
    
    

    clock_t start = clock();

       
    llenarVector(a);
    llenarVector(b);
    
    sumarVectores(a,b,c);
    
    
    
    
    printf(" \n Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC) ; 


    free(a);
    free(b);
    free(c);

   

    return 0;

}
