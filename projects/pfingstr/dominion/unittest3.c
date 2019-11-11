
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define CARD_TEST "Mine"

//gcc -o unittest3 dominion.c rngs.c unittest3.c

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

    //Add minion card to players hand at position 6
    testPlayer.hand[player][testPlayer.handCount[player]] = mine;
    testPlayer.handCount[player]++;
    
    // 3 Check that the mine card count is +1 for testplayer
    for (i = 0; i < basePlayer.handCount[player]; i++){
        if(basePlayer.hand[player+1][i] = mine);
			count++;
    }	
	for (i = 0; i < testPlayer.handCount[player]; i++){
        if(testPlayer.hand[player][i] = mine);
			count2++;
    }
    fakeAssert(count+1, count2, &ErrCnt);

    // 4 Check that the hand count increased
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);
    
    testPlayer.hand[player][0] = copper;
    testPlayer.hand[player][1] = gold;
    
    //Play mine card.
    cardEffect(mine, copper, gold, 0, &testPlayer, handpos, &bonus);
	
    /////////////////////////////////////////////

	// 5 Check for introduced bug 1 test player should not gain any cards
    fakeAssert((*(int*)testPlayer.handCount), (*(int*)basePlayer.handCount), &ErrCnt);
    
    //6 Check for bug 2 testplayer should not discard any cards.
    fakeAssert((*(int*)testPlayer.discardCount), (*(int*)basePlayer.discardCount), &ErrCnt);

    // 7 Check that test player has +2 coins vs base player
    fakeAssert(testPlayer.coins, basePlayer.coins+2, &ErrCnt);
    
}

/*int refactoredMine(struct gameState *state, int choice1, int choice2, int currentPlayer, int handPos)
{
    int i;
    int j = state->hand[currentPlayer][choice1];  //store card we will trash

        if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
        {
            return -1;
        }

        if (choice2 > treasure_map || choice2 < curse)
        {
            return -1;
        }

        if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
        {
            return -1;
        }

        //gainCard(choice2, state, 2, currentPlayer); BUG INTRODUCED

        //discard card from hand
        //discardCard(handPos, currentPlayer, state, 0);  BUG INTRODUCED

        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(i, currentPlayer, state, 0);
                break;
            }
        }

        return 0;
}*/