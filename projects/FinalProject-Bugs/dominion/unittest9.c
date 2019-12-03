/*Possible bug with the way duplicate "revealed cards" are handled for the Tribute card.  If 
tributeRevealedCards[0] is the same as tributeRevealedCards[1], the code sets tributeRevealedCards[1] 
to -1.  The loop that follows expects 2 entries in the array, which is fine - there are still two entries: index 0 
contains the card and index 1 contains -1.  What isn't fine is there is no condition to catch the -1.*/

//gcc -o unittest9 dominion.c rngs.c unittest9.c .... ./Desktop/cs362


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

void tribute9(struct gameState *post)
{
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    int ErrCnt;
    ErrCnt = 1;
	int i;
	int currentPlayer = 0;
	int nextPlayer = 1;

	for (i = 0; i < 6; ++i) {
		drawCard(currentPlayer, post);
	}
	post->discardCount[nextPlayer] = 5;
	post->deckCount[nextPlayer] = 5;
    //Fill oponents deck:
	post->deck[nextPlayer][0] = copper;
	post->deck[nextPlayer][1] = copper;
    // Fill with estate to control loop bug 7.
	post->deck[nextPlayer][2] = estate;
    // tributerevealedcard [1]:
	post->deck[nextPlayer][3] = copper;
    // tributerevealedcard [0]:
	post->deck[nextPlayer][4] = copper;
    
	cardEffect(tribute, 0,0,0, post, 0, 0);
    //printf("pre actions - %d\n", pre.numActions);
    //printf("post actions - %d\n", post->numActions);
    //printf("pre actions - %d\n", pre.coins);
    //printf("post actions - %d\n", post->coins);
	fakeAssert(pre.numActions, post->numActions, &ErrCnt, "numActions should NOT increase by 2.");
	fakeAssert(post->coins, pre.coins + 2, &ErrCnt, "coins should increase by 2.");
}

int main()
{
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, tribute, village, baron, great_hall
                };

	int playernum = 2;
	int seed = 100;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));
	initializeGame(playernum, k, seed, &G);
    
    printf("Testing for Bug 9.\n");
	tribute9(&G);
    exit(0);
}