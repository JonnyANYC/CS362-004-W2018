#ifndef _TESTHELPER_H
#define _TESTHELPER_H

#include "dominion.h"

// No way to set this dynamically, unfortunately.
#define LAST_CARD treasure_map

int addCards(int* cardPile, int card, int cardCount);

int assertTrue(int bool, char* msg);

int assertEqual(int expected, int actual, char* msg);

void randomizeGameState(struct gameState G);

void randomizePile(int* cardPile, int cardCount);

void printGameStateSummary(int i, int playerCount, int handPos,
                           struct gameState G, struct gameState initialG);

#endif //_TESTHELPER_H
