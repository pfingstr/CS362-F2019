CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest_assert.o: dominion_helpers.h unittest_assert.c
	gcc -c unittest_assert.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o unittest_assert.o
	gcc  -o unittest1 -g  unittest1.c dominion.o rngs.o unittest_assert.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o unittest_assert.o
	gcc  -o unittest2 -g  unittest2.c dominion.o rngs.o unittest_assert.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o unittest_assert.o
	gcc  -o unittest3 -g  unittest3.c dominion.o rngs.o unittest_assert.o $(CFLAGS)



unittest7: unittest7.c dominion.o rngs.o unittest_assert.o
	gcc  -o unittest7 -g  unittest7.c dominion.o rngs.o unittest_assert.o $(CFLAGS)

unittest8: unittest8.c dominion.o rngs.o unittest_assert.o
	gcc  -o unittest8 -g  unittest8.c dominion.o rngs.o unittest_assert.o $(CFLAGS)

unittest9: unittest9.c dominion.o rngs.o unittest_assert.o
	gcc  -o unittest9 -g  unittest9.c dominion.o rngs.o unittest_assert.o $(CFLAGS)

unittest10: unittest10.c dominion.o rngs.o unittest_assert.o
	gcc  -o unittest10 -g  unittest10.c dominion.o rngs.o unittest_assert.o $(CFLAGS)

unittestresults: unittest1 #unittest2 unittest3 
	./unittest1 &> unittestresult.out
	#./unittest2 >> unittestresult.out
	#./unittest3 >> unittestresult.out

	gcov -b -f dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
