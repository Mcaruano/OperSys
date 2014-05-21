/* 
//FILE: List.c
//AUTHOR: Matt Caruano
//VERSION: Rev1 - 05-26-2013 (Fixed some memory issues)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#include "List.h"

/***************** Struct Declarations *****************/
typedef struct Node
{
  long data;
  int count;

  /* Data tracked for memory statistics */
  int allocated_size;    /* space allocated with malloc */
  struct timeval tv;     /* time of the allocation */
  void* address;         /* address of the beginning of allocated region */
  char* file_and_line;   /* file name and line number of malloc call */
  int in_use;            /* Returns various numbers to indicate state */
  /* End new data section */

  struct Node* prev;
  struct Node* next;
} NodeType;
/*********************************************/
typedef struct ListHdr
{
  NodeType* first;
  NodeType* last;
  NodeType* current;
} ListType;
/*********************************************/
typedef struct List
{
  ListType* header;
  int length;
} List;
/*********************************************/



/***************** Constructors/Destructors *****************/
ListRef newList(void)
{
  ListRef newL;
  /* Allocate space for the List struct */
  newL = malloc(sizeof(List));
  /* Initialize length of the list to 0 */
  newL->length = 0;

  /* Allocate space for the ListHdr struct within the List struct */
  newL->header = malloc(sizeof(ListType));

   /* Initialize all ListHdr pointers to NULL */
  newL->header->first = NULL;
  newL->header->current = NULL;
  newL->header->last = NULL;     
          
  return newL;
}
/*********************************************/
void freeList(ListRef* pL)
{
  ListRef L;
  ListType* temp;

  L = *pL;

  /* Free the nodes */
  makeEmpty(L);
  /* Free the Header struct */
  temp = L->header;
  free(temp);   
  /* Free the List struct */
  free(L);
}
/*********************************************/


/********************** Access Functions **********************/
int isEmpty(ListRef L)
{
  /* If the length is 0, then the List is empty */
  if(L->length == 0)
    return 1;    
  else
    return 0;
}
/*********************************************/
int offEnd(ListRef L)
{
  if(L->header->current == NULL)
    return 1;         
  else
    return 0;
}
/*********************************************/
int atFirst(ListRef L)
{
  /* If the current node is the first node, return True */
  if(L->header->current == L->header->first)
    return 1;   
  else
    return 0;
}
/*********************************************/
int atLast(ListRef L)
{
  /* If the current node is the last node, return True */
  if(L->header->current == L->header->last)
    return 1;   
  else
    return 0;
}
/*********************************************/
long getFirst(ListRef L)
{
  return L->header->first->data;
}
/*********************************************/
long getCurrent(ListRef L)
{
  return L->header->current->data;
}
/*********************************************/
long getLast(ListRef L)
{
  return L->header->last->data;
}
/*********************************************/
int getLength(ListRef L)
{
  return L->length;   
}
/*********************************************/
int equals(ListRef A, ListRef B)
{
  long nodeDataA;
  long nodeDataB; 
  NodeType* iteratorA;
  NodeType* iteratorB;
  int counter;
  int i;

  /* Compare the lengths, if not the same then they can't be equal */
  if(A->length != B->length)
    return 0;
     
  /* Initialize an iterator pointer to be used in the loop */
  iteratorA = A->header->first;
  iteratorB = B->header->first;
  /* Initialize the variable for the loop invariant, as well as the counter */
  counter = A->length;

  /* Compare each element */
  for(i = 0; i < counter; i++)
  {
    /* Get the data of each node */
    nodeDataA = iteratorA->data;
    nodeDataB = iteratorB->data;                        
    /* If they aren't equal, return false */
    if(nodeDataA != nodeDataB)
      return 0;
    /* Move the iterators to the next element */
    iteratorA = iteratorA->next;
    iteratorB = iteratorB->next;
  }
     
  /* If the function gets to this point, they are equal */
  return 1;
}
/*********************************************/


