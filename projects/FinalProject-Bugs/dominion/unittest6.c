/*The logic in the case statement for feast seems to be incorrect.  On line 762 Instead of updating the coins 
tally, it should enter the while loop and allowing players to gain a card up to 5 coins without taking into 
account how much coins the player has.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
//#include "unittest_assert.c"

void assert(int condition) {
	if (condition)
		printf("assertion passe\n");
	else
		printf("assertion not pass\n");
}

int main()
{
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, sea_hag, treasure_map
	};

	int playernum = 2;
	int seed = 100;
	int result = 0;
	int currentPlayer = 0;
	int bonus = 0;

	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(playernum, k, seed, &G);
	// initialize game state described in test plan, 
	G.coins = 0;
	int choice1 = mine;
	int choice2 = 0;
	int choice3 = 0;
	//insert a feast in player's hand
	G.hand[currentPlayer][G.handCount[currentPlayer]] = feast;
	G.handCount[currentPlayer]++;

	printf("Start testing isGameOver().\n");
	result = cardEffect(feast,choice1,choice2,choice3,&G,G.hand[currentPlayer][G.handCount[currentPlayer]-1],&bonus);
	result = buyCard(copper, &G);
	assert(result == -1);
	printf("actual value of result is:%d\n", result);

	printf("bug 6 test complete\n");
}
