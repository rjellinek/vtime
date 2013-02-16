#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#define SIZE 4096
#define OUTPUT 64
#define MB 1048576

unsigned long long int rdtsc(){

	unsigned long long a, d;

	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return ((unsigned long long) a) | (((unsigned long long) d) << 32);
}


main(int argc, const char* argv[]){

	if (argc < 2) {
		printf("usage: ./prefetch <result file number>");
		exit(1);
	}

	unsigned long long base_start, base_stop;
	unsigned long long tick_start, tick_stop;
	char * buffer;
	char output[OUTPUT];
	
	int base = 0;	
	double freq =  2.8 * pow(10.0, 9);
	
	char result_filename[10];
	sprintf(result_filename, "results/run%d", atoi(argv[1]));

	int fd = open("../data", O_RDONLY);
	int results = open(result_filename, O_CREAT | O_APPEND | O_RDWR, 0644);

	buffer = (char *)malloc(SIZE);
	
	srand(time(NULL));
	base = rand() % 1000;	

	// start at a random block
	lseek(fd, base * SIZE, SEEK_SET);

	// read a block to engage the prefetching
//	read(fd, buffer, SIZE);

	// sleep to ensure prefetched data is in the cache
//	sleep(1);

	int i = 1;
	for(i; i <= 200; i++){

		//buffer = (char *)malloc(SIZE);
		//lseek(fd, i * SIZE, SEEK_CUR);

		tick_start = rdtsc();
		read(fd, buffer, SIZE);
		tick_stop = rdtsc();
		double time = ((tick_stop - tick_start) / freq) * pow(10.0, 6);
		// output is in number of blocks (4K each)
		// think it should be 32 blocks between prefetches
		sprintf(output, "%3d %f\n", i, time);
		write(results, output, strlen(output));
	}

	free(buffer);		
	close(results);
	close(fd);
}
