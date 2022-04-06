#include <stdio.h>
#include <string.h>

unsigned long myhash(char*,int);

int main(int argc, char **argv)
{
    if (argc != 2) 
    {
        printf("single argument expected with no spaces, exiting...\n");
        return -1;
    } 
    else 
    {
        printf("%lu\n",myhash(argv[1],strlen(argv[1])));
        return 0;
    }
}

unsigned long myhash(char *str, int len)
{
    unsigned long hash = 0;
    for (int i=0;i<len;i++)
    	hash += str[i];
    return hash;
}

