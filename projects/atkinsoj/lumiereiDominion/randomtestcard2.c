// Ian Lumiere
// February 17, 2018
// CS 362
// Assignment 4
// randomtestcard2.c
// This program implements a random tester for the village card

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// Global Test Result Trackers
int drawFailures = 0;
int discardFailures = 0;
int handCountFailures = 0;
int deckCountFailures = 0;
int cardEffectFailures = 0;
int actionFailures = 0;
int failedTestRuns = 0;

// This is the actual test suite that takes a random input and tests village and its related functions
void villageTest(struct gameState *currentGameTest, int playerCount){
    // Copy the gameState for comparison testing
    int coin_bonus = 0;
    struct gameState copyGameTest;
    memcpy(&copyGameTest, currentGameTest, sizeof(struct gameState));
    
    // Set a flag to see if the current test run fails
    int currentFail = 0;
    
    // Run the card function on the currentGameTest
    int cardEffectTestResult = cardEffect(village, 0, 0, 0, currentGameTest, 0, &coin_bonus);
    
    // Manually call the functions performed by the village card
    int drawCardTest1 = drawCard(playerCount, &copyGameTest);
    int discardTest = discardCard(0, playerCount, &copyGameTest, 0);
    copyGameTest.numActions += 2;
    
    // Check the test results
    if(cardEffectTestResult != 0){
        cardEffectFailures += 1;
        currentFail += 1;
    }
    
    if(drawCardTest1 == -1 && copyGameTest.deckCount[playerCount] != 0){
        drawFailures += 1;
        currentFail += 1;
    }
    
    if(discardTest != 0){
        discardFailures += 1;
        currentFail += 1;
    }
    
    if(copyGameTest.numActions != currentGameTest->numActions){
        actionFailures += 1;
        currentFail += 1;
    }
    
    // Check the hand count and deck count for the currentGameTest and copyGameTest
    if(currentGameTest->handCount[playerCount] != copyGameTest.handCount[playerCount]){
        handCountFailures += 1;
        currentFail += 1;
    }
    
    if(currentGameTest->deckCount[playerCount] != copyGameTest.deckCount[playerCount]){
        deckCountFailures += 1;
        currentFail += 1;
    }
    
    // Check to see if there was a failed test, if so, mark the overall test run as a failure
    if(currentFail > 0){
        failedTestRuns += 1;
    }
    
}

int main(){
    // Seed the random number generator
    srand(time(NULL));
    
    // Set up the variables required for the test
    int numberOfTests = 120000;
    struct gameState currentGameTest;
    int playerCount;
    
    printf("This program will test the Village card in dominion.c. Please stand by for results:\n");
    
    // Run the loop for the requisite number of times
    int i;
    for(i = 0; i < numberOfTests; i++){
        // Create a game with random initializers
        // Get a random number of players between 1 and 4
        playerCount = rand() % 4;
        
        int newGame;
        for(newGame = 0; newGame < sizeof(struct gameState); newGame++){
            ((char*)&currentGameTest)[newGame] = rand() % 256;
        }
        
        // Get random numbers for the other things set up in a game
        currentGameTest.whoseTurn = playerCount;
        currentGameTest.handCount[playerCount] = rand() % 500;
        currentGameTest.deckCount[playerCount] = rand() % 500;
        currentGameTest.discardCount[playerCount] = rand() % 500;
        currentGameTest.playedCardCount = rand() % 499;
        currentGameTest.numActions = rand() % 10;
        
        // Run the test suite with the fully built random input
        villageTest(&currentGameTest, playerCount);
    }
    
    // Output the results
    printf("The following are the results from the test:\n");
    
    if(drawFailures + discardFailures + handCountFailures + cardEffectFailures + deckCountFailures + actionFailures > 0){
        printf("There were %d successful test runs.\nThere were %d failed test runs.\n", numberOfTests - failedTestRuns, failedTestRuns);
        printf("There were %d failed individual tests!\n", drawFailures + discardFailures + handCountFailures + cardEffectFailures + deckCountFailures + actionFailures);
        printf("Here is the failure breakdown:\n");
        printf("cardEffect() failed %d times.\n", cardEffectFailures);
        printf("There were %d failures to get the correct hand count.\n", handCountFailures);
        printf("There were %d failures to get the correct deck count.\n", deckCountFailures);
        printf("There were %d failures to get the correct number of actions.\n", actionFailures);
        printf("drawCard() failed %d times.\n", drawFailures);
        printf("discardCard() failed %d times.\n", discardFailures);
        
    }
    else{
        printf("There were 0 failed tests!\n There were %d passed tests!\n", numberOfTests);
        printf("Great news! All tests passed!\n");
    }
    
    printf("See below for the test coverage:\n");
    
    return 0;
}

