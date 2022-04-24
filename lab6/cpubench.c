#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

#define MSG "* running cpubench %s using %s with size %s and %s threads...\n"

#define USAGE "usage: ./cpubench <mode> <type> <size> <threads> \n" \
"     - mode: flops / matrix \n" \
"     - type: single / double \n" \
"     - size: 10 / 100 / 1000 / 1024 / 4096 / 16386 \n" \
"     - threads: 1 / 2 / 4 \n"

#define GIGAFLOPS 1000000000
#define GIGABYTES 1024*1024*1024


// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
void multiply_int(int** mat1, int** mat2, int** res, int size)
{
	//implement integer matrix multiplication

}

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
void multiply_double(double** mat1, double** mat2, double** res, int size)
{
	//implement double matrix multiplication

}


int compute_flops_int(int size)
{
	int index;
	int result;
	int loops = size*GIGAFLOPS;
	for (index=0;index<loops;index++)
	{
		result = index+1;
	}
	return result;
}

double compute_flops_double(int size)
{
	int index;
	double result;
	int loops = size*GIGAFLOPS;
	for (index=0;index<loops;index++)
	{
		result = index+1.0;
	}
	return result;
}


int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
    if (argc != 5) 
    {
        printf(USAGE);
        exit(1);
    } 
    else 
    {
		int mode = -1;
        if(strcmp(argv[1],"flops") == 0)
        	mode = 0;
        else if(strcmp(argv[1],"matrix") == 0)
        	mode = 1;
        else
        	mode = -1;

		int type = -1;
        if(strcmp(argv[2],"single") == 0)
        	type = 0;
        else if(strcmp(argv[2],"double") == 0)
        	type = 1;
        else
        	type = -1;


        int size = atoi(argv[3]);
        int num_threads = atoi(argv[4]);

		struct timeval start, end;

		if (mode == 0 && type == 0)
		{	
			gettimeofday(&start, NULL);
			compute_flops_int(size);
		    gettimeofday(&end, NULL);
		}
		else if (mode == 0 && type == 1)
		{	
			gettimeofday(&start, NULL);
			compute_flops_double(size);
		    gettimeofday(&end, NULL);
		}		
		else if (mode == 1 && type == 0)
		{	
			gettimeofday(&start, NULL);
			multiply_int(NULL,NULL,NULL,size);
		    gettimeofday(&end, NULL);
		}
		else if (mode == 1 && type == 1)
		{	
			gettimeofday(&start, NULL);
			multiply_double(NULL,NULL,NULL,size);
		    gettimeofday(&end, NULL);
		}
		else
		{
        	printf(USAGE);
			printf("unrecognized option, exiting...\n");
        	exit(1);
		}

		double elapsed_time_sec = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))/1000000.0;
		double num_giga_ops = 0;
		
		if (size*GIGAFLOPS < 0)
		{
			printf("error in size, check for overflow; exiting...\n");
			exit(1);
		}
		if (elapsed_time_sec < 0)
		{
			printf("error in elapsed time, check for proper timing; exiting...\n");
			exit(1);
		}
		if (elapsed_time_sec == 0)
		{
			printf("elapsed time is 0, check for proper timing or make sure to increase amount of work performed; exiting...\n");
			exit(1);
		}
			
		
		if (mode == 0)
			num_giga_ops = size;
		else if (mode == 1)
			num_giga_ops = size*size*size/(GIGABYTES);
		double throughput = num_giga_ops/elapsed_time_sec;
		printf("mode=%s type=%s size=%d threads=%d time=%lf throughput=%lf\n",argv[1],argv[2],size,num_threads,elapsed_time_sec,throughput);
 
    }

    return 0;
}
