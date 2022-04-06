#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MSG "* running fileio %s workload with %s blocks and %s process(es) and %s measure\n"

#define USAGE "usage: ./fileio <workload> <block_size> <num_procs> <measure>\n" \
"     - workload: WS / WR / RS / RR \n" \
"     - block_size: 1KB / 10KB / 1000KB / 1MB \n" \
"     - num_procs: 1 / 2 / 4 \n" \
"     - measure: IOPS / THROUGHPUT \n" \
"     - WS = write-sequential \n" \
"     - WR = write-random \n" \
"     - RS = read-sequential \n" \
"     - RR = read-random \n"
clock_t start, end;
int ops = 0;
void read_sequential(int processes, int block_size);
void read_random(int processes, int block_size);
void write_sequential(int processes, int block_size);
void write_random(int processes, int block_size);
void read_random_small(int processes, int block_size);
void write_random_small(int processes, int block_size);


int main(int argc, char **argv)
{
    if (argc != 5) {
        printf(USAGE);
        exit(1);
    } else {
	int processes = (int) argv[3][0] - 48;
	int block_size;
	double cpu_time_used;
	double metric;
	char *units;
	
	if (strcmp(argv[2], "64KB") == 0) {
		block_size = 64000;
	} else if (strcmp(argv[2], "1MB") == 0) {
		block_size = 1000000;
	} else if (strcmp(argv[2], "16MB") == 0) {
		block_size = 16000000;
	} else if (strcmp(argv[2], "4KB") == 0) {
		block_size = 4000;
	}
	
	if (argv[1][0] == 'R') {
		if (argv[1][1] == 'S') {
			read_sequential(processes, block_size);
		} else if (argv[1][1] == 'R') {
			if (strcmp(argv[4], "THROUGHPUT") == 0) {
				read_random(processes, block_size);
			} else if (strcmp(argv[4], "IOPS") == 0) {
				read_random_small(processes, block_size);
			}
		}
	} else if (argv[1][0] == 'W') {
		if (argv[1][1] == 'S') {
                        write_sequential(processes, block_size);
                } else if (argv[1][1] == 'R') {
			if (strcmp(argv[4], "THROUGHPUT") == 0) {
				write_random(processes, block_size);
			} else if (strcmp(argv[4], "IOPS") == 0) {
				write_random_small(processes, block_size);
			}
                }
	
	}
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	if (strcmp(argv[4], "THROUGHPUT") == 0) {
		metric = (double) 1000 / cpu_time_used; 
		units = "MB per second";
	} else if (strcmp(argv[4], "IOPS") == 0) {
		metric = (double) ops / cpu_time_used;
		units = "I/O Operations per second";
	} 
	printf("%s measure for workload %s with %s block size and %s process(es): %f%s\n", argv[4], argv[1], argv[2], argv[3], metric, units);  
    }
    return 0;
}

void read_help(char *filename, int block_size) {
	FILE * fp = fopen(filename, "r");
	char *buff;
        buff = (char *) malloc(block_size);
	while(!feof(fp)) {
		fread(buff, sizeof(char), block_size, fp);
	}
	free(buff);
	fclose(fp);
}

void write_help(char *filename, int block_size) {
	FILE * fp = fopen(filename, "r");
	char s[6], str[16];
       	s[0] = filename[strlen(filename)-5];
	s[1] = '.';
	s[2] = 't';
	s[3] = 'x';
	s[4] = 't';
	s[5] = '\0';
	strcpy(str, "testfiles/");
	FILE * wfp = fopen(strcat(str,s), "w");
	char *buff;
	buff = (char *) malloc(block_size);
	while(!feof(fp)) {
		fread(buff, sizeof(char), block_size, fp);
		fwrite(buff, sizeof(char), block_size, wfp);
	}
	free(buff);
	fclose(fp);
	fclose(wfp);
}

void read_help_random(char *filename, int read_size, int block_size) {
	FILE * fp = fopen(filename, "r");
	char *buff;
	int left = read_size;
	int div = read_size - block_size;
	buff = (char *) malloc(block_size);
	if ((read_size - block_size) <= 0) {
                div = 1;
        }
	while (left > 0) {
		fseek(fp, rand() % div, SEEK_SET); 
		fread(buff, sizeof(char), block_size, fp);
		ops += 1;
		left -= block_size;
	}
	free(buff);
	fclose(fp);
}

