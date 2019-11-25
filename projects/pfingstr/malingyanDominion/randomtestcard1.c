#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#define CARD_TEST "Baron"

int main (int argc, char** argv) {
        int kingdom[10] = {adventurer, gardens, great_hall, village, council_room, mine, cutpurse, sea_hag, tribute, smithy};
        int testSuccessful = 0;
        int testFailed = 0;
        int i; 
        int tests = 100;

        for(i = 0; i < tests; i++) {

                int num_players = rand() % 4;
                int p = 0;
                //int op = 1;
                int rand_seed = rand();
                struct gameState *g = malloc(sizeof(struct gameState));
                initializeGame(num_players, kingdom, rand_seed, g);
                //Randomize opponents info was useful for testing
                //int prev_op_deck = g->deckCount[op] = rand() % MAX_DECK;
                //int prev_op_discard = g->discardCount[op] = rand() % MAX_DECK;
                //int prev_op_hand = g->handCount[op] = rand() % MAX_HAND;
                //int prev_op_act = g->numActions;

                //int prev_p_deck = g->deckCount[p] = rand() % MAX_DECK;
                //int prev_p_discard = g->discardCount[p] = rand() % MAX_DECK;
                int prev_p_hand = g->handCount[p] = rand() % MAX_HAND;
                //int prev_p_act = g->numActions; 
                int prev_p_buys = g->numBuys;
                int prev_p_coins = g->coins;
                int prev_p_estate = g->supplyCount[estate] = rand() % 20;
                //printf("coins: %d\n", prev_p_coins);
                //printf("Pre P - deck:%d    discard:%d    hand:%d    act:%d\n", prev_p_deck, prev_p_discard, prev_p_hand, prev_p_act);
                cardEffect(baron, 0, 0, 0, g, 0, 0);
                //printf("post coins: %d\n", g->coins);
                //printf("post P - deck:%d    discard:%d    hand:%d    act:%d\n\n", g->deckCount[p], g->discardCount[p], g->handCount[p], g->numActions);
              
		if ((prev_p_estate - 2 == g->supplyCount[estate]) && (prev_p_buys + 1 == g->numBuys) 
                && (prev_p_hand +1 == g->handCount[p]) && (prev_p_coins + 2 == g->coins))
		{testSuccessful++;}
		else
		{testFailed++;}
                free(g);
        }
        printf("Random Test 1: %s Card.\n", CARD_TEST);
        printf("Total Successful Tests: %d\nOut of: %d games\nTotal Failed Tests: %d", testSuccessful, tests, testFailed);
        return 0;
}
//gcc -Wall -fprofile-arcs -ftest-coverage -o randomtestcard1 dominion.c rngs.c randomtestcard1.c

