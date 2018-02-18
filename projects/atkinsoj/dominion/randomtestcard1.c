#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelper.h"

// FIXME: Should I test cardEffect() or cardEffectAdventurer()?
// FIXME: If the former, should I randomize everything?

void testMain(int iterations, int seed) {

    if (seed == -1) {
        // If no seed provided, use the system clock.
        seed = (int)time(NULL);
    }
    srand(seed);

    printf("Starting test of %d iterations with seed %d.\n", iterations, seed);

    int card = village;
    struct gameState G, initialG;
    int playerCount;
    int choice1, choice2, choice3, handPos;
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

        // Randomize choice1, choice2, and choice3
        choice1 = rand() % 256;
        choice2 = rand() % 256;
        choice3 = rand() % 256;

        // FIXME: randomize bonus

        // Clone G so I can compare it. Logic taken from Lesson 11.
        memcpy(&initialG, &G, sizeof(struct gameState));


        //FIXME: switched to use cardEffectVillage()
        result = cardEffectVillage(&G, handPos, G.whoseTurn);

//        int result = cardEffect(card, choice1,choice2,choice3, &G, handPos, &p);


        // Test oracle 1: basics.
        r = 0;
        r += assertEqual(0, result, "Response value is 0");
        r += assertEqual(initialG.whoseTurn, G.whoseTurn, "The player turn is unchanged");
        r += assertEqual(initialG.numPlayers, G.numPlayers, "player count is unchanged");

        // Test oracle 2: verify +1 card for the current player.
        r += assertEqual(initialG.handCount[G.whoseTurn], G.handCount[G.whoseTurn],
                         "hand count increased by 0 (+1 - 1 played Village)");
        currentCard = initialG.deck[G.whoseTurn][initialG.deckCount[G.whoseTurn] - 1];
        // TODO: What if deck and discard are both empty?
        if (G.deckCount[G.whoseTurn] == initialG.deckCount[G.whoseTurn] - 1) {
            // No shuffling occurred. Verify that a normal card-draw happened.
            r += assertEqual(currentCard,
                             G.hand[G.whoseTurn][handPos],
                             "New card in hand equals the card previously on top of the deck");
        } else {
            // Verify that shuffling occurred as expected.
            r += assertEqual(fullDeckCount(G.whoseTurn, currentCard, &initialG),
                            fullDeckCount(G.whoseTurn, currentCard, &G),
                            "The card added to the hand came from the deck or discards.");
            r += assertEqual(initialG.deckCount[G.whoseTurn] + initialG.discardCount[G.whoseTurn],
                             G.deckCount[G.whoseTurn] + G.discardCount[G.whoseTurn] + 1,
                             "After shuffle, deck + discard count is equivalent (+1 card)");
        }

        // Test oracle 3: verify +2 actions for the current player.
        r += assertEqual(initialG.numActions +2, G.numActions, "numActions is +2");
        r += assertEqual(initialG.playedCardCount + 1, G.playedCardCount, "playedCardCount is +1");
        r += assertEqual(card, G.playedCards[G.playedCardCount - 1], "last played card is a Village");

        // Test oracle 4: verify the remaining state for the current player is unchanged.
        r += assertEqual(initialG.numBuys, G.numBuys, "numBuys is unchanged");

        // Test oracle 5: verify no changes for the other players.

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
    testMain(200000, -1);
}