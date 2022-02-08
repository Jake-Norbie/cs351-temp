#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s STRING1 STRING2\n", argv[0]);
    printf("       %s -d STRING\n", argv[0]);
    exit(1);
  }
  char str[100];
  fgets(str, 100, stdin);
  for (int l = 0; l < strlen(str); l++) {
     char *pos;
     pos = strchr(argv[1],str[l]);
     if (pos) {
       printf("%c",argv[2][pos - &argv[1][0]]);
     }
     else {
       printf("%c",str[l]);
     }
  }
  printf("%d",&argv[1][1]); 
  exit(0); 
  return 0;
}
