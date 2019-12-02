/*Tribute card bug around line 1075.  The for loop overruns the array. The tributeRevealedCards array has 
two elements and the loop is written to iterate 3 times.*/


//gcc -o unittest7 dominion.c rngs.c unittest7.c .... /Desktop/cs362/CS362-F2019/projects/pfingstr


/* * If the player after you has fewer than 2 cards left in his deck, he reveals all 
         the cards in his deck, shuffles his discard pile (which does not include currently 
         revealed cards), and then reveals the remainder needed. The player then discards the revealed cards.
       * If the player after you does not have enough cards to reveal 2, he reveals what he can.
       * You get bonuses for the types of cards revealed, counting only the different cards.
       * A card with 2 types gives you both bonuses.
         So if the player to your left reveals Copper and Harem, you get +$4 and +2 cards; 
         if he reveals 2 Silvers, you just get +$2.  
         Changed: for (i = 0; i <= 2; i ++) {
        changed to: for (i = 0; i <= 1; i ++) {
        Impact: There will only be max +2 gold for the player.
        2. Removed: shuffle(nextPlayer,state);
    I   mpact: If there are no available cards for next player their deck will not be shuffled.*/

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