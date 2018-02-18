CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testSuite: unittest?.c cardtest?.c testSuite.c dominion.o rngs.o
	gcc  -o testSuite -g  testSuite.c unittest?.c cardtest?.c dominion.o rngs.o $(CFLAGS)
	./testSuite > unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

testHelper.o: testHelper.h testHelper.c
	gcc -c testHelper.c -g  $(CFLAGS)

testRandom: randomtest*.c dominion.o rngs.o testHelper.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o testHelper.o $(CFLAGS)
	rm -f dominion.gcda dominion.c.gcov
	./randomtestadventurer > randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o testHelper.o $(CFLAGS)
	rm -f dominion.gcda dominion.c.gcov
	./randomtestcard1 > randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o testHelper.o $(CFLAGS)
	rm -f dominion.gcda dominion.c.gcov
	./randomtestcard2 > randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard *.exe
