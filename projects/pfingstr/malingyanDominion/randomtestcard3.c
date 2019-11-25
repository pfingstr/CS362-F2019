#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#define CARD_TEST "Tribute"

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
                int prev_p_act = g->numActions; 
                //int prev_p_buys = g->numBuys;
                //int prev_p_coins = g->coins;
                //int prev_p_estate = g->supplyCount[estate] = rand() % 10;
		
		cardEffect(tribute, 0, 0, 0, g, 0, 0);
	
		//printf("pre actions:%d post actions:%d\n", prev_p_act, g->numActions);
		//printf("%d, %d\n", g->hand[p][prev_p_hand], g->hand[p][prev_p_hand+1]);
		/*int x, gld, cpr, sil, est;
		gld = cpr = sil = est = 0;
		for(x = 0 ; x < g->handCount[p]; x++) 
		{
			if(g->hand[p][x] == gold)
			{gld++;}
			else if(g->hand[p][x] == silver)
			{sil++;}
			else if(g->hand[p][x] == copper)
			{cpr++;}
			else if(g->hand[p][x] == estate)
			{est++;}
		}
		printf("PRE: G:%d S:%d C:%d E:%d\n", gld,sil,cpr,est);
		
		cardEffect(tribute, 0, 0, 0, g, 0, 0);
		int pgld, pcpr, psil, pest;
		pgld = pcpr = psil = pest = 0;
		for(x = 0 ; x < g->handCount[p]; x++) 
		{
			if(g->hand[p][x] == gold)
			{pgld++;}
			else if(g->hand[p][x] == silver)
			{psil++;}
			else if(g->hand[p][x] == copper)
			{pcpr++;}
			else if(g->hand[p][x] == estate)
			{pest++;}
		}
		printf("POST: G:%d S:%d C:%d E:%d\n", pgld,psil,pcpr,pest);*/
		//printf("pre coins:%d post coins:%d\n", prev_p_coins, g->coins);
		//printf("Post OP - deck:%d    discard:%d    hand:%d\n", g->deckCount[op], g->discardCount[op], g->handCount[op]);
        //printf("Post P - deck:%d    discard:%d    hand:%d\n\n", g->deckCount[p], g->discardCount[p], g->handCount[p]);
		//Oponents deck count being decresed by 4 every play
		//Players hand count increasing by 2 every play.
		//Players num actions always increased by 4 every play of tribute meaning 
		//Adding two #4 cards (copper) every turn.
		
		if ((prev_p_hand + 2 == g->handCount[p]) && (prev_p_act + 2  == g->numActions))
                {testSuccessful++;}
                else
                {testFailed++;}
		free(g);
	}
       	printf("Random Test 3: %s Card.\n", CARD_TEST);
		printf("Total Successful Tests: %d\nOut of: %d games\nTotal Failed Tests: %d\n", testSuccessful, tests, testFailed);
        return 0;
}

//gcc -Wall -fprofile-arcs -ftest-coverage -o randomtestcard3 dominion.c rngs.c randomtestcard3.c