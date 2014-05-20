all: testing

testing: testing.c memory.c memory.h List.h List.c
	cc -Wall testing.c memory.c List.c -o testing

clean:
	rm testing
