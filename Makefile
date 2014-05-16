all: testing.o memory.o List.o binary testing

testing.o: testing.c
	gcc -c testing.c

memory.o: memory.c memory.h
	gcc -c memory.c

List.o: List.c List.h
	gcc -c List.c

binary: testing.o memory.o List.o
	gcc testing.o memory.o List.o -o binary

testing: testing.c memory.c memory.h List.h List.c
	gcc testing.c memory.c memory.h List.h List.c -o testing

clean:
	rm testing binary *.o
