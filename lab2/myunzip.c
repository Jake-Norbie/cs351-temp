#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }
  FILE *fp = fopen(argv[1],"r");
  while (1) {
    int num1;
    if ((num1 = fgetc(fp)) == EOF) {
      break;
    }
    int num2 = fgetc(fp) * 256;
    int num3 = fgetc(fp) * 65536;
    int num4 = fgetc(fp) * 1677216;
    int c = fgetc(fp);
    if (c == EOF) {
      break;
    }
    for (int t1 = 0; t1 < num1; t1++) {
      printf("%c",c);
    }
    for (int t2 = 0; t2 < num2; t2++) {
      printf("%c",c);
    }
    for (int t3 = 0; t3 < num3; t3++) {
      printf("%c",c);
    }
    for (int t4 = 0; t4 < num4; t4++) {
      printf("%c",c);
    }
    //printf("\n");
  }
  exit(0);
  return 0;
}
