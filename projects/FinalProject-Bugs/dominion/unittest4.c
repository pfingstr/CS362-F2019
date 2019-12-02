/*There is a bug in the isGameOver function. While checking if there are 3 cards with a card count of 0, it 
only loops through 25 cards.*/
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

	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(playernum, k, seed, &G);
	//set curse, cards >25 to be 0 in supply,so there are 3 cards are at 0, the game should end
	G.supplyCount[0] = 0;
	G.supplyCount[25] = 0;
	G.supplyCount[26] = 0;

	printf("Start testing isGameOver().\n");
	result = isGameOver(&G);
	assert(result == 1);
	printf("actual value of result is:%d\n", result);

	printf("bug 4 test complete\n");
}
