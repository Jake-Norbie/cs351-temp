#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s STRING1 STRING2\n", argv[0]);
    printf("       %s -d STRING\n", argv[0]);
    exit(1);
  }
  if (strlen(argv[1]) != (strlen(argv[2])) && (strcmp(argv[1],"-d") != 0)) {
    printf("STRING1 and STRING2 must have the same length\n");
    exit(1);
  }
  while (1) {
    char str[100];
    if (fgets(str,100, stdin) == NULL) {
      break;
    }
    for (int l = 0; l < strlen(str); l ++) {
       char *pos;
       if (strcmp(argv[1],"-d") == 0) {
         pos = strchr(argv[2],str[l]);
         if (!pos) {
           printf("%c",str[l]);
         }
       } else {
         pos = strchr(argv[1],str[l]);
         if (pos) {
           printf("%c",argv[2][pos - &argv[1][0]]);
         }
         else {
           printf("%c",str[l]);
         }
       }
    }
  } 
  exit(0); 
  return 0;
}
