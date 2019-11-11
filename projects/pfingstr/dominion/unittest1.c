
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_TEST "Ambassador"


/*  First you reveal a card from your hand.
    Then take 0, 1, or 2 copies of that card from your hand and put them on top of their Supply pile.
    Then each other player gains a copy of that card from the Supply.
    If there are not enough copies to go around, deal them out in turn order, starting with the player to your left. */

//gcc -o unittest1 dominion.c rngs.c unittest1.c

void fakeAssert(int i, int j, int *ErrCnt)
{
    if(i == j)
    {
        printf("TEST %d PASSED\n", *ErrCnt);
    }
    else
    {
        printf("TEST %d FAILED\n", *ErrCnt);
    }
    *ErrCnt = *ErrCnt+1;
    
}

void main() 
{
    int i;

    int handpos = 0, bonus = 0;
    int seed = 1000;
    //number of players
    int numPlayers = 2;
    int player=0;
    //each holds a pointer to game state variable
	struct gameState basePlayer, testPlayer;
    //Kingdom cards avaliable for purchase
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int ErrCnt = 1;
    int count, count2;
    count = count2 = 0;


    printf("TESTING - %s\n", CARD_TEST);
	
    // 1 Initialize a game state and player cards
    fakeAssert(initializeGame(numPlayers, k, seed, &basePlayer), 0, &ErrCnt);

	//Copy the game state of player to testPlayer
	memcpy(&testPlayer, &basePlayer, sizeof(struct gameState));

    // 2 Check deck count is equal for both
    fakeAssert( (*(int*)testPlayer.deckCount), (*(int*)basePlayer.deckCount), &ErrCnt);

    //Add ambassador card to players hand
    testPlayer.hand[player][testPlayer.handCount[player]] = ambassador;
    testPlayer.handCount[player]++;

    // 3 Check that the ambassador card count is +1 for testplayer
    for (i = 0; i < basePlayer.handCount[player]; i++){
        if(basePlayer.hand[player+1][i] = ambassador);
			count++;
    }	
	for (i = 0; i < testPlayer.handCount[player]; i++){
        if(testPlayer.hand[player][i] = ambassador);
			count2++;
    }
    fakeAssert(count+1, count2, &ErrCnt);
    // 4
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);
    
    //Play ambassador card with a 3 for choice 1 and 0 for choice 2 to identify bug 1
    cardEffect(ambassador, 3, 0, 0, &testPlayer, handpos, &bonus);
	
    ////////////////////////////////////////////////////////
	
	// 5 Check the players supplycount to identify bug 2 
    fakeAssert((*(int*)basePlayer.supplyCount)+1, (*(int*)testPlayer.supplyCount), &ErrCnt);
    
 
}

