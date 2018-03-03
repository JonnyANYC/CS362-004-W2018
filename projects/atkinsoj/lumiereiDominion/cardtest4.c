#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testSuite.h"

int testGreatHall() {

    // Build a canned game state.
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    int player = 1;

    addCards(state->deck[player], copper, 13);
    state->deckCount[player] = 13;
    state->deck[player][0] = gold;
    state->deck[player][4] = gold;
    state->deck[player][12] = gold;

    addCards(state->hand[player], copper, 5);
    state->handCount[player] = 5;
    state->hand[player][0] = gold;
    state->hand[player][4] = great_hall;

    addCards(state->discard[player], copper, 2);
    state->discardCount[player] = 2;
    state->discard[player][1] = gold;

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;

    int choice1 = -1, choice2 = -1, choice3 = -1;
    int handPos = 5;
    int* bonus = &player;  // Bogus pointer that isn't needed
    int ret = cardEffect(great_hall, choice1, choice2, choice3, state, handPos, bonus);

    // Test oracle
    int r = 0;
    r += assertTrue(ret == 0, "Successful execution.");

    // FIXME: Find out why the card isn't being pulled out and new cards fetched.

    // Actions are not decremented in cardEffect().
    r += assertEqual(1 + 1, state->numActions, "Available actions is increased by 1.");

    r += assertEqual(2, state->discardCount[player], "Still 2 discarded cards.");
    int playedCardCount = state->playedCardCount;
    r += assertEqual(1, playedCardCount, "One played card.");
    r += assertEqual(great_hall, state->playedCards[playedCardCount - 1], "Last played card is a great hall.");

    int handCount = state->handCount[player];
    r += assertEqual(5, handCount, "5 cards in hand.");
    r += assertEqual(gold, state->hand[player][handPos], "Newest card in deck is a gold.");
    r += assertEqual(13 - 1, state->deckCount[player], "12 cards in deck.");


    // Cleanup.
    free(state);

    return r;
}
