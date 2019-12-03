/*In the remodel case within the cardEffect function, the if statement that compares the two choice 
statements needs to be switched (around Line #846).*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void checkRemodel(struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

	int choice1 = silver;
	//int currentPlayer = 0;	
    int card = remodel;
    int choice2 = copper;
    int choice3 = 0;
    int handPos = 0;
    int *bonus = 0;

    int r = cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	//baronEffect(choice1, post, currentPlayer);

	printf("Testing when card is remodel, for compare treasure\n");

    printf("r = %d.\n", r);
    if(r == -1){
        printf("failed, return value should be 0.\n");
    }
    else{
        printf("passed, return value should be 0.\n");
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

    //printf ("Testing .\n");

	//checkBaronEffect1(&G);
	checkRemodel(&G);


    printf ("Test completed.\n");

    exit(0);
}
