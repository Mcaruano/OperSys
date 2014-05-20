#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "List.h"

#define MAX_SIZE 134217728     /* this is 2^27, or 128 MiB */

int exit_val = 0; 

ListRef list = NULL;

void slug_memstats(void);

void *slug_malloc ( size_t size, char *WHERE ){

   if (exit_val == 0 ) { 
      exit_val = 1; 
      atexit (slug_memstats);
   }

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

   insertNewNode(list, address, WHERE, size);
   
   return address;
}

void slug_free ( void *addr, char *WHERE ){
   printf("The address that called slug_free is: %p\n", addr);
   int check; 
   check = is_allocated(list, addr);
   switch (check) {
      case 0: printf("The address that is being freed is: %p\n", addr);
              free(addr);
              break;
      case 1: fprintf(stderr, "Tried to free unallocated memory location %p at %s\n", addr, WHERE);
              exit(1);
      case 2: fprintf(stderr, "Tried to free already free memory %p at %s\n", addr, WHERE);
              exit (1);
              break;
      default: break;
  }
}

void slug_memstats ( void ){
   print_list_alloc(list);
}
