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
void testScoreFor()
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

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;
    state->handCount[state->whoseTurn] = 0;
