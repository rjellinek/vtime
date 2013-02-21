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

	// file that needs to be open for writing to
	int fd = open("creation", O_CREAT | O_WRONLY, 0644);
	
	// file to output the results
	char result_filename[14];
	sprintf(result_filename, "results/run%d", atoi(argv[1]));
	int results = open(result_filename, O_CREAT | O_RDWR, 0644);

	// loop through the buffer making it 4096 (1 block) long	
/*	int k = 0;
	for(k; k < BLOCK_SIZE; k++){
		buffer[k] = 'a';
	}
*/

	int data = open("../data", O_RDONLY);
	read(data, buffer, BLOCK_SIZE);

	int i = 0;
	for(i; i < 16; i++){
		// read in data to be written out

		lseek(fd, 0, SEEK_SET);

		tick_start = rdtsc();
		int k = 0;
		for(k; k < (i+1); k++){
			write(fd, buffer, BLOCK_SIZE);
		}
		fsync(fd);
		tick_stop = rdtsc();

		// result in microseconds
		double time = ((tick_stop - tick_start) / freq) * pow(10.0, 6);
		
		// the output is which block was just written and how long it took
		sprintf(output, "%3d %f\n", ((i+1)), time);
		write(results, output, strlen(output));
	}
	close(fd);
	close(results);
	close(data);
}
