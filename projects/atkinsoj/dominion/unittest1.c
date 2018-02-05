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
int testShuffle() {

    // Build a canned game state. Mostly adapted from initializeGame().
    struct gameState* state = malloc(sizeof(struct gameState));
    state->numPlayers = 2;

    // TODO: Do I need to initialize the supply cards?
    state->supplyCount[curse] = 10;
    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 8;
    state->supplyCount[copper] = 46;  // 60 - (7 * # of players)
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    // Create all of the cards for player 1 in the discard pile.
    // TODO: Add a separate test case for a non-empty deck.
    int player = 1;

    state->discardCount[player] = 0;
    state->deckCount[player] = 0;

    // 3 estate cards at the beginning of the player's deck.
    for (int j = 0; j < 3; j++)
    {
        state->deck[player][j] = estate;
        state->deckCount[player]++;
    }
    // 7 copper cards at the end of the player's deck.
    for (int j = 3; j < 10; j++)
    {
        state->deck[player][j] = copper;
        state->deckCount[player]++;
    }

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;
    state->handCount[state->whoseTurn] = 0;


    int ret = shuffle(player, state);

    // FIXME: Improve log statements.
    printf("Deck and discard counts after shuffle: %d, %d\n",
            state->deckCount[player],
            state->discardCount[player]);

    // Test oracle 1: confirm all of the discards are moved to the deck.
    int r = 0;
    r += assertTrue(ret == 0, "Function return value is 0");
    r += assertTrue(state->discardCount[player] == 0, "Discard count is 0");
    r += assertTrue(state->deckCount[player] == 3 + 7, "Deck count is 10");

    // Test oracle 2: count the # of estates and coppers.
    int estateCount = 0;
    int copperCount = 0;
    int orderChanged = 0;
    for (int i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == estate) {
            estateCount++;
            if (i > 2)
            {
                orderChanged = 1;
            }
        } else if (state->deck[player][i] == copper)
        {
            copperCount++;
            if (i < 3)
            {
                orderChanged = 1;
            }
        } else
        {
            // Found a card that wasn't in the original discard pile. Fail test.
            r += assertTrue(state->deck[player][i] == copper, "No new cards introduced");
        }
    }

    r += assertTrue(estateCount == 3, "estateCount is 3");
    r += assertTrue(copperCount == 7, "copperCount is 7");


    // Test oracle 3: confirm the order has changed.
    // Note: this test will fail on very rare cases where the
    // shuffle is identical to the input state.
    r += assertTrue(orderChanged == 1, "the order of the cards was changed");

    // Cleanup.
    free(state);

    return r;
}