/****************** Manipulation Procedures ******************/
void makeEmpty(ListRef L)
{
  /* Initialize the variable for the loop invariant, as well as the counter */
  int counter;
  int i;  

  counter = L->length;    
    
  for(i = 0; i < counter; i++)
  {
    deleteFirst(L);
  }        
}
/*********************************************/
void moveFirst(ListRef L)
{
  L->header->current = L->header->first;     
}
/*********************************************/
void moveLast(ListRef L)
{
  L->header->current = L->header->last;     
}
/*********************************************/
void movePrev(ListRef L)
{
  if(atFirst(L))
  {
    L->header->current = NULL;
    return;
  }

  else   
    L->header->current = L->header->current->prev;     
}
/*********************************************/
void moveNext(ListRef L)
{
  if(atLast(L))
  {
    L->header->current = NULL;
    return;
  }

  else      
    L->header->current = L->header->current->next;     
}
/*********************************************/
void insertBeforeFirst(ListRef L, long data)
{
  /* Declare the new node, allocate space for it, and give it the data */
  NodeType* newNode;

  newNode = malloc(sizeof(NodeType));
  newNode->data = data;
  newNode->count = 1;

  /* If there are no nodes on the list at all, make all header pointers */
  /* point to newNode, and set newNode's pointers to NULL */
  if(L->length == 0)
  {
    L->header->first = newNode;
    L->header->current = newNode;
    L->header->last = newNode;
      
    newNode->prev = NULL;
    newNode->next = NULL;
  }

  else
  {
    /* Set newNode's pointers properly to make it the first element */
    newNode->prev = NULL;
    newNode->next = L->header->first;
    /* Set the pre-existing first element's prev pointer to newNode */
    L->header->first->prev = newNode;
    /* Update the first node in the ListHdr object */
    L->header->first = newNode;
    /* Also make the newNode the current element */
    L->header->current = newNode;
  }
     
  /* Increment the length of the list regardless */
  L->length++;
}
/*********************************************/
void insertAfterLast(ListRef L, long data)
{
  /* Declare the new node, allocate space for it, and give it the data */
  NodeType* newNode;

  newNode = malloc(sizeof(NodeType));
  newNode->data = data;
  newNode->count = 1;

  /* If there are no nodes on the list at all, make all header pointers */
  /* point to newNode, and set newNode's pointers to NULL */
  if(L->length == 0)
  {
    L->header->first = newNode;
    L->header->current = newNode;
    L->header->last = newNode;
      
    newNode->prev = NULL;
    newNode->next = NULL;
  }

  else
  {
    /* Set newNode's pointers properly to make it the last element */
    newNode->prev = L->header->last;
    newNode->next = NULL;
    /* Set the pre-existing last element's next pointer to newNode */
    L->header->last->next = newNode;
    /* Update the last node in the ListHdr object */
    L->header->last = newNode;
    /* Also make the newNode the current element */
    L->header->current = newNode;
  }
     
  /* Increment the length of the list regardless */
  L->length++;
}
/*********************************************/
void insertBeforeCurrent(ListRef L, long data)
{
  NodeType* newNode;

  if(atFirst(L))
  {
    insertBeforeFirst(L, data);
    return;
  }

  /* Declare the new node, allocate space for it, and give it the data */
  newNode = malloc(sizeof(NodeType));
  newNode->data = data;
  newNode->count = 1;

  /* If there are no nodes on the list at all, make all header pointers */
  /* point to newNode, and set newNode's pointers to NULL */
  if(L->length == 0)
  {
    L->header->first = newNode;
    L->header->current = newNode;
    L->header->last = newNode;
      
    newNode->prev = NULL;
    newNode->next = NULL;
  }    
        
  else
  {
    /* Make newNode's next pointer point to current */
    newNode->next = L->header->current;
    /* Make newNode's prev pointer point to node before current */
    newNode->prev = L->header->current->prev;
    /* Make the node before current's next pointer point to newNode */
    L->header->current->prev->next = newNode;
    /* Make current's prev pointer point to newNode */
    L->header->current->prev = newNode;           
  }


  /* Set newNode as the new current node */
  L->header->current = newNode; 
    
  /* Increment the length of the list regardless */
  L->length++;
}
/*********************************************/
void insertAfterCurrent(ListRef L, long data)
{
  /* Declare the new node, allocate space for it, and give it the data */
  NodeType* newNode;

  newNode = malloc(sizeof(NodeType));
  newNode->data = data;
  newNode->count = 1;

  /* If there are no nodes on the list at all, make all header pointers */
  /* point to newNode, and set newNode's pointers to NULL */
  if(L->length == 0)
  {
    L->header->first = newNode;
    L->header->current = newNode;
    L->header->last = newNode;
      
    newNode->prev = NULL;
    newNode->next = NULL;
  }

  if(atLast(L))
  {
    /* Make newNode's next pointer point to NULL */
    newNode->next = NULL;
    /* Make newNode's prev pointer point to current */
    newNode->prev = L->header->current;
    /* Make current's next pointer point to newNode */
    L->header->current->next = newNode;
    /* Make the header's last pointer point to newNode */
    L->header->last = newNode;
  }
        
  else
  {
    /* Make newNode's next pointer point to the node after current */
    newNode->next = L->header->current->next;
    /* Make newNode's prev pointer point to current */
    newNode->prev = L->header->current;
    /* Make current's next pointer point to newNode */
    L->header->current->next = newNode;
    /* Make the node after newNode's prev pointer point to newNode */
    newNode->next->prev = newNode;
  }


  /* Set newNode as the new current node */
  L->header->current = newNode; 
    
  /* Increment the length of the list regardless */
  L->length++;
}
/*********************************************/
void deleteFirst(ListRef L)
{       
  NodeType* temp;

  /* If the current pointer is set to the first element, */
  /* set it to the next element before freeing */
  if(L->header->current == L->header->first)
    L->header->current = L->header->current->next;

  /* Save a temporary pointer to the first element, and make the */
  /* first pointer point to the next element */
  temp = L->header->first;
  L->header->first = L->header->first->next;
  /* Finally, delete the element by calling free */
  free(temp);
     
  /* Regardless, decrement the length by 1 */
  L->length--;          
}
/*********************************************/       
void deleteLast(ListRef L)
{       
  NodeType* temp;

  /* If the current pointer is set to the last element, */
  /* set it to the previous element before freeing */
  if(L->header->current == L->header->last)
    L->header->current = L->header->current->prev;

  /* Save a temporary pointer to the last element, and make the */
  /* last pointer point to the previous element */
  temp = L->header->last;
  L->header->last = L->header->last->prev;
  /* Finally, delete the element by calling free */
  free(temp);
     
  /* Regardless, decrement the length by 1 */
  L->length--;    
}
/*********************************************/ 
void deleteCurrent(ListRef L)
{       
  NodeType* temp;

  /* If current is the first element, call deleteFirst */
  /* and set current to NULL afterwards */
  if(atFirst(L))
  {
    deleteFirst(L);
    L->header->current = NULL;
    return;
  }

  /* If current is the last element, call deleteLast */
  /* and set current to NULL afterwards */
  if(atLast(L))
  {
    deleteLast(L);
    L->header->current = NULL;
    return;
  }

  else
  {
    /* Make the previous element point to the next element */
    L->header->current->prev->next = L->header->current->next;
    /* Make the next element's prev pointer point to the previous element */
    L->header->current->next->prev = L->header->current->prev;
    /* Save a temporary pointer to the current element, and */
    /* make the current pointer NULL */
    temp = L->header->current;
    L->header->current = NULL;
    /* Finally, delete the element by calling free */
    free(temp);

    /* Decrement the length by 1 */
    L->length--;  
  }           
}
/*********************************************/  
void insertSorted(ListRef L, long data)
{
  /* Declare the new node, allocate space for it, and give it the data */
  NodeType* newNode;
  int counter;
  int i;  
  long nodeData; 

  newNode = malloc(sizeof(NodeType));
  newNode->data = data;
  newNode->count = 1;

  /* If there are no nodes on the list at all, make all header pointers */
  /* point to newNode, set newNode's pointers to NULL, and return from */
  /* the function */
  if(L->length == 0)
  {
    L->header->first = newNode;
    L->header->current = newNode;
    L->header->last = newNode;
      
    newNode->prev = NULL;
    newNode->next = NULL;

    L->length++;
    return;
  }

  /* If the data is smaller than anything on the list, ammend it */
  /* to the front */
  if(data < (L->header->first->data))
  {
    insertBeforeFirst(L, data);
    return;
  }
        
  /* Set the current pointer to point to the Last item */
  L->header->current = L->header->last;

  /* Initialize the variable for the loop invariant, as well as the counter */
  counter = L->length;      

  for(i = 0; i < counter; i++)
  {      
    /* Get the current element's data */
    nodeData = L->header->current->data; 

    /* If an element with this exact data already exists, just */
    /* increment it's 'count' variable */
    if(data == nodeData)
    {
      L->header->current->count++;
      free(newNode);
      return;
    }

    /* If the new element's data is now greater than the current */
    /* element, it needs to be inserted after it */
    if(data > nodeData)
    {
      insertAfterCurrent(L, data);
      return;
    }

    /* If the new element is strictly less than the current */
    /* element, move the current element to the previous */
    if(data < nodeData)
      movePrev(L);
  }
}
/*********************************************/  


