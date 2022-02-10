#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }
  FILE *fp = fopen(argv[1],"r");
  int ch = -1;
  int count = 0;
  int divisor = 256;
  int num;
  while (1) {
    int c = getc(fp);
    if (c == ch) {
      count += 1;
    } else if (count == 0) {
      ch = c;
      count += 1;
    } else {
      for (int _ = 0; _ < 4; _++) {
        num = count % divisor;
        fputc(num,stdout);
        count = count/divisor;    
      }
      fputc(ch,stdout);
      ch = c;
      count = 1;
    }
    if (c == EOF) {
      break;
    }
  }
  return 0;
}
