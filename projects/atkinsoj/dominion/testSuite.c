#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"


void setUpGame(struct gameState* state) {
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
}

void countTestResults(int ret, int* successes, int* fails, int* failed) {
    if (ret == 0) {
        (*successes)++;
    } else {
        (*fails)++;
        *failed = -1;
    }
}

void printTestResults(int successes, int fails) {
    printf("%d of %d tests passed.\n", successes, successes + fails);
}

void printTestSuiteResults(int failed) {
    if (failed == -1) {
        printf("TEST SUITE FAILED\n");
    } else {
        printf("ALL TESTS PASSED\n");
    }
}

int addCards(int* cardPile, int card, int cardCount)
{
    for (int i = 0; i < cardCount; i++)
    {
        cardPile[i] = card;
    }

    return cardCount;
}


int assertTrue(int bool, char* msg) {
    if (bool != 1) {
        // TODO: Print to stderr instead of stdout.
        printf("Failed assertion: %s\n", msg);
        return -1;
    } else {
        return 0;
    }
}


int assertEqual(int expected, int actual, char* msg) {

    if (expected == actual) {
        return 0;
    }

    // TODO: Print to stderr instead of stdout.
    printf("Failed assertion because %d != %d: %s\n", expected, actual, msg);
    return -1;
}

int main() {
    int ret, successes, fails, failed = 0;

    // unittest1
    printf("testing shuffle():\n");
    successes = 0, fails = 0;
    ret = testShuffle();
    countTestResults(ret, &successes, &fails, &failed);

    ret = testShuffleEmptyDeck();
    countTestResults(ret, &successes, &fails, &failed);

    printTestResults(successes, fails);

    // unittest2
    printf("testing fullDeckCount():\n");
    successes = 0, fails = 0;
    ret = testFullDeckCount();
    countTestResults(ret, &successes, &fails, &failed);
    printTestResults(successes, fails);

    // unittest3
    printf("testing isGameOver():\n");
    successes = 0, fails = 0;
    ret = testIsGameOverNotYet();
    countTestResults(ret, &successes, &fails, &failed);

    ret = testIsGameOverEmptyProvincePile();
    countTestResults(ret, &successes, &fails, &failed);

    ret = testIsGameOverThreeEmptySupplyPiles();
    countTestResults(ret, &successes, &fails, &failed);

    printTestResults(successes, fails);

    // unittest4
    printf("testing scoreFor():\n");
    successes = 0, fails = 0;
    ret = testScoreFor();
    countTestResults(ret, &successes, &fails, &failed);

    ret = testScoreForWithGardens();
    countTestResults(ret, &successes, &fails, &failed);

    printTestResults(successes, fails);

    // cardtest1
    printf("testing smithy:\n");
    successes = 0, fails = 0;
    ret = testSmithy();
    countTestResults(ret, &successes, &fails, &failed);
    printTestResults(successes, fails);

    // cardtest2
    printf("testing adventurer:\n");
    successes = 0, fails = 0;
    ret = testAdventurer();
    countTestResults(ret, &successes, &fails, &failed);
    printTestResults(successes, fails);

    // cardtest3
    printf("testing village:\n");
    successes = 0, fails = 0;
    ret = testVillage();
    countTestResults(ret, &successes, &fails, &failed);
    printTestResults(successes, fails);

    // cardtest4
    printf("testing great hall:\n");
    successes = 0, fails = 0;
    ret = testGreatHall();
    countTestResults(ret, &successes, &fails, &failed);
    printTestResults(successes, fails);


    // Output results.
    printTestSuiteResults(failed);
}