/****************** Other Operations ******************/
void printList(ListRef L)
{
  /* Initialize an iterator pointer to be used in the loop */
  NodeType* iterator;
  /* Initialize the variable for the loop invariant, as well as the counter */
  int counter;
  int i;
  long nodeData;
  int nodeCount;

  /* If the list is empty, inform the user and return */
  if(isEmpty(L))
  {
    printf("The list is empty.\n");
    return;
  }

  iterator = L->header->first;
  counter = L->length;

  for(i = 0; i < counter; i++)
  {
    /* Get the node's data */
    nodeData = iterator->data;
    nodeCount = iterator->count;

    /* If there's only one copy of that element, print it out */
    if(nodeCount == 1)
      printf("%lld ", nodeData);

    /* If there's more than one of it, print out the number of */
    /* occurrences of it in addition to the element */
    else
      printf("(%d)%lld ",nodeCount, nodeData);

    /* Move the iterator to the next element */
    iterator = iterator->next;
  }

  /* Print out a return line */
  printf("\n");
}
/*********************************************/
ListRef copyList(ListRef L)
{
  ListRef newL;
  NodeType* iterator;
  int counter;
  int i;
  long nodeData;
  int nodeCount;

  newL = newList();

  /* Initialize an iterator pointer to be used in the loop */
  iterator = L->header->first;

  /* Initialize the variable for the loop invariant, as well as the counter */
  counter = L->length;

  for(i = 0; i < counter; i++)
  {
    /* Get the node's data and count variables */
    nodeData = iterator->data;
    nodeCount = iterator->count;

    /* Insert a copy of the node into the new List object */
    insertAfterCurrent(newL, nodeData);

    /* Make sure to copy the node's count variable as well */
    newL->header->current->count = nodeCount;

    /* Move the iterator to the next element */
    iterator = iterator->next;
  }

  return newL;
}

