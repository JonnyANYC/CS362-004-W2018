#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testHelper.h"

// FIXME: Should I test cardEffect() or cardEffectAdventurer()?
// FIXME: If the former, should I randomize everything?

int main() {

    // srand(time(NULL));
    // FIXME: debug
    srand(1);

    int card = adventurer;
    struct gameState G, initialG;
    int playerCount;
    int choice1, choice2, choice3, handPos;

    // TODO: Extract method.

    // Run the test many times.
    int i;
    for (i = 0; i < 20000; i++) {

        // Start with a completely random gameState.
        randomizeGameState(G);

        // Random but sane player count (1 .. MAX_PLAYERS)
        playerCount = rand() % (MAX_PLAYERS - 1) + 1;

        G.whoseTurn = rand() % playerCount;

        // Random but sane state for the player piles.
        // TODO: Extract method
        int p;
        for (p = 0; p < playerCount; p++) {

            // The hand must be non-empty to play a card.
            // And save cards for other piles. (1 .. MAX_HAND - 2)
            G.handCount[p] = rand() % (MAX_HAND - 3) + 1;
            //randomizePile(G.hand[p], G.handCount[p]);

            G.deckCount[p] = rand() % (MAX_DECK - G.handCount[p]);
            randomizePile(G.deck[p], G.deckCount[p]);

            if (MAX_DECK - G.handCount[p] - G.deckCount[p] <= 0) {
                G.discardCount[p] = 0;
                //randomizePile(G.discard[p], G.discardCount[p]);
            } else {
                G.discardCount[p] = rand() % (MAX_DECK - G.handCount[p] - G.deckCount[p]);
            }
        }

        // Random but sane state for the current turn
        handPos = rand() % G.handCount[G.whoseTurn];

        // FIXME: Debug
        printf("iter %d: active player %d of %d has: deck %d discard %d hand %d actions %d buys %d played %d handpos %d\n", i, G.whoseTurn, playerCount, G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn], G.handCount[G.whoseTurn], G.numActions, G.numBuys, G.playedCardCount, handPos);

        // Randomize choice1, choice2, and choice3
        // The last card in the CARD enum is the highest acceptable value.
        choice1 = rand() % (LAST_CARD + 1);
        choice2 = rand() % (LAST_CARD + 1);
        choice3 = rand() % (LAST_CARD + 1);

        // FIXME: randomize bonus

        // Clone G so I can compare it. Logic taken from Lesson 11.
        memcpy(&initialG, &G, sizeof(struct gameState));

        int result = cardEffect(card, choice1,choice2,choice3, &G, handPos, &p);

        //int result = drawCard(G.whoseTurn, &G);

        // Test oracle 1: basics.
        assertEqual(0, result, "Response value is 0");
        assertEqual(initialG.whoseTurn, G.whoseTurn, "The player turn is unchanged");
        assertEqual(initialG.numPlayers, G.numPlayers, "player count is unchanged");

        // Test oracle 2: validate changes for the current player.
        assertTrue(G.handCount[G.whoseTurn] > initialG.handCount[G.whoseTurn], "handCount increased");
        assertTrue(G.handCount[G.whoseTurn] < initialG.handCount[G.whoseTurn] + 3, "handCount increased by 2 or less.");
        assertTrue(G.discardCount[G.whoseTurn] > initialG.discardCount[G.whoseTurn] + 1, "discardCount increased by 2 at least");
        assertTrue(G.deckCount[G.whoseTurn] < initialG.deckCount[G.whoseTurn] - 1, "deckCount decreased by at least 2.");

        assertEqual(initialG.numActions, G.numActions, "numActions is unchanged");
        assertEqual(initialG.numBuys, G.numBuys, "numBuys is unchanged");
        assertEqual(initialG.playedCardCount, G.playedCardCount, "playedCardCount is unchanged");

        // FIXME: Handle reshuffles of the deck.

        // FIXME: Not checking the actual cards yet!

        // Test oracle 3: validate no changes for the other players.
        // TODO: extract method
        for (p = 0; p < playerCount && p != G.whoseTurn; p++) {

            assertEqual(initialG.handCount[p], G.handCount[p], "handCount is unchanged for other players.");
            assertEqual(initialG.discardCount[p], G.discardCount[p], "discardCount is unchanged for other players.");
            assertEqual(initialG.deckCount[p], G.deckCount[p], "deckCount is unchanged for other players.");
        }

        // FIXME: more tests please!

    }
    // FIXME: Output results
}