
all: crunch iobound

crunch: crunch.c
	cc crunch.c -o crunch

iobound: iobound.c
	cc iobound.c -o iobound

test: crunch
	time ./crunch &
	time ./crunch &

combotest: crunch iobound
	./crunch &
	./crunch &
	./iobound

clean:
	rm crunch iobound
