all: testing listdr

testing: testing.c memory.c memory.h
	cc testing.c memory.c memory.h -o testing

listdr:
	gcc Listdr.c List.h List.c -o listdr

clean:
	rm *.o testing listdr