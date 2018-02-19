#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelper.h"


void testMain(int iterations, int seed) {

    if (seed == -1) {
        // If no seed provided, use the system clock.
        seed = (int)time(NULL);
    }
    srand(seed);

    printf("Starting test of %d iterations with seed %d.\n", iterations, seed);

    int card = smithy;
    struct gameState G, initialG;
    int playerCount, handPos;
    int result, r, totalFailedCases = 0;
    int rndSum, rnd1 = -1, rnd2 = -1, rnd3 = -1;
    int currentCard;
    int i, p;

    // TODO: Extract method.

    // Run the test many times.
    for (i = 0; i < iterations; i++) {

        // Start with a completely random gameState.
        randomizeGameState(G);

        // Random but sane player count (1 .. MAX_PLAYERS)
        playerCount = rand() % (MAX_PLAYERS - 1) + 1;

        G.whoseTurn = rand() % playerCount;

        // Random but sane state for the player piles.
        // TODO: Extract method
        rndSum = MAX_HAND + 1;
        for (p = 0; p < playerCount; p++) {
            // Pick random counts for each player's hand that don't overload the deck.
            // This includes boundaries of 0 (except for handCount) and a sum of MAX_HAND
            while (rndSum > MAX_HAND || rnd1 < 1) {
                rnd1 = rand() % MAX_HAND;
                rnd2 = rand() % MAX_HAND;
                rnd3 = rand() % MAX_HAND;
                rndSum = rnd1 + rnd2 + rnd3;
            }

            G.handCount[p] = rnd1;
            G.deckCount[p] = rnd2;
            G.discardCount[p] = rnd3;
            // The code can't process invalid cards, so let's sanitize.
            randomizePile(G.deck[p], G.deckCount[p]);
            randomizePile(G.discard[p], G.discardCount[p]);
        }

        // Random but sane state for the current turn

        G.numActions = rand() % 255;
        G.playedCardCount = rand() % MAX_HAND;
        randomizePile(G.playedCards, G.playedCardCount);

        handPos = rand() % G.handCount[G.whoseTurn];
        G.hand[G.whoseTurn][handPos] = card;


        // Clone G so I can compare it. Logic taken from Lesson 11.
        memcpy(&initialG, &G, sizeof(struct gameState));


        result = cardEffectSmithy(&G, handPos, G.whoseTurn);


        // Test oracle 1: basics.
        r = 0;
        r += assertEqual(0, result, "Response value is 0");
        r += assertEqual(initialG.whoseTurn, G.whoseTurn, "The player turn is unchanged");
        r += assertEqual(initialG.numPlayers, G.numPlayers, "player count is unchanged");

        // Test oracle 2: verify +3 cards for the current player.
        // Next test FAILS because of an intentional bug in cardEffectSmithy().
        r += assertEqual(initialG.handCount[G.whoseTurn] + 2, G.handCount[G.whoseTurn],
                         "hand count increased by 2 (+ 3 - 1 played Smithy)");
        currentCard = initialG.deck[G.whoseTurn][initialG.deckCount[G.whoseTurn] - 1];
        // TODO: What if deck and discard are both empty? Is that a valid scenario?
        if (G.discardCount[G.whoseTurn] == initialG.discardCount[G.whoseTurn]) {
            // No shuffling occurred. Verify that a normal card-draw happened.

            // Next test FAILS because of an intentional bug in cardEffectSmithy().
            r += assertEqual(currentCard,
                             G.hand[G.whoseTurn][G.handCount[G.whoseTurn] - 2],
                             "Second to last card in hand is the card previously on top of the deck");
            // TODO: Perform above test for the other two drawn cards as well.
            // TODO: currentCard should be a pointer, so I can easily access its neighbors.
        } else {
            // Verify that shuffling occurred as expected.
            r += assertEqual(fullDeckCount(G.whoseTurn, currentCard, &initialG),
                             fullDeckCount(G.whoseTurn, currentCard, &G),
                             "The card added to the hand came from the deck or discards.");
            // Next test FAILS because of an intentional bug in cardEffectSmithy().
            r += assertEqual(initialG.deckCount[G.whoseTurn] + initialG.discardCount[G.whoseTurn] - 3,
                             G.deckCount[G.whoseTurn] + G.discardCount[G.whoseTurn],
                             "After shuffle, deck + discard count is equivalent (-3 cards)");
        }

        // Test oracle 3: verify the remaining state for the current player.
        r += assertEqual(initialG.numActions, G.numActions, "numActions is unchanged");
        r += assertEqual(initialG.playedCardCount + 1, G.playedCardCount, "playedCardCount is +1");
        r += assertEqual(card, G.playedCards[G.playedCardCount - 1], "last played card is a Smithy");
        r += assertEqual(initialG.numBuys, G.numBuys, "numBuys is unchanged");

        // Test oracle 4: verify no changes for the other players.

        for (p = 0; p < playerCount; p++) {

            if (p == G.whoseTurn) {
                // Skip the active player, since that player was checked previously.
                continue;
            }
            r += assertEqual(initialG.handCount[p], G.handCount[p], "handCount is unchanged for other players.");
            r += assertEqual(0, memcmp(initialG.hand[p], G.hand[p], sizeof(int) * MAX_HAND),
                             "the hand is unchanged for all other players");
            r += assertEqual(initialG.discardCount[p], G.discardCount[p], "discardCount is unchanged for other players.");
            r += assertEqual(0, memcmp(initialG.discard[p], G.discard[p], sizeof(int) * MAX_DECK),
                             "the discard pile is unchanged for all other players");
            r += assertEqual(initialG.deckCount[p], G.deckCount[p], "deckCount is unchanged for other players.");
            r += assertEqual(0, memcmp(initialG.deck[p], G.deck[p], sizeof(int) * MAX_DECK),
                             "the deck is unchanged for all other players");
        }

        if (r < 0) {
            totalFailedCases++;
            printf("Failed test for: ");
            printGameStateSummary(i, playerCount, handPos, G, initialG);
        }

        // TODO: more tests please!

    }

    // Output results
    if (totalFailedCases > 0) {
        printf("TEST SUITE FAILED: %d failures out of %d cases. (Seed: %d)\n",
               totalFailedCases, iterations, seed);
    } else {
        printf("ALL TESTS PASSED for %d cases.\n", iterations);
    }
}


int main() {
    testMain(20000, -1);
}