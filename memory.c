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

  address = malloc(size);

  /* If malloc failed, indicate so */
  if(address == NULL){
    fprintf(stderr, "Malloc failed in slug_malloc at %s\n", WHERE);
    return address;
  }

  /* If the list has not been created/initialized yet, do so */
  if(list == NULL){
    list = newList();
  }

  /* TODO: THIS CODE NEVER GETS EXECUTED, ANY MALLOC OF SIZE 0 RETURNS NULL AND IS CAUGHT BY address==NULL above */
  /* If we're mallocing something of size 0, indicate to the user that something might be wrong */
  if (size == 0){
    fprintf(stderr, "Warning: Malloc of size 0 performed, this might suggest a bug in your program.\n");
  }

  /* Enforce maximum allocation size restriction */
  if (size >= MAX_SIZE){ 
    fprintf(stderr, "Allocation too large!\n");
    exit (1);
  }

  /* Insert a record for this allocation into our linked-list */
  insertNewMemoryRecord(list, address, WHERE, size);

  return address;
}

/*******************************************************************/
void slug_free (void *addr, char *WHERE){
  int check; 
  check = isAllocated(list, addr);

  switch(check){
    case 0: free(addr);
            break;
    case 1: fprintf(stderr, "Tried to free unallocated memory location %p at %s\n", addr, WHERE);
            exit(1);
    case 2: fprintf(stderr, "Tried to free already free memory %p at %s\n", addr, WHERE);
            exit (1);
            break;
    default: break;
  }
}

/*******************************************************************/
void slug_memstats (void){
  listPrintMemstats(list);
}