void write_help_random(char *filename, int read_size, int block_size) {
	FILE * fp = fopen(filename, "r");
	char s[6], str[16];
        s[0] = filename[strlen(filename)-5];
        s[1] = '.';
        s[2] = 't';
        s[3] = 'x';
        s[4] = 't';
        s[5] = '\0';
        strcpy(str, "testfiles/");
        FILE * wfp = fopen(strcat(str,s), "w");
	char *buff;
	int left = read_size;
	int div = read_size - block_size;
	buff = (char *) malloc(block_size);
	if ((read_size - block_size) <= 0) {
		div = 1;
	}
	while (left > 0) {
		fseek(fp, rand() % div, SEEK_SET);
		fread(buff, sizeof(char), block_size, fp);
		fwrite(buff, sizeof(char), block_size, wfp);
		ops += 2;
		left -= block_size;
	}
	free(buff);
	fclose(fp);
	fclose(wfp);
}

void read_sequential(int processes, int block_size) {
	start = clock();
	if (processes == 1) {
		read_help("testfiles/onethousand1.txt", block_size);
	} else if (processes == 2) {
		if (fork() == 0) {
                	read_help("testfiles/fivehundred1.txt", block_size);
                        exit(0);
		} else {
			read_help("testfiles/fivehundred2.txt", block_size);
                        wait(NULL);
		}
	} else if (processes == 4) {
		if (fork() == 0) {
			if (fork() == 0) {
                        	read_help("testfiles/twohundredfifty1.txt", block_size);
			       	exit(0);
			} else {
				read_help("testfiles/twohundredfifty2.txt", block_size);
				exit(0);
                       	}
		} else {
			if (fork() == 0) {
                                read_help("testfiles/twohundredfifty3.txt", block_size);
               		        exit(0);
                       	} else {
                                read_help("testfiles/twohundredfifty4.txt", block_size);
                                wait(NULL);
				wait(NULL);
				wait(NULL);
                        	}
			}
	} else if (processes == 8) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        read_help("testfiles/onehundredtwentyfive1.txt", block_size);
                                        exit(0);
                                } else {
 					read_help("testfiles/onehundredtwentyfive2.txt", block_size);                                       
 					exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        read_help("testfiles/onehundredtwentyfive3.txt", block_size);
                                        exit(0);
                                } else {
                                        read_help("testfiles/onehundredtwentyfive4.txt", block_size);
                                        exit(0);
                                }
                        }
		} else {
			if (fork() == 0) {
                                if (fork() == 0) {
                                        read_help("testfiles/onehundredtwentyfive5.txt", block_size);
                                        exit(0);
                                } else {
					read_help("testfiles/onehundredtwentyfive6.txt", block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        read_help("testfiles/onehundredtwentyfive7.txt", block_size);
                                        exit(0);
                                } else {
                                        read_help("testfiles/onehundredtwentyfive8.txt", block_size);
                                        wait(NULL);
					wait(NULL);
					wait(NULL);
					wait(NULL);
					wait(NULL);
					wait(NULL);
					wait(NULL);
                                }
                        }
		}       
	}
	end = clock();
}

