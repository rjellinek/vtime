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
#define ITERATIONS 190
#define OUTPUT 64
#define MB 1048576

unsigned long long int rdtsc(){

	unsigned long long a, d;

	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return ((unsigned long long) a) | (((unsigned long long) d) << 32);
}


main(int argc, const char* argv[]){

	if (argc < 2) {
		exit(1);
	}

	unsigned long long tick_start, tick_stop, dup_start, dup_stop;
	char output[OUTPUT];
	int amount_read = 0;
	char * buffer;
	int offset = 0;

	double freq =  2.8 * pow(10.0, 9);

	int fd = open("../data", O_RDONLY);
	
	char result_filename[14];
	sprintf(result_filename, "results/run%d", atoi(argv[1]));
	
	int results = open(result_filename, O_CREAT | O_RDWR | O_APPEND, 0644);

//	int size_in_mb = atoi(argv[2]) * MB;

	// read in chunks of step MB
	int step = 32;

	int i = 1;
	for(i; i <= ITERATIONS; i++){
		//long blocks = (long)(((step * i) * MB) / SIZE);
		//printf("step: %d\ni: %d\nMB=%d\nSIZE=%d\nTotal=%ld\n\n", step, i, MB, SIZE, (long)step*i*MB/SIZE);
		buffer = (char *)malloc(SIZE);
	
		// read it in the first time to make sure that it is in the cache	
		lseek(fd, 0, SEEK_SET);
		tick_start = rdtsc();
		int k = 0;
		// read from byte zero up until i * step megabytes
		// doing so in 1 block increments
		for(k; k < (long)step*i*MB/SIZE; k++){
			read(fd, buffer, SIZE);
		}
		tick_stop = rdtsc();
		
		// wait to guarantee its there	
		//sleep(1);

		// read the data again, if this read takes a long time
		// then that means the first blocks got pushed out of the cache
		k = 0;
		lseek(fd, 0, SEEK_SET);
		dup_start = rdtsc();
		for( k; k < (long)step*i*MB/SIZE; k++){
			read(fd, buffer, SIZE);
		}
		dup_stop = rdtsc();

		free(buffer);

		double time = ((dup_stop - dup_start) / freq) * pow(10.0, 3);

		sprintf(output, "%d %f\n", step * i, time);
//		printf("%s", output);
		write(results, output, strlen(output));
	}

	close(results);
	close(fd);
}
