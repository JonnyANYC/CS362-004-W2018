#ifndef _TESTHELPER_H
#define _TESTHELPER_H

int addCards(int* cardPile, int card, int cardCount);

int assertTrue(int bool, char* msg);

int assertEqual(int expected, int actual, char* msg);

#endif //_TESTHELPER_H
