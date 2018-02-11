#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"


// FIXME: Should I test cardEffect() or cardEffectAdventurer()?
// FIXME: If the former, should I randomize everything?

int main() {

    int card = adventurer;

    // FIXME: Randomize choice1, choice2, and choice3

    // FIXME: Randomize gameState

    // FIXME: randomize handPos

    // FIXME: randomize bonus

    int result = cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

    // FIXME: Validate result

    // FIXME: compare to the expected gameState

    // FIXME: Output results
}