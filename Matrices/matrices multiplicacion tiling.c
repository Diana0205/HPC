#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <cuda.h>
#include <math.h>

#define TILE_WIDTH 4


// Simple utility function to check for CUDA runtime errors
void checkCUDAError(const char *msg);

// Part 3 of 5: implement the kernel
__global__ void MatrixTiles(int *d_a ,int *d_b,int *d_c,int width )
{
  int fil=blockIdx.x*TILE_WIDTH+threadIdx.x;
  int col=blockIdx.y*TILE_WIDTH+threadIdx.y;
  
  
  int pvalue=0;
  //for each computes one element of the block sub-matrix
  for(int i=0;i<width;i++)
  {
    pvalue+=(d_a[fil*width+i]*d_b[i*width+col]);
  }
  d_c[fil*width+col]=pvalue;
}

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main( ) 
{
    // pointer for host memory
    int *h_a,*h_b,*h_c;

    // pointer for device memory
    int *d_a,*d_b,*d_c;

    // define grid and block size
    int numBlocks = 4;
    int numThreadsPerBlock = 16;

    // Part 1 of 5: allocate host and device memory
    size_t memSize = numBlocks * numThreadsPerBlock * sizeof(int);
    h_a = (int *) malloc(memSize);
    cudaMalloc((void**) &d_a,memSize );
    
    
    h_b = (int *) malloc(memSize);
    cudaMalloc((void**) &d_b,memSize );
    
    h_c = (int *) malloc(memSize);
    cudaMalloc((void**) &d_c,memSize );
    
    
    
    for(int n=0;n<numThreadsPerBlock*numBlocks;n++)
    {
      h_a[n]=h_b[n]=1;
    }

    // Part 2 of 5: configure and launch kernel
    dim3 dimGrid( numBlocks/2,numBlocks/2 );
    dim3 dimBlock(  numThreadsPerBlock/TILE_WIDTH,numThreadsPerBlock/TILE_WIDTH);
    

   

    // check if kernel execution generated an error
    checkCUDAError("kernel execution");

    // Part 4 of 5: device to host copy
    cudaMemcpy( d_a,h_a ,memSize,cudaMemcpyHostToDevice);
    cudaMemcpy( d_b,h_b ,memSize,cudaMemcpyHostToDevice);
    
    
    MatrixTiles<<< dimGrid ,dimBlock  >>>(d_a,d_b,d_c,TILE_WIDTH*2);
     // block until the device has completed
    cudaThreadSynchronize();
    cudaMemcpy( h_c,d_c ,memSize,cudaMemcpyDeviceToHost);

    // Check for any CUDA errors
    checkCUDAError("cudaMemcpy");

    for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
         printf(" ",h_c[8*i+j]);
      
    }

    // free device memory
    cudaFree(d_a);

    // free host memory
    free(h_a);

    // If the program makes it this far, then the results are correct and
    // there are no run-time errors.  Good work!
    printf("Correct!\n");

    return 0;
}

void checkCUDAError(const char *msg)
{
    cudaError_t err = cudaGetLastError();
    if( cudaSuccess != err) 
    {
        fprintf(stderr, "Cuda error: %s: %s.\n", msg, cudaGetErrorString( err) );
        exit(-1);
    }                         
}