void read_random(int processes, int block_size) {
	start = clock();
        if (processes == 1) {
                read_help_random("testfiles/onethousand1.txt", 1000000000, block_size);
        } else if (processes == 2) {
                if (fork() == 0) {
                        read_help_random("testfiles/fivehundred1.txt", 500000000, block_size);
                        exit(0);
                } else {
                        read_help_random("testfiles/fivehundred2.txt", 500000000, block_size);
                        wait(NULL);
                }
        } else if (processes == 4) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                read_help_random("testfiles/twohundredfifty1.txt", 250000000, block_size);
                                exit(0);
                        } else {
                                read_help_random("testfiles/twohundredfifty2.txt", 250000000, block_size);
                                exit(0);
                        }
                } else {
                        if (fork() == 0) {
                                read_help_random("testfiles/twohundredfifty3.txt", 250000000, block_size);
                                exit(0);
                        } else {
                                read_help_random("testfiles/twohundredfifty4.txt", 250000000, block_size);
                                wait(NULL);
                                wait(NULL);
                                wait(NULL);
                                }
                        }
	} else if (processes == 8) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        read_help_random("testfiles/onehundredtwentyfive1.txt", 125000000, block_size);
                                        exit(0);
                                } else {
                                        read_help_random("testfiles/onehundredtwentyfive2.txt", 125000000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        read_help_random("testfiles/onehundredtwentyfive3.txt", 125000000, block_size);
                                        exit(0);
                                } else {
                                        read_help_random("testfiles/onehundredtwentyfive4.txt", 125000000, block_size);
                                        exit(0);
                                }
                        }
                } else {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        read_help_random("testfiles/onehundredtwentyfive5.txt", 125000000, block_size);
                                        exit(0);
                                } else {
                                        read_help_random("testfiles/onehundredtwentyfive6.txt", 125000000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        read_help_random("testfiles/onehundredtwentyfive7.txt", 125000000, block_size);
                                        exit(0);
                                } else { 
                                        read_help_random("testfiles/onehundredtwentyfive8.txt", 125000000, block_size);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                }
                        }
                }
        }
        end = clock();
}

void write_sequential(int processes, int block_size) {
        start = clock();
        if (processes == 1) {
                write_help("testfiles/onethousand1.txt", block_size);
        } else if (processes == 2) {
                if (fork() == 0) {
                        write_help("testfiles/fivehundred1.txt", block_size);
                        exit(0);
                } else {
                        write_help("testfiles/fivehundred2.txt", block_size);
                        wait(NULL);
                }
        } else if (processes == 4) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                write_help("testfiles/twohundredfifty1.txt", block_size);
                                exit(0);
                        } else {
                                write_help("testfiles/twohundredfifty2.txt", block_size);
                                exit(0);
			}
                } else {
                        if (fork() == 0) {
                                write_help("testfiles/twohundredfifty3.txt", block_size);
                                exit(0);
                        } else {
                                write_help("testfiles/twohundredfifty4.txt", block_size);
                                wait(NULL);
                                wait(NULL);
                                wait(NULL);
                                }
                        }
	} else if (processes == 8) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        write_help("testfiles/onehundredtwentyfive1.txt", block_size);
                                        exit(0);
                                } else {
                                        write_help("testfiles/onehundredtwentyfive2.txt", block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        write_help("testfiles/onehundredtwentyfive3.txt", block_size);
                                        exit(0);
                                } else {
                                        write_help("testfiles/onehundredtwentyfive4.txt", block_size);
                                        exit(0);
                                }
                        }
                } else {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        write_help("testfiles/onehundredtwentyfive5.txt", block_size);
                                        exit(0);
                                } else {
                                        write_help("testfiles/onehundredtwentyfive6.txt", block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        write_help("testfiles/onehundredtwentyfive7.txt", block_size);
                                        exit(0);
                                } else {
                                        write_help("testfiles/onehundredtwentyfive8.txt", block_size);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                }
                        }
                }
        }
        end = clock();
}

void write_random(int processes, int block_size) {
	start = clock();
	if (processes == 1) {
                write_help_random("testfiles/onethousand1.txt", 1000000000, block_size);
        } else if (processes == 2) {
                if (fork() == 0) {
                        write_help_random("testfiles/fivehundred1.txt", 500000000, block_size);
                        exit(0);
                } else {
                        write_help_random("testfiles/fivehundred2.txt", 500000000, block_size);
                        wait(NULL);
                }
        } else if (processes == 4) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                write_help_random("testfiles/twohundredfifty1.txt", 250000000, block_size);
                                exit(0);
                        } else {
                                write_help_random("testfiles/twohundredfifty2.txt", 250000000, block_size);
                                exit(0);
                        }
                } else {
                        if (fork() == 0) {
                                write_help_random("testfiles/twohundredfifty3.txt", 250000000, block_size);
                                exit(0);
                        } else {
                                write_help_random("testfiles/twohundredfifty4.txt", 250000000, block_size);
                                wait(NULL);
                                wait(NULL);
                                wait(NULL);
                                }
                        }
        } else if (processes == 8) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        write_help_random("testfiles/onehundredtwentyfive1.txt", 125000000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/onehundredtwentyfive2.txt", 125000000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        write_help_random("testfiles/onehundredtwentyfive3.txt", 125000000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/onehundredtwentyfive4.txt", 125000000, block_size);
                                        exit(0);
                                }
                        }
                } else {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        write_help_random("testfiles/onehundredtwentyfive5.txt", 125000000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/onehundredtwentyfive6.txt", 125000000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        write_help_random("testfiles/onehundredtwentyfive7.txt", 125000000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/onehundredtwentyfive8.txt", 125000000, block_size);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                }
                        }
                }
	}
	end = clock();
}

