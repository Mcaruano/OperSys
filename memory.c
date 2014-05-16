#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/*int main(int argc, char *argv[])
{
    /*Maybe use this main function to test*//*
	return 0;
}*/
	
#define MAX_SIZE 134217728

void *slug_malloc ( size_t size, char *WHERE ){
	
	struct timeval tv;
	int err; 
	double ticks; 
	err = gettimeofday(&tv, NULL);
	if (!err){
		ticks = tv.tv_sec + tv.tv_usec * 1e-6;
		printf ("time is %f \n", ticks);

	}

	if (size == 0 ) {
		fprintf(stderr,  "This an unusual operation!\n");
	}

	if (size >= MAX_SIZE) { 
		fprintf(stderr,  "Allocation too large!\n");
		exit (1);
	}

	printf("%s\n", WHERE);
	return malloc(size);
}

void slug_free ( void *addr, char *WHERE ){

}

void slug_memstats ( void ){

}