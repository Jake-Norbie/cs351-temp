#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h> 

#define MSG "running matrixadd3d with size %s...\n"

#define USAGE "usage: ./matrixadd3d <size> \n" \
"     - size: 4 / 128 / 1024 \n" \


// This function adds mat1[][][] and mat2[][][],
// and stores the result in res[][][]
void add(double*** mat1, double*** mat2, double*** res, int size)
{

}

// This function finds the minimum value in mat[][][] array
double min(double*** mat, int size)
{
    return 0.0;
}

// This function finds the average value in mat[][][] array
double aver(double*** mat, int size)
{
    return 0.0;
}

// This function finds the maximum value in mat[][][] array
double max(double*** mat, int size)
{
    return 0.0;
}

// This function frees the memory allocated to mat[][][] array
void free_array(double ***mat, size_t len)
{

}

// This function allocates dynamic memory to mat[][][] array and returns it
double ***alloc_array(size_t len)
{
    size_t mem_aloc = sizeof(double *) * len * len * len;
    printf("allocating %lf GB memory...\n",mem_aloc*1.0/(1024*1024*1024)); 
	return NULL;
}


int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
    if (argc != 2) 
    {
        printf(USAGE);
        exit(1);
    } 
    else 
    {

        printf(MSG, argv[1]);

        int size = atoi(argv[1]);
		struct timeval start, end;
    	size_t len = 0;

		//declare arr1, arr2, and arr3
		double ***arr1 = alloc_array(size);
		double ***arr2 = alloc_array(size);
		double ***arr3 = alloc_array(size);

		//initialize arr1 and arr2 to random double values between 0.0 and 1.0

		//get start timestamp
  		gettimeofday(&start, NULL);

		//add arr1 and arr2 and store it in arr3
		printf("add arr1 and arr2 and store it in arr3\n");
		add(arr1,arr2,arr3,size);
		//compute minimum value of arr3
		printf("min(arr3)=%lf\n",min(arr3,size));
		//compute aver value of arr3
		printf("aver(arr3)=%lf\n",aver(arr3,size));
		//compute max value of arr3
		printf("max(arr3)=%lf\n",max(arr3,size));

		double elapsed_time_us = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		printf("matrixadd3d with 3D array of size %d ==> %lf MFlop/sec\n",size,(size*size*size*4/(1024*1024))/(elapsed_time_us/1000000.0));
 
    }

    return 0;
}