void read_random_small(int processes, int block_size) {
        start = clock();
        if (processes == 1) {
                read_help_random("testfiles/fourmb1.txt", 4000000, block_size);
        } else if (processes == 2) {
                if (fork() == 0) {
                        read_help_random("testfiles/twomb1.txt", 2000000, block_size);
                        exit(0);
                } else {
                        read_help_random("testfiles/twomb2.txt", 2000000, block_size);
                        wait(NULL);
                }
        } else if (processes == 4) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                read_help_random("testfiles/onemb1.txt", 1000000, block_size);
                                exit(0);
                        } else {
                                read_help_random("testfiles/onemb2.txt", 1000000, block_size);
                                exit(0);
                        }
                } else {
                        if (fork() == 0) {
                                read_help_random("testfiles/onemb3.txt", 1000000, block_size);
                                exit(0);
                        } else {
                                write_help_random("testfiles/onemb4.txt", 1000000, block_size);
                                wait(NULL);
                                wait(NULL);
                                wait(NULL);
                                }
                        }
        } else if (processes == 8) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        read_help_random("testfiles/halfmb1.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        read_help_random("testfiles/halfmb2.txt", 500000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        read_help_random("testfiles/halfmb3.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        read_help_random("testfiles/halfmb4.txt", 500000, block_size);
                                        exit(0);
                                }
                        }
                } else {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        read_help_random("testfiles/halfmb5.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        read_help_random("testfiles/halfmb6.txt", 500000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        read_help_random("testfiles/halfmb7.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        read_help_random("testfiles/halfmb8.txt", 500000, block_size);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                }
                       }
                }
        }
        end = clock();
}

void write_random_small(int processes, int block_size) {
        start = clock();
        if (processes == 1) {
                write_help_random("testfiles/fourmb1.txt", 4000000, block_size);
        } else if (processes == 2) {
                if (fork() == 0) {
                        write_help_random("testfiles/twomb1.txt", 2000000, block_size);
                        exit(0);
                } else {
                        write_help_random("testfiles/twomb2.txt", 2000000, block_size);
                        wait(NULL);
                }
        } else if (processes == 4) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                write_help_random("testfiles/onemb1.txt", 1000000, block_size);
                                exit(0);
                        } else {
                                write_help_random("testfiles/onemb2.txt", 1000000, block_size);
                                exit(0);
                        }
                } else {
                        if (fork() == 0) {
                                write_help_random("testfiles/onemb3.txt", 1000000, block_size);
                                exit(0);
                        } else {
                                write_help_random("testfiles/onemb4.txt", 1000000, block_size);
                                wait(NULL);
                                wait(NULL);
                                wait(NULL);
                                }
                        }
        } else if (processes == 8) {
                if (fork() == 0) {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        write_help_random("testfiles/halfmb1.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/halfmb2.txt", 500000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        write_help_random("testfiles/halfmb3.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/halfmb4.txt", 500000, block_size);
                                        exit(0);
                                }
                        }
                } else {
                        if (fork() == 0) {
                                if (fork() == 0) {
                                        write_help_random("testfiles/halfmb5.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/halfmb6.txt", 500000, block_size);
                                        exit(0);
                                }
                        } else {
                                if (fork() == 0) {
                                        write_help_random("testfiles/halfmb7.txt", 500000, block_size);
                                        exit(0);
                                } else {
                                        write_help_random("testfiles/halfmb8.txt", 500000, block_size);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                        wait(NULL);
                                }
			}
		}
	}
	end = clock();
}
