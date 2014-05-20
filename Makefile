all: testing

testing: testing.c memory.c memory.h List.h List.c
	gcc testing.c memory.c memory.h List.h List.c -o testing

clean:
	rm testing
