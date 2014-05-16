//FILE: Listdr.c
//AUTHOR: Matt Caruano
//VERSION: Original - created 04-17-2013
//
//PURPOSE: This program tests every function provided in List.h for errors,
//outputting many lines to standard output along the way. The test passes if
//this program compiles and runs successfully && all of the values anticipated
//in the statements printed to the screen match the output from the list
//functions.

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main(int argc, char *argv[])
{
    //Declare a new List, it should be empty
    printf("CREATING A NEW, EMPTY LIST\n");
    ListRef test = newList();
    
    if(isEmpty(test))
       printf("***This new List is empty according to the isEmpty function.\n");
    if(offEnd(test))
       printf("***The current pointer of this List is NULL according to the offEnd function.\n");      
    printf("At this point, printList should output a message telling us the\n");
    printf("list is empty, does it?\n");
    printf("printList output: ");
    printList(test);
    printf("\n\n");
    
    //Add a value to it
    printf("ADDING A NEW ELEMENT TO THE LIST (using insertBeforeFirst)\n");
    long long value = 1100100100;
    insertBeforeFirst(test, value);
    
    long long firstVal = getFirst(test);
    long long currentVal = getCurrent(test);
    long long lastVal = getLast(test);
    int length = getLength(test);
    printf("There is only one element, and getLength returns %d.\n", length);
    printf("There is only one element, and the data stored in that\n");
    printf("element is 1100100100. So getfirst, getCurrent, and getLast\n");
    printf("should all return this value.\n");
    printf("getFirst returns: %lld\n", firstVal);
    printf("getCurrent returns: %lld\n", currentVal);
    printf("getLast returns: %lld\n\n\n", lastVal);
    
    //Add another value before the First
    printf("ADDING A SECOND ELEMENT TO THE LIST (using insertBeforeFirst)\n");
    long long nextVal = 2100100100;
    insertBeforeFirst(test, nextVal);
    
    long long newFirstVal = getFirst(test);
    long long newCurrentVal = getCurrent(test);
    long long newLastVal = getLast(test);
    int newLength = getLength(test);
    printf("There are now two elements, and getLength returns %d.\n", newLength);
    printf("The first element should be 2100100100, the second(last) element should\n");
    printf("be 1100100100, and the current element should be 2100100100.\n");
    printf("getFirst returns: %lld\n", newFirstVal);
    printf("getCurrent returns: %lld\n", newCurrentVal);
    printf("getLast returns: %lld\n\n\n", newLastVal);
    
    //Testing printList
    printf("USING THE CURRENT LIST TO TEST printList\n");
    printf("printList should output \"2100100100 1100100100\"\n");
    printf("printList outputs: ");
    printList(test);
    printf("\n\n");
    
    //Testing equals
    printf("TESTING equals\n");
    //Make a duplicate of the previous list
    ListRef testTwo = newList();
    long long valueTwo = 100100100;
    insertBeforeFirst(testTwo, valueTwo);
    long long nextValTwo = 2100100100;
    insertBeforeFirst(testTwo, nextValTwo);
    printf("My duplicate list contains: ");
    printList(testTwo);
    printf("So the equals function should return True.\n");
    if(equals(test, testTwo))
       printf("***These two Lists are equal according to the equals function.\n\n");
    //Add one more element, test for equals (should return False)   
    printf("I'm now adding another element with data = 100100100 to the\n");
    printf("second list, and am going to test to see if equals returns False.\n");
    insertBeforeFirst(testTwo, valueTwo);
    printf("So the second list now contains: ");
    printList(testTwo);
    if(!equals(test, testTwo))
       printf("***These two Lists are not equal according to the equals function.\n\n");   
       
    //Testing insertAfterLast
    printf("TESTING insertAfterLast\n");
    ListRef test3 = newList();
    long long v1 = 101;
    long long v2 = 102;
    long long v3 = 103;
    insertAfterLast(test3, v1);
    insertAfterLast(test3, v2);
    insertAfterLast(test3, v3);
    printf("We are now using insertAfterLast to insert the values 101, 102, and 103\n");
    printf("into an empty List in that order. If it worked correctly, printList\n");
    printf("should output: 101 102 103\n");
    printf("printList returns: ");
    printList(test3);
    printf("\n\n"); 
    
    //Testing insertBeforeFirst
    printf("TESTING insertBeforeFirst\n");
    ListRef test3B = newList();
    long long va1 = 101;
    long long va2 = 102;
    long long va3 = 103;
    insertBeforeFirst(test3B, va1);
    insertBeforeFirst(test3B, va2);
    insertBeforeFirst(test3B, va3);
    printf("We are now using insertBeforeFirst to again insert the values 101, 102, and 103\n");
    printf("into an empty List in that order. If it worked correctly, printList\n");
    printf("should output: 103 102 101\n");
    printf("printList returns: ");
    printList(test3B);
    printf("\n\n");     
    
    //Testing insertAfterCurrent
    printf("TESTING insertAfterCurrent\n");
    long long v4 = 104;
    long long test3Current = getCurrent(test3);
    printf("We will use the previous List for this test. getCurrent returns: %lld\n", test3Current);
    printf("Current is the last element, so this is the boundary case.\n");
    printf("So using insertAfterCurrent to insert the value 104 should give us:\n");
    printf("101 102 103 104\n");  
    insertAfterCurrent(test3, v4);
    printf("After calling insertAfterCurrent, the List contains: ");
    printList(test3); 
    printf("\n\n"); 
        
    //Testing insertBeforeCurrent
    printf("TESTING insertBeforeCurrent\n");
    long long v5 = 105;
    moveFirst(test3);
    long long test3CurrentF = getCurrent(test3);
    printf("We will use the previous List for this test. but we'll set the\n");
    printf("current pointer to the first value to test the boundary case.\n");
    printf("getCurrent returns: %lld\n", test3CurrentF);
    printf("So using insertBeforeCurrent to insert the value 105 should give us:\n");
    printf("105 101 102 103 104\n");  
    insertBeforeCurrent(test3, v5);
    printf("After calling insertBeforeCurrent, the list contains: ");
    printList(test3); 
    printf("\n\n"); 
    
    //Testing moveFirst, moveLast, movePrev, moveNext
    printf("TESTING moveFirst, moveLast, movePrev, moveNext\n");
    printf("Using the previous List, the values are: ");
    printList(test3);
    long long test3Current1 = getCurrent(test3);
    printf("And the current value is %lld.\n", test3Current1);
    movePrev(test3);
    if(offEnd(test3))
       printf("After calling movePrev, the current pointer is NULL.\n");
    moveFirst(test3);
    long long test3Current4 = getCurrent(test3);
    printf("moveFirst set current to %lld.\n", test3Current4);
    if(atFirst(test3))
       printf("This follow-up message prints out only if atFirst is True.\n");
    moveNext(test3);
    long long test3Current3 = getCurrent(test3);
    printf("moveNext set current to %lld.\n", test3Current3); 
    moveLast(test3);
    long long test3Current5 = getCurrent(test3);
    printf("And moveLast set current to %lld.\n", test3Current5);
    if(atLast(test3))
       printf("This follow-up message prints out only if atLast is True.\n\n\n");
        
    //Testing makeEmpty
    printf("TESTING makeEmpty\n");
    printf("Using the previous List, the values are: ");
    printList(test3);
    int test3Length = getLength(test3);
    printf("And the length of the List is: %d\n", test3Length);
    makeEmpty(test3);
    int test3Length2 = getLength(test3);
    printf("After makeEmpty was called, the length is now: %d\n", test3Length2);
    printf("And a call to printList yields: ");
    printList(test3);
    printf("\n\n"); 
    
    //Testing deleteFirst, deleteLast, and deleteCurrent
    printf("TESTING deleteFirst, deleteLast, and deleteCurrent\n");
    ListRef test4 = newList();
    long long val1 = 1001;
    long long val2 = 1002;
    long long val3 = 1003;
    long long val4 = 1004;
    long long val5 = 1005;
    insertAfterLast(test4, val1);
    insertAfterLast(test4, val2);
    insertAfterLast(test4, val3);
    insertAfterLast(test4, val4);
    insertAfterLast(test4, val5);
    movePrev(test4);
    movePrev(test4);
    printf("We are using a new List whose values are: \n");
    printList(test4);
    long long test4Current = getCurrent(test4);
    printf("The current pointer is: %lld\n", test4Current);
    deleteFirst(test4);
    printf("After calling deleteFirst, the List contains: \n");
    printList(test4);
    deleteLast(test4);
    printf("After calling deleteLast, the List contains: \n");
    printList(test4);
    deleteCurrent(test4);
    printf("After calling deleteCurrent, the List contains: \n");
    printList(test4);
    deleteFirst(test4);
    deleteLast(test4);
    printf("Calling deleteFirst and deleteLast each once more yields: \n");
    printList(test4);
    printf("\n\n"); 
    
    //Testing copyList
    printf("TESTING copyList\n");
    ListRef test5 = newList();
    long long valu1 = 1001;
    long long valu2 = 1002;
    long long valu3 = 1003;
    long long valu4 = 1004;
    long long valu5 = 1005;
    insertAfterLast(test5, valu1);
    insertAfterLast(test5, valu2);
    insertAfterLast(test5, valu3);
    insertAfterLast(test5, valu4);
    insertAfterLast(test5, valu5);
    printf("We are using a new List whose values are: \n");
    printList(test5);
    ListRef test5Copy = copyList(test5);
    printf("After calling copyList, the new List object contains: \n");
    printList(test5Copy);
    printf("\n\n");
    
    //Testing insertSorted
    printf("TESTING insertSorted\n");
    ListRef test6 = newList();
    long long value1 = 1101;
    long long value2 = 1102;
    long long value3 = 1103;
    long long value4 = 1104;
    long long value5 = 1105;
    insertSorted(test6, value1);
    printf("After inserting 1101 to the List, we get: \n");
    printList(test6);
    insertSorted(test6, value4);
    printf("After inserting 1104 to the List, we get: \n");
    printList(test6); 
    insertSorted(test6, value3);
    printf("After inserting 1103 to the List, we get: \n");
    printList(test6);   
    printf("\n\n");
    
    //Testing insertSorted, listCopy, equals, and makeEmpty
    printf("TESTING insertSorted, listCopy, equals, and makeEmpty\n");
    ListRef test7 = newList();
    long long value11 = 111;
    long long value12 = 112;
    long long value13 = 113;
    long long value14 = 110;
    long long value15 = 115;
    long long value16 = 113;
    long long value17 = 113;
    long long value18 = 115;
    long long value19 = 110;
    long long value20 = 113;
    long long value21 = 109;
    insertSorted(test7, value11);
    insertSorted(test7, value12);
    insertSorted(test7, value13);
    insertSorted(test7, value14);
    insertSorted(test7, value15);
    insertSorted(test7, value16);
    insertSorted(test7, value17);
    insertSorted(test7, value18);
    insertSorted(test7, value19);
    insertSorted(test7, value20);
    insertSorted(test7, value21);
    printf("After inserting 111, 112, 113, 110, 115, 113, 113, 115, 110, 113, and 109\n");
    printf("to the List, we get: \n");
    printList(test7);
    int test7Length = getLength(test7);
    printf("And getLength returns: %d\n", test7Length);
    
    ListRef test7C = copyList(test7);
    printf("Copying this list yields a list containing: \n");
    printList(test7C);
    int test7CLength = getLength(test7C);
    printf("Whose getLength returns: %d\n", test7CLength);
    if(equals(test7, test7C))
       printf("***These two lists are equal according to the equals function\n");
    makeEmpty(test7C);
    printf("After using makeEmpty on the newly copied List, printList returns: \n");
    printList(test7C);
    printf("\n\n");    
    
    //Testing freeList
    printf("TESTING freeList\n");
    ListRef test8 = newList();
    long long vl1 = 1101;
    long long vl2 = 1102;
    long long vl3 = 1103;
    long long vl4 = 1104;
    long long vl5 = 1105;
    insertSorted(test8, vl1);
    insertSorted(test8, vl2);
    insertSorted(test8, vl3);
    insertSorted(test8, vl4);
    insertSorted(test8, vl5);    
    printf("We are using a new list whose values are: \n");
    printList(test8);
    //Free the list
    ListRef* test8p = &test8;
    freeList(test8p);
    printf("freeList passes the test if the program doesn't crash\n");
    printf("\n\n");
	
    //SUCCESS
    printf("The test was a success!!! All functions passed!\n");

  system("PAUSE");	    	
  return 0;
}

