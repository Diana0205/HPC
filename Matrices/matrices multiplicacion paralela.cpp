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

__global__ void mulMatriceGPU(float *a, float *b, float *c, int width) {

	//calculando el indice de fila
 	int fil = blockIdx.y * blockDim.y + threadIdx.y;
 	int col = blockIdx.x * blockDim.x + threadIdx.x;
	float cont=0;
  	
  	
  	if((fil<width)&&(col<width))
  	{
  		cont=0;
  		//cada hilo calcula un elemento del sub- bloque de la matriz
  		for(int k=0; k < width; k++){
			 	cont += a[fil*width+k]*b[k*width+col];
		 }
		c[fil*width+col]=cont;
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
 	
 	llenarVector(m1));
    llenarVector(m2);
 	
 	//Vslores GPU
 	int *dm1, *dm2, *dm3;

    cudaMalloc((void**) &dm1, fil * col * sizeof(int));
 	cudaMalloc((void**) &dm2, fil * col * sizeof(int));
 	cudaMalloc((void**) &dm3, fil * col * sizeof(int));

  // copiando memoria a la GPU
 	cudaMemcpy(dm1, m1, fil * col * sizeof(int), cudaMemcpyHostToDevice);
 	cudaMemcpy(dm2, m2, fil * col * sizeof(int), cudaMemcpyHostToDevice);

  // cada bloque en dimensión x y y tendrá un tamaño de T Threads
 	dim3 dimThreadsBloque(T, T);

  // Calculando el número de bloques en 1D
 	float BFloat = (float) N / (float) T;
 	int B = (int) ceil(BFloat);

  // El grid tendrá B número de bloques en x y y
 	dim3 dimBloques(B, B);

  // Llamando a ejecutar el kernel
 	mulMatriceGPU<<<dimBloques, dimThreadsBloque>>>(dm1, dm2, dm3);

  // copiando el resultado a la memoria Host
	 cudaMemcpy(m3, dm3, N * N * sizeof(int), cudaMemcpyDeviceToHost);
 //cudaMemcpy(m2, dm2, N * N * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(dm1);
	cudaFree(dm2);
 	cudaFree(dm3);

  printf("\n");

  for (i = 0; i < N; i++) {
  for (j = 0; j < N; j++) {
   printf(" [%d,%d]=%d", i, j, m3[i][j]);

   }
  printf("\n\n");

  }
 printf("\nB = %d", B);
 printf("\n%d, %d",dimBloques.x, dimBloques.y);
 printf("\n%d, %d",dimThreadsBloque.x, dimThreadsBloque.y);
 return (EXIT_SUCCESS);
}
