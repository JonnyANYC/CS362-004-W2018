#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testSuite.h"

int testAdventurer() {

    // Build a canned game state.
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    int player = 1;

    addCards(state->deck[player], estate, 13);
    state->deckCount[player] = 13;
    state->deck[player][12] = copper;
    state->deck[player][10] = silver;
    state->deck[player][8] = gold;

    addCards(state->hand[player], copper, 5);
    state->handCount[player] = 5;
    state->hand[player][0] = gold;
    state->hand[player][4] = adventurer;

    addCards(state->discard[player], copper, 2);
    state->discardCount[player] = 2;
    state->discard[player][1] = gold;

    //initialize player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = player;

    int choice1 = -1, choice2 = -1, choice3 = -1;
    int handPos = 4;
    int* bonus = &player;  // Bogus pointer that isn't needed
    int ret = cardEffect(adventurer, choice1, choice2, choice3, state, handPos, bonus);


    // Test oracle
    int r = 0;
    r += assertTrue(ret == 0, "Successful execution.");

    // Actions are not decremented in cardEffect().
    r += assertEqual(1, state->numActions, "Available actions is still the default of 1.");

    // Next should fail because of intentional bug: a silver and following estate is discarded.
    r += assertEqual(2 + 1, state->discardCount[player], "5 discarded cards.");
    int playedCardCount = state->playedCardCount;
    // Next two should pass, but cardEffectAdventurer() fails to discard the adventurer card. Bug!
    r += assertEqual(1, playedCardCount, "One played card.");
    r += assertEqual(adventurer, state->playedCards[playedCardCount - 1], "Last played card is an adventurer.");

    int handCount = state->handCount[player];
    r += assertEqual(5 + 2, handCount, "7 cards in hand.");
    r += assertEqual(copper, state->hand[player][handCount - 2], "Second to last card in deck is a copper.");
    // Next two should fail because of intentional bug: a silver and following estate are discarded.
    r += assertEqual(silver, state->hand[player][handCount - 1], "Last card in deck is a silver.");
    r += assertEqual(13 - 3, state->deckCount[player], "10 cards in deck.");

    // Cleanup.
    free(state);

    return r;
}
