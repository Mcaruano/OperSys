In testing.c
	added some more mallocs of varying sizes in a loop below
	made a call to slug_memstats() to test output
	
In List.c
	Added 5 fields to the node to store the data I could think about that would be needed
	Added two functions below, insertAfterLast_test() and print_list_alloc()
	insertAfterLast_test() is a variation on insertAfterLast(), made to fit the updated data structure.
	print_list_alloc() prints out the information for slug_memstats() as per the specs
	
In List.h
	Added prototypes for the two above functions
	
In memory.c
	Added a global ListRef variable to be the accessor to the list.
	Included a call to insertAfterLast_test() in slug_malloc() to add the allocation to the list
	Included a call to print_list_alloc() in slug_memstats() to perform it's job
	
In memory.h
	Temporarily added a prototype to slug_memstats() so testing.c could call the function directly
	
In Makefile
	Added a target 'binary', and several dependencies, to compile the test program