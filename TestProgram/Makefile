
all: crunch iobound fast

crunch: crunch.c
	cc crunch.c -o crunch

fast: fast.c
	cc fast.c -o fast

iobound: iobound.c
	cc iobound.c -o iobound

test1: crunch
	time ./crunch &
	time ./crunch &

test2: crunch
	time nice -n 10 ./crunch &
	time ./crunch &

test3: crunch
	time nice -n 15 ./crunch &
	time nice -n 10 ./crunch &
	time ./crunch &

test4: crunch
	time ./crunch &
	time ./crunch &
	time ./crunch &
	time ./crunch &
	time ./crunch &
	time nice -n 15 ./fast

test5and6: crunch iobound
	./crunch &
	./crunch &
	./iobound

clean:
	rm crunch iobound fast
