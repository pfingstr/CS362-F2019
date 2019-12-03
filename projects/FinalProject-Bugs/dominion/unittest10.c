/*In the dominion.c cardEffect function, ambassador case, line 1100 to 1106, the program goes through the 
currentPlayer's hand, and tries to find copies of choice1 card.  In this loop, if the i-th card is not 
"ambassador", the same kind of card as the choice1-th card and "i != choice1", count up "j".  But this line 
compares the position "i" with the card in choice1-th position.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void fakeAssert(int i, int j, int *ErrCnt, char *message)
{
    if(i == j)
    {
        printf("TEST %d PASSED - %s\n", *ErrCnt, message);
    }
    else
    {
        printf("TEST %d FAILED - %s\n", *ErrCnt, message);
    }
    *ErrCnt = *ErrCnt+1;
}

void ambassador10(struct gameState *post) {
	int i;
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    int ErrCnt;
    ErrCnt = 1;
	int handPos = 4;
	int currentPlayer = 0;
	int choice1 = 1;
	int choice2 = 2;

    post->hand[0][0] = curse;
    post->hand[0][1] = curse;
    post->hand[0][2] = curse;
    post->hand[0][3] = copper;
    post->hand[0][4] = ambassador;
    
    for (i = 0; i < 5; ++i) {
		drawCard(currentPlayer, post);
	}

    //return 1 curse to supply
	int r = cardEffect(ambassador, choice1, choice2, 0, post, handPos, 0);
    //printf("%d\n", r);
    fakeAssert(0, r, &ErrCnt, "Ambassador card is now actually counting curse cards.");
    
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

	ambassador10(&G);
    exit(0);
}