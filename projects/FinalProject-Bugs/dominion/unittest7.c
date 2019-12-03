/*Tribute card bug around line 1075.  The for loop overruns the array. The tributeRevealedCards array has 
two elements and the loop is written to iterate 3 times.*/


//gcc -o unittest7 dominion.c rngs.c unittest7.c .... /Desktop/cs362/CS362-F2019/projects/pfingstr

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


void tribute7(struct gameState *post)
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

	post->deck[nextPlayer][0] = baron;
	post->deck[nextPlayer][1] = mine;
    // Bug 7 loop also uses this card
	post->deck[nextPlayer][2] = copper;
    // tributerevealedcard [1]:
	post->deck[nextPlayer][3] = mine;
    // tributerevealedcard [0]:
	post->deck[nextPlayer][4] = estate;

	cardEffect(tribute, 0,0,0, post, 0, 0);
	fakeAssert(pre.numActions + 2, post->numActions, &ErrCnt, "numActions should increase by 2. (mine)");
	fakeAssert(post->coins, pre.coins + 2, &ErrCnt, "coins not supposed to increase but do (copper).");
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
    
    printf ("Testing tributeEffect.\n");
	tribute7(&G);
    exit(0);
}