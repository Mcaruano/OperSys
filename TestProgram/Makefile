
all: crunch fileinit iobound getline

crunch: crunch.c
	cc crunch.c -o crunch

fileinit: fileinit.c
	cc fileinit.c -o fileinit

iobound: iobound.c
	cc iobound.c -o iobound

getline: getline.c
	cc getline.c -o getline

test: crunch
	time ./crunch &
	time ./crunch &

combotest: crunch getline
	./crunch &
	./getline

clean:
	rm crunch iobound fileinit getline