/*******************************************************************/
/*                  MEMORY UTILITY FUNCTIONS                       */

void insertNewMemoryRecord(ListRef L, void* address, char *string, int size)
{
  /* Declare the new node, allocate space for it, and give it the data */
  NodeType* newNode = malloc(sizeof(NodeType));
  newNode->data = 0;              /* Initializing dummy values from original linked-list */
  newNode->count = 1;             /* Initializing dummy values from original linked-list */
  newNode->allocated_size = size;
  newNode->address = address;
  newNode->file_and_line = string;
  newNode->in_use = 1; 
  gettimeofday(&(newNode->tv), NULL);       

  /* If there are no nodes on the list at all, make all header pointers
  point to newNode, and set newNode's pointers to NULL */
  if(L->length == 0)
  {
    L->header->first = newNode;
    L->header->current = newNode;
    L->header->last = newNode;
      
    newNode->prev = NULL;
    newNode->next = NULL;
  }

  else
  {
    /* Set newNode's pointers properly to make it the last element */
    newNode->prev = L->header->last;
    newNode->next = NULL;
    /* Set the pre-existing last element's next pointer to newNode */
    L->header->last->next = newNode;
    /* Update the last node in the ListHdr object */
    L->header->last = newNode;
    /* Also make the newNode the current element */
    L->header->current = newNode;
  }
     
  /* Increment the length of the list regardless */
  L->length++;
}

