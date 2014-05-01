
all: crunch

crunch: crunch.c
	cc crunch.c -o crunch

test: 
	time ./crunch &
	time ./crunch &

clean:
	rm *.o crunch
