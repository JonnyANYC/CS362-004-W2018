#ifndef _TESTSUITE_H
#define _TESTSUITE_H

int addCards(int* cardPile, int card, int cardCount);

int assertTrue(int bool, char* msg);

int assertEqual(int expected, int actual, char* msg);

#endif //_TESTSUITE_H
