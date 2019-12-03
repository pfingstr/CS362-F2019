/*For the Mine switch statement in the cardEffect function (around line 821), it seems that it checks the cost 
of the card they trash against the cost of the card they want to buy incorrectly.  It looks like if the cost of 
the treasure that they choose to trash plus 3, is greater than the cost of the card they want to buy, then it 
will return -1.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void checkMineTreasure(struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

	int choice1 = copper;
	//int currentPlayer = 0;	
    int card = mine;
    int choice2 = gold;
    int choice3 = 0;
    int handPos = 0;
    int *bonus = 0;

    int r = cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	//baronEffect(choice1, post, currentPlayer);

	printf("Testing when card is mine, for trashing treasure\n");

    if(r == -1){
        printf("passed, return value should be -1.\n");
    }
    else{
        printf("failed, return value should be -1.\n");
    }
    //myAssert(pre.discardCount + 5 == post->discardCount, "discard count should increase 5.\n");

	
}

int main()
{
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall
                };

	int playernum = 2;
	int seed = 100;

	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(playernum, k, seed, &G);

    printf ("Testing baronEffect.\n");

	//checkBaronEffect1(&G);
	checkMineTreasure(&G);


    printf ("Test completed.\n");

    exit(0);
}
