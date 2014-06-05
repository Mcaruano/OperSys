all: generictest

generictest: generictest.c metadata.c metadata.h
	cc -Wall generictest.c metadata.c -o generictest

 clean:
	rm generictest