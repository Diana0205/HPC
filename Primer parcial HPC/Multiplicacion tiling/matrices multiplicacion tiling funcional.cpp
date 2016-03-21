#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <math.h>

#define TILE_WIDTH 32
#define width 32 			//tamaño del vector

int llenarMatriz(int *matriz){
  int i,j;
  //int width=2048;
  
  for(i=0;i<width;i++){
    for(j=0;j<width;j++){
      matriz[i*width+j]=rand() % width;
    }
  }
  
  
  return 0;
}



__global__ void MatrizTiles(int *d_a ,int *d_b,int *d_c )
{
	__shared__ int Mds[TILE_WIDTH][TILE_WIDTH];
  __shared__ int Nds[TILE_WIDTH][TILE_WIDTH];
	int fil=blockIdx.x*TILE_WIDTH+threadIdx.x;
	int col=blockIdx.y*TILE_WIDTH+threadIdx.y;
	int Pvalue=0;
  
  
  for(int i=0;i<width/TILE_WIDTH;i++)
  {
  	Mds[threadIdx.y][threadIdx.x]=d_a[fil*width + i*TILE_WIDTH + threadIdx.x];
  	Nds[threadIdx.y][threadIdx.x]=d_b[(i*TILE_WIDTH + threadIdx.x) * width + col];
    
    __syncthreads();
    
    for(int k = 0; k < TILE_WIDTH; ++k){
		Pvalue += Mds[threadIdx.y][k] * Nds[k][threadIdx.x];	    
	}
	__syncthreads();
    }
  d_c[fil*width+col]=Pvalue;
}

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main()
{
	int *m1;
	int *m2;
	int *m3;
	

  /* inicializando variables con datos foo*/
 	m1 = (int*)malloc(width*width*sizeof(int));
 	m2 = (int*)malloc(width*width*sizeof(int));
 	m3 = (int*)malloc(width*width*sizeof(int));
	 	
 	llenarMatriz(m1);
  	llenarMatriz(m2);
 	
 	
 	//Vslores GPU
 	int *dm1, *dm2, *dm3;

  cudaMalloc((void**) &dm1, width*width* sizeof(int));
 	cudaMalloc((void**) &dm2, width*width* sizeof(int));
 	cudaMalloc((void**) &dm3, width*width* sizeof(int));
 
 	

  // copiando memoria a la GPU
 	cudaMemcpy(dm1, m1, width*width * sizeof(int), cudaMemcpyHostToDevice);
 	cudaMemcpy(dm2, m2, width*width * sizeof(int), cudaMemcpyHostToDevice);

  // cada bloque en dimensión x y y tendrá un tamaño 32 threads
  float Blocksize=32.0;
 	dim3 dimBloque(Blocksize, Blocksize,1);

    // El grid tendrá B número de bloques en x y y
 	dim3 dimGrid(ceil(width/float(Blocksize)),ceil(width/float(Blocksize)),1);

  clock_t start = clock();
  // Llamando a ejecutar el kernel
 	MatrizTiles<<<dimGrid, dimBloque>>>(dm1, dm2, dm3);

  // copiando el resultado a la memoria Host
	 cudaMemcpy(m3, dm3, width*width * sizeof(int), cudaMemcpyDeviceToHost);
 //cudaMemcpy(m2, dm2, N * N * sizeof(int), cudaMemcpyDeviceToHost);

  printf("Tiempo transcurrido: %f", ((double)clock() - start) / CLOCKS_PER_SEC);
  
  
	free(m1);
	free(m2);
	free(m3);

  	cudaFree(dm1);
	cudaFree(dm2);
 	cudaFree(dm3);

  printf("\n");


  }
