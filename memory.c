#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "List.h"

/*int main(int argc, char *argv[])
{
    /*Maybe use this main function to test*//*
	return 0;
}*/

#define MAX_SIZE 134217728     /* this is 2^27, or 128 MiB */

ListRef list = NULL;
struct timeval init_time;
init_time->tv_sec = 0;
init_time->tv_usec = 0;

void *slug_malloc ( size_t size, char *WHERE ){
   
   double ticks = init_time.tv_sec + init_time.tv_usec * 1e-6;
   printf("slug_malloc init_time: %f\n", ticks);

   if(list == NULL){
      /* record initial timestamp */
      gettimeofday(&init_time, NULL);
      list = newList();
   }
   
   if (size == 0 ) {
      fprintf(stderr,  "This an unusual operation!\n");
   }
   
   if (size >= MAX_SIZE) { 
      fprintf(stderr,  "Allocation too large!\n");
      exit (1);
   }

   insertAfterLast_test(list, init_time, WHERE, size);
   
   printf("%s\n", WHERE);
   return malloc(size);
}

void slug_free ( void *addr, char *WHERE ){
   
}

void slug_memstats ( void ){
   print_list_alloc(list);
}
