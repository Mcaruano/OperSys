all: test1 test2 test3 test4 test5

test1:
	cc -Wall test1.c memory.c List.c -o test1

test2:
	cc -Wall test2.c memory.c List.c -o test2

test3:
	cc -Wall test3.c memory.c List.c -o test3

test4:
	cc -Wall test4.c memory.c List.c -o test4

test5:
	cc -Wall test5.c memory.c List.c -o test5
	
clean:
	rm test1 test2 test3 test4 test5
