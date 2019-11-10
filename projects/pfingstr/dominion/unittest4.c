#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#define CARD_TEST "Minion"

//gcc -o unittest4 dominion.c rngs.c unittest4.c

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
    int i, j, m;
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

    //Add minion card to players hand at position 6
    testPlayer.hand[player][testPlayer.handCount[player]] = minion;
    testPlayer.handCount[player]++;

    // 3 Check that the minion card count is +1 for testplayer
    for (i = 0; i < basePlayer.handCount[player]; i++){
        if(basePlayer.hand[player][i] = minion);
			count++;
    }
		
	for (i = 0; i < testPlayer.handCount[player]; i++){
        if(testPlayer.hand[player][i] = minion);
			count2++;
    }
    fakeAssert(count+1, count2, &ErrCnt);
    
    // 4 Check hand count +1
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);
    
    //Play minion card with +2 Gold option.
    cardEffect(minion, 1, 0, 0, &testPlayer, handpos, &bonus);
	
	
    /*Choose one: +$2; or discard your hand, +4 Cards, 
    and each other player with at least 5 cards in 
    hand discards their hand and draws 4 cards. 
    
    
    */
	
	// 5 Check the players hand count decreased after playing card
    fakeAssert(basePlayer.handCount[player], testPlayer.handCount[player]-1, &ErrCnt);
    
    // 6 Check gold count option
    fakeAssert(testPlayer.coins-2, basePlayer.coins, &ErrCnt);

    // 7 Check num action +1 for test player
    fakeAssert(testPlayer.numActions+1, basePlayer.numActions, &ErrCnt);
    
    //Reinitilize game
    initializeGame(numPlayers, k, seed, &basePlayer);
    memcpy(&testPlayer, &basePlayer, sizeof(struct gameState));
    
    // 8 Add minion card to players hand and check hand count
    testPlayer.hand[player][testPlayer.handCount[player]] = minion;
    testPlayer.handCount[player]++;
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);

    //Play minion card with second option
	cardEffect(minion, 0, 1, 0, &testPlayer, handpos, &bonus);
    
    // 9 Hand count should equal 5 based on bug introduced
    fakeAssert(5, testPlayer.handCount[player], &ErrCnt);
    // 10 Hand count should equal 5 based on bug introduced
    fakeAssert(5, basePlayer.handCount[player], &ErrCnt);
    
    // 11 Check dicsard count
    fakeAssert(testPlayer.discardCount[player], basePlayer.discardCount[player], &ErrCnt);


}


