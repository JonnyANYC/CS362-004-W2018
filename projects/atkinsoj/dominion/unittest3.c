#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

/*********************************************************************
** Program Filename:
** Author: Jon Atkinson
** Date: 1/27/2018
** Description:
** Input:
** Output:
*********************************************************************/


/*********************************************************************
** Function:
** Description:
** Parameters:
** Returns:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
int testIsGameOverNotYet() {
    // Build a canned game state. Mostly adapted from initializeGame().
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 1;
    state->supplyCount[copper] = 46;  // 60 - (7 * # of players)
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    int ret = isGameOver(state);

    // Cleanup.
    free(state);

    // Test oracle
    int r = 0;
    // FIXME: Why is this assertion failing?
    r += assertTrue(ret == 0, "Game is not over.");
    return r;
}

int testIsGameOverEmptyProvincePile() {
    // Build a canned game state. Mostly adapted from initializeGame().
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    state->supplyCount[curse] = 10;
    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 0;
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
