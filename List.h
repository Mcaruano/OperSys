//FILE: List.h
//AUTHOR: Matt Caruano
//VERSION: Original - created 04-17-2013
//
//PURPOSE: This provides all of the functions necessary to manipulate a linked
//list structure. The nodes of this structure can store a 'long long' type and 
//a regular 'int' type.
//
//
//CONSTRUCTORS/DESTRUCTORS:
//  ListRef newList(void)
//     Postcondition: A new List object has been created with no elements. All
//                    pointers are set to NULL
//
//  void freeList(ListRef* pL)
//     The list structure, including all underlying and dependant structures, have
//     been returned to memory
//
//
//ACCESS FUNCTIONS:
//  int isEmpty(ListRef L)
//     Returns True if the list contains no nodes
//
//  int offEnd(ListRef L)
//     Returns True of the current pointer is set to a NULL target
//
//  int atFirst(ListRef L)
//     Returns True if the current pointer is pointing to the first element
//
//  int atLast(ListRef L)
//     Returns True if the current pointer is pointing to the last element
//
//  long long getFirst(ListRef L)
//     Precondition: !isEmpty()
//     Returns the first element of the list
//
//  long long getLastListRef L)
//     Precondition: !isEmpty()
//     Returns the last element of the list
//
//  long long getCurrent(ListRef L)
//     Precondition: !offEnd()
//     Returns the element of the list that the current pointer is pointing to
//
//  int getLength(ListRef L)
//     Precondition: !offEnd()
//     Returns the length of the list
//
//  int equals(ListRef A, ListRef B)
//     Returns True if and only if the two lists' elements contain the same data,
//     the same quantity of data(if multiples of one item), and are in the same order
//
//
//MANIPULATION PROCEDURES:
//  void makeEmpty(ListRef L)
//     Postcondition: isEmpty()
//     All nodes in the list have been returned to memory
//
//  void moveFirst(ListRef L)
//     Precondition: !isEmpty()
//     Postcondition: !offEnd()
//     The current pointer now points to the first element
//
//  void moveLast(ListRef L)
//     Precondition: !isEmpty()
//     Postcondition: !offEnd()
//     The current pointer now points to the last element
//
//  void movePrev(ListRef L)
//     Precondition: !offEnd()
//     Postcondition: offEnd() only if atFirst() was True
//
//  void moveNext(ListRef L)
//     Precondition: !offEnd()
//     Postcondition: offEnd() only if atLast() was True
//
//  void insertBeforeFirst(ListRef L, long long data)
//     Postcondition: !isEmpty()
//     A node containing 'data' has been inserted before the first element of
//     the list. It is now the first element.
//
//  void insertAfterLast(ListRef L, long long data)
//     Postcondition: !isEmpty()
//     A node containing 'data' has been inserted after the last element of
//     the list. It is now the last element.
//
//  void insertBeforeCurrent(ListRef L, long long data)
//     Precondition: !offEnd()
//     Postcondition: !isEmpty(), !offEnd()
//     A node containing 'data' has been inserted before the element that the
//     current pointer is pointing to. It is now the current element.
//
//  void insertAfterCurrent(ListRef L, long long data)
//     Precondition: !offEnd()
//     Postcondition: !isEmpty(), !offEnd()
//     A node containing 'data' has been inserted after the element that the
//     current pointer is pointing to. It is now the current element.
//
//  void deleteFirst(ListRef L)
//     Precondition: !isEmpty()
//     The first element of the list has been returned to memory
//
//  void deleteLast(ListRef L)
//     Precondition: !isEmpty()
//     The last element of the list has been returned to memory
//
//  void deleteCurrent(ListRef L)
//     Precondition: !isEmpty(), !offEnd()
//     Postcondition: offEnd()
//     The current element of the list has been returned to memory. The current
//     pointer now points to NULL
//
//  void insertSorted(ListRef L, long long data)
//     Precondition: !offEnd()
//     Postcondition: !isEmpty(), !offEnd()
//     An element containing 'data' has been inserted to the list such that an
//     ascending order has been preserved whereby the first element of the list
//     contains the smallest value and the last element of the list contains the
//     largest value.
//
//OTHER OPERATIONS:
//  void printList(ListRef L)
//     The contents of the list have been output to the standard output
//
//  ListRef copyList(ListRef L)
//     An exact copy of L has been returned, with the same nodes in the same
//     order with the same multiplicity

#include <sys/time.h>

typedef struct List* ListRef;

/*********** Constructors/Destructors ***********/
ListRef newList(void);
void freeList(ListRef* pL);

/*************** Access Functions ***************/
int isEmpty(ListRef L);
int offEnd(ListRef L);
int atFirst(ListRef L);
int atLast(ListRef L);
long long getFirst(ListRef L);
long long getCurrent(ListRef L);
long long getLast(ListRef L);
int getLength(ListRef L);
int equals(ListRef A, ListRef B);

/************ Manipulation Procedures ************/
void makeEmpty(ListRef L);
void moveFirst(ListRef L);
void moveLast(ListRef L);
void movePrev(ListRef L);
void moveNext(ListRef L);

void insertBeforeFirst(ListRef L, long long data);
void insertAfterLast(ListRef L, long long data);
void insertBeforeCurrent(ListRef L, long long data);
void insertAfterCurrent(ListRef L, long long data);

void deleteFirst(ListRef L);
void deleteLast(ListRef L);
void deleteCurrent(ListRef L);
void insertSorted(ListRef L, long long data);

/************ Other Operations ************/
void printList(ListRef L);
ListRef copyList(ListRef L);

/************ Memory Operations ***********/
void insertAfterLast_test(ListRef L, struct timeval init_time, char *string, int val);
void print_list_alloc(ListRef L);
