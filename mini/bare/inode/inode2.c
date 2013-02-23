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

    double freq =  2.8 * pow(10.0, 9);

	// file to output the results
	char result_filename[14];
	sprintf(result_filename, "results/run%d", atoi(argv[1]));
	int results = open(result_filename, O_CREAT | O_RDWR, 0644);
	int rdfd = open("/dev/urandom", O_RDONLY);
    int wrfd = open("./outfile", O_CREAT | O_TRUNC | O_WRONLY | O_DIRECT, 0644);
    int scratchfd = open("./scratch", O_CREAT | O_TRUNC | O_WRONLY | O_DIRECT, 0644);
    //struct stat *statbuf = malloc(sizeof(struct stat));
    
	int i, j;
	for(i = 0; i < 16; i++){
        
        // write to start of the write file we're timing
        lseek(wrfd, 0, SEEK_SET);

        // read the random data we're going to write
        read(rdfd, buffer, BLOCK_SIZE);

        // write to some scratch file  -- necessary??
        write(scratchfd, buffer, BLOCK_SIZE);
        fsync(scratchfd);

        // read into buffer again
        read(rdfd, buffer, BLOCK_SIZE);
	
        // fill write buffer we care about
        for (j = 0; j <= i; j++) {
            write(wrfd, buffer, BLOCK_SIZE);
        }

        // time write
        tick_start = rdtsc();
		fsync(wrfd);
		tick_stop = rdtsc();

		// result in microseconds
		double time = ((tick_stop - tick_start) / freq) * pow(10.0, 6);
		
		// the output is which block was just written and how long it took
		sprintf(output, "%3d %f\n", ((i+1)), time);
		write(results, output, strlen(output));
		
		// necessary?
		fsync(results);
	}
    //free(statbuf);
    close(scratchfd);
	close(results);
	close(rdfd);
	close(wrfd);
}
