all: testing

testing: testing.c memory.c memory.h
	cc testing.c memory.c memory.h -o testing

clean:
	rm testing