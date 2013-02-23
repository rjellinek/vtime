#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 4096
#define OUTPUT 512
#define FREQ 1.59615e9

unsigned long long int rdtsc(){

	unsigned long long a, d;

	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return ((unsigned long long) a) | (((unsigned long long) d) << 32);
}


main(int argc, const char *argv[]){

	if (argc < 2){
		exit(1);
	}

	unsigned long long tick_start, tick_stop;
	char buffer[BLOCK_SIZE];
	char output[OUTPUT];

	//double freq =  2.8 * pow(10.0, 9);
    double freq = FREQ;

	// file to output the results
	char result_filename[14];
	sprintf(result_filename, "results/run%d", atoi(argv[1]));
	int results = open(result_filename, O_CREAT | O_RDWR, 0644);

	int rdfd = open("./file", O_RDONLY | O_SYNC | O_DIRECT);
    struct stat *statbuf = malloc(sizeof(struct stat));
    if (statbuf == NULL) {
        fprintf(stderr, "Error: malloc statbuf\n\n");
        exit(1);
    }

	int i = 0, j;
	for(i; i < 16; i++){
        
        lseek(rdfd, 0, SEEK_SET);
        fstat(rdfd, statbuf);

		tick_start = rdtsc();
 //       for (j = 0; j <= i; j++) {
            read(rdfd, buffer, BLOCK_SIZE);
 //       }
		tick_stop = rdtsc();

		// result in microseconds
		double time = ((tick_stop - tick_start) / freq) * pow(10.0, 6);
		
		// the output is which block was just written and how long it took
		sprintf(output, "%3d %f\n", ((i+1)), time);
		write(results, output, strlen(output));
	}
    //free(statbuf);
	close(results);
	close(rdfd);
}
