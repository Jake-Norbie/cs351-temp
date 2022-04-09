#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

#define MSG "* running netio with method %s operation %s for %s number of ops...\n"

#define USAGE "usage: ./netio <method> <operation> <num_ops> \n" \
"     - method: function / pipe / socket \n" \
"     - operation: add / subtract / multiply / divide \n" \
"     - num_calls: 1000 | 1000000 | 1000000000 \n"

double multiply(double a, double b)
{
	return a*b;
}

double divide(double a, double b)
{
	if(b == 0.0)
		return 0;
	else
		return a/b;
}

double add(double a, double b)
{
	//printf("add(%f,%f)\n",a,b);

	return a+b;
}

double subtract(double a, double b)
{
	return a-b;
}


int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
	int method = -1; //used to store what method to test
	int operation = -1; //used to store what operation to test
    if (argc != 4) 
    {
        printf(USAGE);
        exit(1);
    } 
    else 
    {
        printf(MSG, argv[1], argv[2], argv[3]);
        if(strcmp(argv[1],"function") == 0)
        	method = 0;
        else if(strcmp(argv[1],"pipe") == 0)
        	method = 1;
        else if(strcmp(argv[1],"socket") == 0)
        	method = 2;
        else
        	method = -1;

        if(strcmp(argv[2],"add") == 0)
        	operation = 0;
        else if(strcmp(argv[2],"subtract") == 0)
        	operation = 1;
        else if(strcmp(argv[2],"multiply") == 0)
        	operation = 2;
        else if(strcmp(argv[2],"divide") == 0)
        	operation = 3;
        else
        	operation = -1;

        int num_ops = atoi(argv[3]);

		struct timeval start, end;

  		gettimeofday(&start, NULL);

		double ret_value = 0.0;

   		switch (method)
     	{
        	case 0:
   				switch (operation)
     			{
        			case 0:
           				for (int i=0;i<num_ops;i++)
           					ret_value = add((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);
           				break;
        			case 1:
           				for (int i=0;i<num_ops;i++)
           					ret_value = subtract((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);
           				break;
        			case 2:
           				for (int i=0;i<num_ops;i++)
           					ret_value = multiply((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);
           				break;
        			case 3:
           				for (int i=0;i<num_ops;i++)
           					ret_value = divide((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);
           				break;
        			default:
           				printf("operation not supported, exit...\n");
           				return -1;
     			}		
     			break;
        	case 1:
   				switch (operation)
     			{
        			case 0:
           				printf("%s %s %s\n",argv[1],argv[2],argv[3]);
           				break;
        			case 1:
           				printf("%s %s %s\n",argv[1],argv[2],argv[3]);
           				break;
					case 2:
						printf("%s %s %s\n",argv[1],argv[2],argv[3]);
						break;
					case 3:
						printf("%s %s %s\n",argv[1],argv[2],argv[3]);
						break;
					default:
           				printf("operation not supported, exit...\n");
           				return -1;
     			}		
     			break;
        	case 2:
   				switch (operation)
     			{
        			case 0:
           				printf("%s %s %s\n",argv[1],argv[2],argv[3]);
           				break;
        			case 1:
           				printf("%s %s %s\n",argv[1],argv[2],argv[3]);
           				break;
					case 2:
					   	printf("%s %s %s\n",argv[1],argv[2],argv[3]);
					   	break;
					case 3:
					   	printf("%s %s %s\n",argv[1],argv[2],argv[3]);
					   	break;
					default:
           				printf("operation not supported, exit...\n");
           				return -1;
     			}		
     			break;
        default:
        	printf("method not supported, exit...\n");
           	return -1;
     	}		

     	gettimeofday(&end, NULL);

		double elapsed_time_us = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		printf("==> %f ops/sec\n",(num_ops/elapsed_time_us)*1000000);
 
    }

    return 0;
}
