#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h> 

#define MSG "running runtime with %s %s %s...\n"

#define USAGE "usage: ./runtime <THREAD_POOL> <NUM_TASKS> <SLEEP> \n" \
"     - THREAD_POOL: 1 / 10 \n" \
"     - NUM_TASKS: 1 / 10 / 1000 \n" \
"     - SLEEP: 1 / 10 \n" 


int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
    if (argc != 4) 
    {
        printf(USAGE);
        exit(1);
    } 
    else 
    {
        printf(MSG, argv[1], argv[2], argv[3]);
        int THREAD_POOL = atoi(argv[1]);
        int NUM_TASKS = atoi(argv[2]);
        int SLEEP = atoi(argv[3]);
		struct timeval start, end;

		//Initialize thread pool of size THREAD_POOL
		printf("Initialize thread pool of size %d\n",THREAD_POOL);

		//get start timestamp
  		gettimeofday(&start, NULL);

		//Running NUM_TASKS sleep tasks where each task sleeps SLEEP seconds
		printf("Running %d sleep tasks where each task sleeps %d seconds\n",NUM_TASKS,SLEEP);

		//get end timestamp
		 gettimeofday(&end, NULL);

		double elapsed_time_us = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		
		printf("Completed running %d sleep %d second tasks using a thread pool of size %d in %lf seconds\n",NUM_TASKS,SLEEP,THREAD_POOL,elapsed_time_us/1000000.0);
    }

    return 0;
}
