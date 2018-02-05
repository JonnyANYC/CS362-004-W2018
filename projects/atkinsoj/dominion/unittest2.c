#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testSuite.h"

int testFullDeckCount()
{
    // Build a canned game state and full deck for a player.
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    int player = 1;

    addCards(state->deck[player], copper, 13);
    state->deckCount[player] = 13;
    state->deck[player][0] = gold;
    state->deck[player][4] = gold;
    state->deck[player][5] = gold;

    addCards(state->hand[player], copper, 5);
    state->handCount[player] = 5;
    state->hand[player][0] = gold;
    state->hand[player][4] = gold;

    addCards(state->discard[player], copper, 2);
    state->discardCount[player] = 2;
    state->discard[player][1] = gold;

    int ret = fullDeckCount(player, gold, state);

    // Cleanup.
    free(state);

    // Test oracle: count should be 6.
    int r = 0;
    r += assertTrue(ret == 3 + 2 + 1, "Function return value is 6");

    return r;
}
