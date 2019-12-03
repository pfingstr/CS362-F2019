/*The number of bonus coins from actions does not appear to be recorded correctly in cardEffect.*/
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

void coin8(struct gameState *post)
{
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    int ErrCnt;
    ErrCnt = 1;
	int i;
	int currentPlayer = 0;
	//int nextPlayer = 1;
    int pc;

	for (i = 0; i < 6; ++i) {
		drawCard(currentPlayer, post);
	}
    
    post->hand[0][0] = baron;
    post->hand[0][1] = curse;
    post->hand[0][2] = estate;
    post->hand[0][3] = copper;

    printf("%d\n", pre.coins);
    pc = playCard(0, 1, 0, 0, post);
    //cardEffect(baron, 1, 0, 0, post, 0, 0);
    printf("%d\n", post->coins);
    printf("%d\n", pc);

	fakeAssert(pc, 0, &ErrCnt, "PlayCard() returning 0.");
	fakeAssert(post->coins, pre.coins + 4, &ErrCnt, "Coins supposed to increase by 4.");
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
	coin8(&G);
    exit(0);
}