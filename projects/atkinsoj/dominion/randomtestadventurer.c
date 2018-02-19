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

    struct gameState G, initialG;
    int playerCount, handPos;
    int result, r, totalFailedCases = 0;
    int rndSum, rnd1 = -1, rnd2 = -1, rnd3 = -1;
    int currentCard, countTreasureCards;
    int i, p, j;

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
            // This includes boundaries of 0 and a sum of MAX_HAND
            while (rndSum > MAX_HAND) {
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
        if (G.handCount[G.whoseTurn] == 0) {
            // Set handPos manually to avoid the divide-by-zero error.
            handPos = 0;
        } else {
            handPos = rand() % G.handCount[G.whoseTurn];
        }

        int temphand[MAX_HAND];
        int drawntreasure = 0;  // always zero in the code


        // Clone G so I can compare it. Logic taken from Lesson 11.
        memcpy(&initialG, &G, sizeof(struct gameState));

        result = cardEffectAdventurer(&G, G.whoseTurn, temphand, drawntreasure);


        // Test oracle 1: basics.
        r = 0;
        r += assertEqual(0, result, "Response value is 0");
        r += assertEqual(initialG.whoseTurn, G.whoseTurn, "The player turn is unchanged");
        r += assertEqual(initialG.numPlayers, G.numPlayers, "player count is unchanged");

        // Test oracle 2: validate changes for the current player.

        // Verify there are 2 additional treasure cards in the hand now.
        countTreasureCards = 0;
        for (j = initialG.handCount[G.whoseTurn]; j < MAX_HAND && j < G.handCount[G.whoseTurn]; j++) {
            currentCard = G.hand[G.whoseTurn][j];
            if (currentCard == gold || currentCard == silver || currentCard == copper) {
                countTreasureCards++;
            } else {
                // A non-treasure card was added to the hand. Fail an assert.
                r += assertEqual(gold, currentCard, "Only treasure cards added to the hand");
            }
        }

        if (countTreasureCards < 2) {
            // Check if there are no more treasure cards in the deck, since this is valid.
            for (j = 0; j < G.deckCount[G.whoseTurn]; j++) {
                currentCard = G.deck[G.whoseTurn][j];
                r += assertTrue(currentCard != gold && currentCard != silver && currentCard != copper,
                                "Less than 2 treasure cards added to the hand because deck has no more");
            }
        } else {
            r += assertEqual(2, countTreasureCards, "2 treasure cards added to the hand");
        }

        r += assertEqual(initialG.deckCount[G.whoseTurn] + initialG.discardCount[G.whoseTurn],
                         G.deckCount[G.whoseTurn] + G.discardCount[G.whoseTurn] + countTreasureCards,
                        "After shuffle, deck + discard count is equivalent (less the treasures)");

        r += assertEqual(initialG.numActions, G.numActions, "numActions is unchanged");
        r += assertEqual(initialG.numBuys, G.numBuys, "numBuys is unchanged");
        r += assertEqual(initialG.playedCardCount, G.playedCardCount, "playedCardCount is unchanged");

        // Test oracle 3: validate no changes for the other players.

        // TODO: extract method
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
    testMain(20000, -1);    // 1518600903 1518601501);
}