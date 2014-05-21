#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "List.h"              /* Doubly-linked list ADT */

#define MAX_SIZE 134217728     /* This is 2^27, or 128 MiB, indicating the maximum allowable allocation */

int exit_set = 0;              /* Indicates if atexit() has been called for this program yet, default is 0 */
ListRef list = NULL;           /* Initializes a pointer to a ListRef object, to be allocated and used to track memory statistics */

void slug_memstats(void);      /* Forward declaration for use in slug_malloc */


/*******************************************************************/
void *slug_malloc (size_t size, char *WHERE){
  void* address;

  /* If atexit() hasn't been set for this program, call it */
  if (exit_set == 0 ) { 
    exit_set = 1; 
    atexit(slug_memstats);
  }

    /* If we're mallocing something of size 0, indicate to the user that something might be wrong */
  if (size == 0){
    fprintf(stderr, "Warning: Malloc of size 0 performed, this might suggest a bug in your program.\n");
  }

  /* Enforce maximum allocation size restriction */
  if (size >= MAX_SIZE){ 
    fprintf(stderr, "Allocation too large, allocations must less than 128 MiB.\n");
    exit (1);
  }

  /* allocate the memory */
  address = malloc(size);

  /* If malloc failed, indicate so */
  if(size != 0){
     if(address == NULL){
        fprintf(stderr, "Malloc failed in slug_malloc at %s\n", WHERE);
        return address;
     }
  }

  /* If the list has not been created/initialized yet, do so */
  if(list == NULL){
    list = newList();
  }

  /* Insert a record for this allocation into our linked-list */
  insertNewMemoryRecord(list, address, WHERE, size);

  return address;
}

/*******************************************************************/
void slug_free (void *addr, char *WHERE){
  int check; 

  /* check to see if freeing is a valid manuever here */
  check = isAllocated(list, addr);

  /* check all the possible results of the check */
  switch(check){

    /* if 0, then the address is valid */
    case 0: free(addr);
            break;

    /* if 1, then generic bad free attempt */
    /* print an error indicating such and exit the program */
    case 1: fprintf(stderr, "Tried to free unallocated memory location %p at %s\n", addr, WHERE);
            exit(1);

    /* if 2, then this looks like an attempt to double free memory */
    /* print an error indicating such and exit the program */
    case 2: fprintf(stderr, "Tried to free already free memory %p at %s\n", addr, WHERE);
            exit (1);

    /* if 3, then attempt to free using an address inside an allocated rarea */
    /* print an error indicating such and exit the program */
    case 3: fprintf(stderr, "Tried to free using a pointer inside a chunk of memory using address %p at %s\n",
                    addr, WHERE);
            exit(1);
    
    /* required default that can't be reached */
    default: break;
  }
}

/*******************************************************************/
void slug_memstats (void){
  listPrintMemstats(list);
}
