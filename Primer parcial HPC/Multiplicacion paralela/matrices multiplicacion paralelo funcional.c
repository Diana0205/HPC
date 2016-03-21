#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <math.h>


#define N 3
#define T 3

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

__global__ void mulMatrizGPU(int *a, int *b, int *c) {

	//calculando el indice de fila
 	int fil = blockIdx.y * blockDim.y + threadIdx.y;
 	int col = blockIdx.x * blockDim.x + threadIdx.x;
	float cont=0;
  	
  	
  	if((fil<N)&&(col<N))
  	{
  		for(int k=0; k < N; k++){
			 	c[fil*col+N] = c[fil*N+col]*a[fil*N+k]*b[k*N+col];
		 }
    
   }
}


int main() 
{
	//valores CPU
	int* m1;
	int* m2;
	int* m3;
	int i, j;
	int c = 0;
	int fil=N,col=N;
  

  /* inicializando variables con datos foo*/
 	m1 = (int*)malloc(fil*col*sizeof(int));
 	m2 = (int*)malloc(fil*col*sizeof(int));
 	m3 = (int*)malloc(fil*col*sizeof(int));
 	
 	llenarMatriz(m1);
    llenarMatriz(m2);
 	
 	//Vslores GPU
 	int *dm1, *dm2, *dm3;

    cudaMalloc((void**) &dm1, fil * col * sizeof(int));
 	cudaMalloc((void**) &dm2, fil * col * sizeof(int));
 	cudaMalloc((void**) &dm3, fil * col * sizeof(int));

  
    float blockSize =32.0;	
 	dim3 dimBloques(blockSize,blockSize,1);
	dim3 dimGrid(ceil(float(N)/blockSize),ceil(float(N)/blockSize),1);
  
    clock_t start = clock();
  
 	cudaMemcpy(dm1, m1, fil * col * sizeof(int), cudaMemcpyHostToDevice);
 	cudaMemcpy(dm2, m2, fil * col * sizeof(int), cudaMemcpyHostToDevice);

  
    mulMatrizGPU<<<dimGrid, dimBloques>>>(dm1, dm2, dm3);

  
	cudaMemcpy(m3, dm3, N * N * sizeof(int), cudaMemcpyDeviceToHost);
 
  
    printf("Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC);

  
  	free(m1);
  	free(m2);
  	free(m3);
  
  
    cudaFree(dm1);
	cudaFree(dm2);
 	cudaFree(dm3);



}
