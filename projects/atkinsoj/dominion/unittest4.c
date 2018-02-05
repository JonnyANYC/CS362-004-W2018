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
int testScoreFor() {
    // Build a canned game state. Mostly adapted from initializeGame().
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;


    int player = 1;
    addCards(state->deck[player], copper, 13);
    state->deckCount[player] = 13;
    state->deck[player][0] = province;
    state->deck[player][4] = estate;
    state->deck[player][5] = duchy;

    addCards(state->hand[player], copper, 5);
    state->handCount[player] = 5;

    addCards(state->discard[player], copper, 2);
    state->discardCount[player] = 2;
    state->discard[player][1] = curse;

    int ret = scoreFor(player, state);

    // Cleanup.
    free(state);

    // Test oracle
    int r = 0;
    r += assertEqual(9, ret, "Score is 9.");
    return r;
}


int testScoreForWithGardens() {
    // Build a canned game state. Mostly adapted from initializeGame().
    struct gameState *state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    int player = 1;
    addCards(state->deck[player], copper, 13);
    state->deckCount[player] = 13;
    state->deck[player][0] = province;
    state->deck[player][4] = estate;
    state->deck[player][5] = duchy;
    state->deck[player][7] = gardens;

    addCards(state->hand[player], copper, 5);
    state->handCount[player] = 5;
    state->deck[player][7] = curse;


    addCards(state->discard[player], copper, 10);
    state->discardCount[player] = 10;
    state->discard[player][3] = estate;

    int ret = scoreFor(player, state);

    // Cleanup.
    free(state);

    // Test oracle
    int r = 0;
    r += assertEqual(6 + 1 + 3 + 2 -1 + 1, ret, "Score is 12.");
    return r;
}
