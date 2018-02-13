#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelper.h"

// FIXME: Should I test cardEffect() or cardEffectSmithy()?
// FIXME: If the former, should I randomize everything?

int main() {

    // srand(time(NULL));
    // FIXME: debug
    srand(1);

    int card = smithy;
    struct gameState G, initialG;
    int playerCount;
    int choice1, choice2, choice3, handPos;

    // TODO: Extract method.

    // Run the test many times.
    int i;
    for (i = 0; i < 200; i++) {

        // Start with a completely random gameState.
        randomizeGameState(G);

        // Random but sane player count (1 .. MAX_PLAYERS)
        playerCount = rand() % (MAX_PLAYERS - 1) + 1;

        G.whoseTurn = rand() % playerCount;

        // Random but sane state for the player piles.
        // TODO: Extract method
        int p;
        for (p = 0; p < playerCount; p++) {

            G.deckCount[p] =  rand() % MAX_DECK;
            //randomizePile(G.deck[p], G.deckCount[p]);

            G.discardCount[p] = rand() % MAX_DECK;
            //randomizePile(G.discard[p], G.discardCount[p]);

            // The hand must be non-zero to play a card. (1 .. MAX_HAND - 1)
            // FIXME: Try zero values for above counts, to make test more robust.
            G.handCount[p] = rand() % (MAX_HAND - 1) + 1;
            //randomizePile(G.hand[p], G.handCount[p]);
        }

        printf("iter %d: active player %d of %d has: %d %d %d\n", i, G.whoseTurn, playerCount, G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn], G.handCount[G.whoseTurn]);

        // Random but sane state for the current turn
        // TODO: Are sane values needed here?
        G.numActions = rand() % MAX_HAND;
        G.numBuys = rand() % MAX_HAND;
        G.playedCardCount = rand() % MAX_HAND;
        handPos = rand() % G.handCount[G.whoseTurn];

        // Randomize choice1, choice2, and choice3
        // The last card in the CARD enum is the highest acceptable value.
        // FIXME: DEBUG
        choice1 = 1; // rand() % (LAST_CARD + 1);
        choice2 = 1; // rand() % (LAST_CARD + 1);
        choice3 = 1; // rand() % (LAST_CARD + 1);

        // FIXME: randomize bonus

        // FIXME: Clone G so I can compare it.
        // Logic taken from Lesson 11.
        memcpy(&initialG, &G, sizeof(struct gameState));

        int result = cardEffect(card, choice1,choice2,choice3, &G, handPos, &p);

        //int result = drawCard(G.whoseTurn, &G);

        // FIXME: Validate result
        assertEqual(0, result, "Response value is 0");

        // FIXME: compare to the expected gameState
        assertEqual(initialG.handCount[G.whoseTurn] + 3, G.handCount[G.whoseTurn], "handCount increased by 3");

    }
    // FIXME: Output results
}