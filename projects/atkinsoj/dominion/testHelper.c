#include "testHelper.h"

// TODO: Move the helper functions in testSuite.c into this file.

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
