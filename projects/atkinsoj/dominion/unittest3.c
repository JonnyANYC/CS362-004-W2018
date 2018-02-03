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
void testIsGameOver()
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

    //initialize first player's turn
    state->outpostPlayed = 0;
    state->phase = 0;
    state->numActions = 1;
    state->numBuys = 1;
    state->playedCardCount = 0;
    state->whoseTurn = 0;
    state->handCount[state->whoseTurn] = 0;
