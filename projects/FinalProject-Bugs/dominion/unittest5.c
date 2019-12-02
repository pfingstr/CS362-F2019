/*In the scoreFor function, the discardCount is being used for the deck count.*/

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
	int score = 0;
	int currentPlayer = 0;

	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(playernum, k, seed, &G);
	// initialize game state described in test plan, set 1 duchy in discard pile�� 2 duchy in deck and one estate in hand.
	G.deckCount[currentPlayer] = 2;
	G.discardCount[currentPlayer] = 1;
	G.handCount[currentPlayer] = 1;
	G.discard[currentPlayer][0] = duchy;
	G.hand[currentPlayer][0] = estate;
	G.deck[0][0] = duchy;
	G.deck[0][1] = duchy;
	G.deck[0][2] = -1;

	printf("Start testing isGameOver().\n");
	score = scoreFor(currentPlayer,&G);
	assert(score == 10);
	printf("actual value of score is:%d\n", score);

	printf("bug 5 test complete\n");
}
