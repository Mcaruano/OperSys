#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "List.h"

#define MAX_SIZE 134217728     /* this is 2^27, or 128 MiB */

ListRef list = NULL;

void *slug_malloc ( size_t size, char *WHERE ){
   
   void* address = malloc(size);
   if(address == NULL)
   {
      fprintf(stderr, "Malloc failed in slug_malloc at %s\n", WHERE);
      return address;
   }

   printf("The address that called slug_malloc is: %p\n", address);

   if(list == NULL){
      list = newList();
   }
   
   if (size == 0 ) {
      fprintf(stderr, "This is an atypical operation!\n");
   }
   
   if (size >= MAX_SIZE) { 
      fprintf(stderr, "Allocation too large!\n");
      exit (1);
   }

   insertAfterLast_test(list, address, WHERE, size);
   
   return address;
}

void slug_free ( void *addr, char *WHERE ){
   printf("The address that called slug_free is: %p\n", addr);

   if (is_allocated(list, addr)){
      printf("The address that is being freed is: %p\n", addr);
      free(addr);
   }

   else {
      fprintf(stderr, "Tried to free unallocated memory location %p at %s\n", addr, WHERE);
      exit(1);
   }
}

void slug_memstats ( void ){
   print_list_alloc(list);
}
