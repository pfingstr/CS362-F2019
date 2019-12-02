/*The last discardCard function call within the mine statement of the cardEffect function are 
not actually trashing the cards.  They are just being put into the currentPlayers discard pile when the 
chosen card should be trashed. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void checkMineDiscard(struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

	int choice1 = 1;
	//int currentPlayer = 0;	
    int card = baron;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int *bonus = 0;

    cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	//baronEffect(choice1, post, currentPlayer);

	//printf("Testing when card is mine\n");

    if(pre.discardCount + 5 == post->discardCount){
        printf("passed, discard count should increase by 5.\n");
    }
    else{
        printf("failed, discard count should increase by 5.\n");
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

    printf ("Testing discard() in mine.\n");

	checkMineDiscard(&G);
	//checkBaronEffect2(&G);


    printf ("Test completed.\n");

    exit(0);
}
