#include <stdio.h>
#include<stdlib.h>
#include "testHelper.h"
#include "dominion.h"

// TODO: Move the helper functions in testSuite.c into this file.

int assertTrue(int bool, char* msg) {
    if (bool != 1) {
        // TODO: Print to stderr instead of stdout.
        printf("Failed assertion: %s\n", msg);
        return -1;
    } else {
        return 0;
    }
}


int assertEqual(int expected, int actual, char* msg) {

    if (expected == actual) {
        return 0;
    }

    // TODO: Print to stderr instead of stdout.
    printf("Failed assertion because %d != %d: %s\n", expected, actual, msg);
    return -1;
}

void randomizeGameState(struct gameState G) {

    // Logic taken from Lesson 11.

    int i;
    for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&G)[i] = rand() % 256;
    }
}

void randomizePile(int* cardPile, int cardCount)
{
    for (int i = 0; i < cardCount; i++)
    {
        cardPile[i] = rand() % (LAST_CARD + 1);
    }
}

void printGameStateSummary(int i, int playerCount, int handPos,
                           struct gameState G, struct gameState initialG) {
    printf("iter %d: active player %d of %d: deck %d -> %d "
            "discard %d -> %d hand %d -> %d actions %d -> %d "
            "buys %d -> %d played %d -> %d handpos %d\n",
           i, G.whoseTurn, playerCount,
           initialG.deckCount[G.whoseTurn], G.deckCount[G.whoseTurn],
           initialG.discardCount[G.whoseTurn], G.discardCount[G.whoseTurn],
           initialG.handCount[G.whoseTurn], G.handCount[G.whoseTurn],
           initialG.numActions, G.numActions, initialG.numBuys, G.numBuys,
           initialG.playedCardCount, G.playedCardCount, handPos);
}