/*******************************************************************/
void listPrintMemstats(ListRef L)
{
  NodeType *iterator;
  int alloc_count, alloc_active, alloc_mem, i;
  double ticks, size_sum, size_mean, std_dev;

  /* Print out a return line */
  printf("\n");

  /* if the list is empty, then no allocations have been made */
  if(isEmpty(L)){
    printf("There were no allocations\n");
    return;
  }

  /* Initialize an iterator pointer to be used in the loop */
  iterator = L->header->first;
  /* Initialize the variable for the loop invariant, as well as the counter */
  alloc_count = L->length;
  alloc_active = 0;
  alloc_mem = 0;
  size_sum = 0;


  printf("These are the allocations that have not been freed:\n");

  /* Iterate through the list and perform necessary calculations and print statements */
  for(i = 0; i < alloc_count; i++){

    size_sum += iterator->allocated_size;
    
    if(iterator->in_use){
      alloc_active++;
      alloc_mem += iterator->allocated_size;
      printf("For allocation %d,\n", i);
      printf("Allocated space:          %d\n", iterator->allocated_size);
      ticks = iterator->tv.tv_sec + iterator->tv.tv_usec * 1e-6;
      printf("Time of allocation:       %f\n", ticks);
      printf("Address of allocation:    %p\n", iterator->address);
      printf("The file and line number: %s\n\n\n", iterator->file_and_line);
    }
       
    /* Move the iterator to the next element */
    iterator = iterator->next;
  }

  size_mean = size_sum / alloc_count;
  size_sum = 0;
  iterator = L->header->first;

  /* Iterate through the list again to calculate the standard deviation of allocation sizes */
  for(i = 0; i < alloc_count; i++){

    size_sum += pow(iterator->allocated_size - size_mean, 2);
    iterator = iterator->next;

  }

  std_dev = sqrt(size_sum / alloc_count);

  /* Print the final report about allocations */
  printf("In total, there were %d allocations\n", alloc_count);
  printf("Of those, there were %d allocations still in memory\n", alloc_active);
  printf("The total size of memory currently in use by these allocations was %d bytes\n", alloc_mem);
  printf("The average allocation size was %g bytes, with a standard deviation of %g bytes\n", size_mean, std_dev);

  /* Print out a return line */
  printf("\n");
}

/*******************************************************************/
int isAllocated(ListRef L, void* address)
{
  NodeType *iterator;
  int i, alloc_count, double_free;

  /* initialize the case to not having found a double_free */
  double_free = 0;

  /* If the list is empty, then no allocations have been made */
  if(isEmpty(L)){
    printf("There were no allocations\n");
    return 1;
  }
   
  /* Initialize an iterator pointer to be used in the loop */
  iterator = L->header->first;

  /* Initialize the variable for the loop invariant */
  alloc_count = L->length;

  /* iterate through each entry in the allocation list */
  for(i = 0; i < alloc_count; i++){

     /* if the memory is currently allocated, return 0 to indicate such */
    if(iterator->address == address && iterator->in_use){
      iterator->in_use = 0;
      return 0;
    } 

    /* if the memory was allocated, but already freed, set double_free to
       1 to indicate that we saw such a thing */
    else if (iterator->address == address && !(iterator->in_use)){
      double_free = 1;
    }   

    /* if the user is attempting to free using an address that is inside
       a currently allocated block, return 3 to indicate such a thing */
    else if (iterator->address < address && 
             (int)(iterator->address) + iterator->allocated_size >= (int)address &&
             iterator->in_use){
      return 3;
    }

    /* Move the iterator to the next element */
    iterator = iterator->next;
  }

  /* if we found an attempt at a double free and no good allocation to
     indicate otherwise, return 2 to indicate such */
  if(double_free){
     return 2;
  }

  /* if it reaches here, then it wasn't an allocated space and it didn't have a special case, return 1 to indicate such */
  return 1;
} 
