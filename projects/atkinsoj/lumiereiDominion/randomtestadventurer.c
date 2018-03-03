// Ian Lumiere
// February 17, 2018
// CS 362
// Assignment 4
// randomtestadventurer.c
// This program implements a random tester for the adventurer card

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
int handCountFailures = 0;
int deckCountFailures = 0;
int cardEffectFailures = 0;
int discardFailures = 0;
int treasureFailures = 0;
int shuffleFailures = 0;
int failedTestRuns = 0;

// This is the actual test suite that takes a random input and tests adventurer and its related functions
void adventurerTest(struct gameState *currentGameTest, int playerCount){
    // Copy the gameState for comparison testing
    int coin_bonus = 0;
    struct gameState copyGameTest;
    memcpy(&copyGameTest, currentGameTest, sizeof(struct gameState));
    
    // Set a flag to see if the current test run fails
    int currentFail = 0;
    
    // Set up the treasureTracker
    int treasureTracker = 0;
    
    // Set up the testHand for checking the treasures drawn
    int testHand[500];
    int cardIndex = 0;
    
    // Run the card function on the currentGameTest
    int cardEffectTestResult = cardEffect(adventurer, 0, 0, 0, currentGameTest, 0, &coin_bonus);
    
    // Manually call the functions performed by the adventurer card
    // Run the loop until the player has drawn 2 treasure cards
    while(treasureTracker < 2){
        // Check to see if the deck needs to be refilled with a shuffle
        if(copyGameTest.deckCount[playerCount] == 0){
            int shuffleTestResult = shuffle(playerCount, &copyGameTest);
            
            if(copyGameTest.deckCount[playerCount] >= 1 && shuffleTestResult == -1){
                shuffleFailures += 1;
                currentFail += 1;
            }
        }
        
        // Draw a card
        int drawCardTest1 = drawCard(playerCount, &copyGameTest);
        
        if(drawCardTest1 == -1 && copyGameTest.deckCount[playerCount] != 0){
            drawFailures += 1;
            currentFail += 1;
        }
        
        // Check if the card drawn was a treasure card, if so, increment the treasureTracker
        int newCard = copyGameTest.hand[playerCount][copyGameTest.handCount[playerCount] - 1];
        
        if(newCard == gold){
            treasureTracker += 1;
        }
        else if(newCard == silver){
            treasureTracker += 1;
        }
        else if(newCard == copper){
            treasureTracker += 1;
        }
        else{
            // Don't keep the card if it isn't a treasure card
            testHand[cardIndex] = newCard;
            copyGameTest.handCount[playerCount]--;
            cardIndex += 1;
        }
        
    }
    
    // Discard the cards that weren't treasure cards that were drawn
    while(cardIndex > 0){
        copyGameTest.discard[playerCount][copyGameTest.discardCount[playerCount]++] = testHand[cardIndex-1];
        cardIndex -= 1;
    }
    
    // Compare the treasure count for the tester and the copy to test if the correct amount of treasure was drawn
    // Check the hands of each game
    int j;
    int currentTreasureCount;
    int currentCard;
    for(j = 0; j < currentGameTest->handCount[playerCount]; j++){
        currentCard = currentGameTest->hand[playerCount][j];
        if(currentCard == gold){
            currentTreasureCount += 1;
        }
        else if(currentCard == silver){
            currentTreasureCount += 1;
        }
        else if(currentCard == copper){
            currentTreasureCount += 1;
        }
    }
    
    int n;
    int copyTreasureCount;
    int copyCard;
    for(n = 0; n < copyGameTest.handCount[playerCount]; n++){
        copyCard = copyGameTest.hand[playerCount][n];
        if(copyCard == gold){
            copyTreasureCount += 1;
        }
        else if(copyCard == silver){
            copyTreasureCount += 1;
        }
        else if(copyCard == copper){
            copyTreasureCount += 1;
        }
    }
    
    if(currentTreasureCount != copyTreasureCount){
        treasureFailures += 1;
        currentFail += 1;
    }
    
    // Check the test results
    if(cardEffectTestResult != 0){
        cardEffectFailures += 1;
        currentFail += 1;
    }
    
    // Check the hand count, deck count, and discard count for the currentGameTest and copyGameTest
    if(currentGameTest->handCount[playerCount] != copyGameTest.handCount[playerCount]){
        handCountFailures += 1;
        currentFail += 1;
    }
    
    if(currentGameTest->deckCount[playerCount] != copyGameTest.deckCount[playerCount]){
        deckCountFailures += 1;
        currentFail += 1;
    }
    
    if(currentGameTest->discardCount[playerCount] != copyGameTest.discardCount[playerCount]){
        discardFailures += 1;
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
    int treasuresInDeck;
    
    printf("This program will test the Adventurer card in dominion.c. Please stand by for results:\n");
    
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
        currentGameTest.handCount[playerCount] = (rand() % 498) + 3;
        currentGameTest.deckCount[playerCount] = (rand() % 498) + 3;
        currentGameTest.discardCount[playerCount] = 0;
        currentGameTest.playedCardCount = rand() % 499;
        currentGameTest.numActions = rand() % 10;
        
        // Randomly fill deck with treasures (need at least 3)
        treasuresInDeck = (rand() % (currentGameTest.deckCount[playerCount] - 2)) + 3;
        int k;
        int treasureToUse;
        int treasureTypes[] = {gold, silver, copper};
        for(k = 0; k < treasuresInDeck; k++){
            // Randomly choose a treasure card and put it in the player's deck
            treasureToUse = rand() % 3;
            
            // Put in a gold if 0
            if(treasureToUse == 0){
                currentGameTest.deck[playerCount][k] = treasureTypes[0];
            }
            
            // Put in a silver if 1
            else if(treasureToUse == 1){
                currentGameTest.deck[playerCount][k] = treasureTypes[1];
            }
            
            // Put in a copper if 2
            else{
                currentGameTest.deck[playerCount][k] = treasureTypes[2];
            }
            
        }
        
        // Run the test suite with the fully built random input
        adventurerTest(&currentGameTest, playerCount);
    }
    
    // Output the results
    printf("The following are the results from the test:\n");
    
    if(drawFailures + discardFailures + handCountFailures + cardEffectFailures + deckCountFailures + treasureFailures + shuffleFailures > 0){
        printf("There were %d successful test runs.\nThere were %d failed test runs.\n", numberOfTests - failedTestRuns, failedTestRuns);
        printf("There were %d failed individual tests!\n", drawFailures + discardFailures + handCountFailures + cardEffectFailures + deckCountFailures + treasureFailures + shuffleFailures);
        printf("Here is the failure breakdown:\n");
        printf("cardEffect() failed %d times.\n", cardEffectFailures);
        printf("There were %d failures to get the correct hand count.\n", handCountFailures);
        printf("There were %d failures to get the correct deck count.\n", deckCountFailures);
        printf("There were %d failures to get the correct discard count.\n", discardFailures);
        printf("There were %d failures to get the correct number of treasures.\n", treasureFailures);
        printf("There were %d failures to shuffle properly.\n", shuffleFailures);
        printf("drawCard() failed %d times.\n", drawFailures);
        
    }
    else{
        printf("There were 0 failed tests!\n There were %d passed tests!\n", numberOfTests);
        printf("Great news! All tests passed!\n");
    }
    
    printf("See below for the test coverage:\n");
    
    return 0;
}

