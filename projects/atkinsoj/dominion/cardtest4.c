#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

/*********************************************************************
** Program Filename:
** Author: Jon Atkinson
** Date: 2/3/2018
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

int testGreatHall() {

    // Build a canned game state.
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
    state->hand[player][4] = great_hall;

    addCards(state->discard[player], copper, 2);
    state->discardCount[player] = 2;
    state->discard[player][1] = gold;


    // TODO: Do I need to initialize the supply cards?
    state->supplyCount[curse] = 10;
    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 8;
    state->supplyCount[copper] = 46;  // 60 - (7 * # of players)
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;

    int choice1 = -1, choice2 = -1, choice3 = -1;
    int handPos = 4;
    int* bonus = &player;  // Bogus pointer that isn't needed
    int ret = cardEffect(great_hall, choice1, choice2, choice3, state, handPos, bonus);


    // Test oracle
    int r = 0;
    r += assertTrue(ret == 0, "Successful execution.");


    r += assertEqual(1, state->numActions, "1 actions remaining to be played.");

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
