#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 4096
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
	char buffer[SIZE];
	char output[OUTPUT];

	double freq =  2.8 * pow(10.0, 9);

	// file that needs to be open for writing to
	int fd = open("/media/48a48b22-9e99-40b7-9efd-21cfb34fb0c5/creation", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	// file to output the results
	char result_filename[14];
	sprintf(result_filename, "results/run%d", atoi(argv[1]));
	int results = open(result_filename, O_CREAT | O_RDWR, 0644);

	// loop through the buffer making it 4096 (1 block) long	
/*	int k = 0;
	for(k; k < SIZE; k++){
		buffer[k] = 'a';
	}
*/

	int data = open("../data", O_RDONLY);

	int i = 0;
	for(i; i < 16; i++){

		read(data, buffer, SIZE);

		tick_start = rdtsc();
		write(fd, buffer, SIZE);
		fsync(fd);
		tick_stop = rdtsc();

		double time = ((tick_stop - tick_start) / freq) * pow(10.0, 6);
		
		// the output is which block was just written and how long it took
		sprintf(output, "%3d %f\n", ((i+1)), time);
//		printf("%s", output);
		write(results, output, strlen(output));
	}
	close(fd);
	close(results);
	close(data);
}
