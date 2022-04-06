#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
	int pid;
	
	if (argc < 3)
	{
		printf("not enough arguments...\n");
		printf("usage: ./parallel <processes> <cmd> <args>\n");
		return -1;
	}

	//write your code here to invoke the number of processes (cmd and args specified) and wait for all of them to complete before exiting	
	
	return 0;
}