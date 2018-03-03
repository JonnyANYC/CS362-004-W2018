#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testSuite.h"

void setNonEmptySupplyPiles(struct gameState* state) {
    state->supplyCount[curse] = 1;
    state->supplyCount[adventurer] = 1;
    state->supplyCount[council_room] = 1;
    state->supplyCount[feast] = 1;
    state->supplyCount[gardens] = 1;
    state->supplyCount[mine] = 1;
    state->supplyCount[remodel] = 1;
    state->supplyCount[smithy] = 1;
    state->supplyCount[village] = 1;
    state->supplyCount[baron] = 1;
    state->supplyCount[great_hall] = 1;
    state->supplyCount[minion] = 1;
    state->supplyCount[steward] = 1;
    state->supplyCount[tribute] = 1;
    state->supplyCount[ambassador] = 1;
    state->supplyCount[cutpurse] = 1;
    state->supplyCount[embargo] = 1;
    state->supplyCount[outpost] = 1;
    state->supplyCount[salvager] = 1;
}


int testIsGameOverNotYet() {
    // Build a canned game state.
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    // Set all the supply piles as non-zero, except for 2.
    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 1;
    setNonEmptySupplyPiles(state);
    state->supplyCount[curse] = 0;
    state->supplyCount[salvager] = 0;

    state->supplyCount[copper] = 46;  // 60 - (7 * # of players)
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    int ret = isGameOver(state);

    // Cleanup.
    free(state);

    // Test oracle
    int r = 0;
    r += assertTrue(ret == 0, "Game is not over.");
    return r;
}

int testIsGameOverEmptyProvincePile() {
    // Build a canned game state.
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    // Set all the supply piles as non-zero, except for the province pile.
    state->supplyCount[curse] = 10;
    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 0;
    setNonEmptySupplyPiles(state);

    state->supplyCount[copper] = 46;  // 60 - (7 * # of players)
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    int ret = isGameOver(state);

    // Cleanup.
    free(state);

    // Test oracle
    int r = 0;
    r += assertTrue(ret == 1, "Game is over.");
    return r;
}

int testIsGameOverThreeEmptySupplyPiles() {
    // Build a canned game state. Mostly adapted from initializeGame().
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    state->supplyCount[curse] = 10;
    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 8;

    // Set all the supply piles as non-zero, except for three of them.
    setNonEmptySupplyPiles(state);
    state->supplyCount[minion] = 0;
    state->supplyCount[steward] = 0;
    state->supplyCount[tribute] = 0;

    state->supplyCount[copper] = 46;  // 60 - (7 * # of players)
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    int ret = isGameOver(state);

    // Cleanup.
    free(state);

    // Test oracle
    int r = 0;
    r += assertTrue(ret == 1, "Game is over.");
    return r;
}
