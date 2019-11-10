CFLAGS= -Wall -fprofile-arcs -ftest-coverage

testme: testme.c 
	gcc -o testme testme.c -g $(CFLAGS)

run: testme
	./testme