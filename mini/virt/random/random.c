#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


#define SIZE 4096
#define OUTPUT 64
#define STEP 512

unsigned long long int rdtsc(){

	unsigned long long a, d;

	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return ((unsigned long long) a) | (((unsigned long long) d) << 32);
}


main(int argc, const char* argv[]){

	if (argc < 2) {
		printf("usage: random <result file number>");
		exit(1);
	}

	unsigned long long tick_start, tick_stop, dup_start, dup_stop;
	char output[OUTPUT];
	char * buffer;
	int offset = 0;
	char result_filename[10];

	sprintf(result_filename, "results/run%d", atoi(argv[1]));

	int fd = open("../data", O_RDONLY);
	if(fd < 0){
		printf("Could not open data\n");
		exit(1);
	}
	int results = open(result_filename, O_CREAT | O_RDWR, 0644);

	double freq =  2.8 * pow(10.0, 9);

	srand(time(NULL));

	// pick starting block randomly from
	// first 1000 blocks
	int base = rand() % 1000;	
	base = (base * 4096) - 1;

	int i = 0;
	for(i; i < 20; i++){	
		buffer = (char *)malloc(1);

		// move pointer by step amount of bytes
		// subtract since reading backwards to counteract
		// possible prefetching. 
		lseek(fd, base - (i * STEP), SEEK_SET);

		tick_start = rdtsc();
		read(fd, buffer, 1);
		tick_stop = rdtsc();

		free(buffer);

		double time = ((tick_stop - tick_start) / freq) * pow(10.0, 6);

		sprintf(output, "%d %f\n", i*STEP, time);
		write(results, output, strlen(output));
	}

	close(results);
	close(fd);
}
