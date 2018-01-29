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
void testShuffle()
{
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
    state->deckCount[player] = 0;
    state->discardCount[player] = 0;
    for (int j = 0; j < 3; j++)
    {
        state->discard[player][j] = estate;
        state->discardCount[player]++;
    }
    for (int j = 3; j < 10; j++)
    {
        state->discard[player][j] = copper;
        state->discardCount[player]++;
    }

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;
    state->handCount[state->whoseTurn] = 0;

    // FIXME: Replace bogus log statement with something useful.
    printf("Deck count now: %d\n", state->deckCount[player]);

    shuffle(player, state);

    // Test oracle 1: confirm all of the discards are moved to the deck.
    assert(state->discardCount[player] == 0);
    assert(state->deckCount[player] == 3 + 10);

    // Test oracle 2: count the # of estates and coppers.
    int estateCount = 0;
    int copperCount = 0;
    int orderChanged = 0;
    for (int i = 0; i < state->discardCount[player]; i++)
    {
        if (state->deck[player][j] == estate) {
            estateCount++;
            if (i > 2)
            {
                orderChanged = 1;
            }
        } else if (state->deck[player][j] == copper)
        {
            copperCount++;
            if (i < 3)
            {
                orderChanged = 1;
            }
        } else
        {
            assert(state->deck[player][j] == copper);
        }
    }

    assert(estateCount == 3);
    assert(copperCount == 10);

    // Test oracle 3: confirm the order has changed.
    // Note: this test will fail on very rare cases where the
    // shuffle is identical to the input state.
    assert(orderChanged == 1);

    // Cleanup.
    free(state);
}