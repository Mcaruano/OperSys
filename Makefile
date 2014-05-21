all: generaltest

generaltest: generaltest.c memory.c memory.h List.h List.c
	cc -Wall generaltest.c memory.c List.c -o generaltest

clean:
	rm generaltest
