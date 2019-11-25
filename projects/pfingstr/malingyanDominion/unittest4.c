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
    testPlayer.hand[player][testPlayer.handCount[player]] = minion;
    testPlayer.handCount[player]++;
    // 3 Check hand count +1
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);
    
    //Play minion card with choice 2.
    cardEffect(minion, 0, 1, 0, &testPlayer, handpos, &bonus);
	//Try to detect bug 2
    /*for (i = 0; i < testPlayer.handCount[player]; i++){
        printf("testp hand: %d\n", testPlayer.hand[player][i]);		
    }*/
    //Test player should only gain 1 estate, with supply of 8-1. Failure == caught bug 2. 
    fakeAssert(supplyCount(estate, &testPlayer), 7, &ErrCnt);
    
   // printf("%d\n", basePlayer.hand[1][0]);
    //int l = whoseTurn(&testPlayer);
    //  printf("%d\n", l);

    //BUG 1 cant catch because the other player is not initilized, something very wrong with dominion.c initilizeGame()


}

/*void minionEffect(int handPos, int choice1, int choice2, struct gameState *state, int currentPlayer)
{
    int i;
    int j;

    //+1 action
    state->numActions++;

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    if (choice1)
    {
        state->coins = state->coins + 2;
    }
    else if (choice2) //discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    {
        //discard hand
        while (numHandCards(state) > 0)
        {
            discardCard(handPos, currentPlayer, state, 0);
        }

        //draw 4
        for (i = 0; i < 4; i++)
        {
            //minoinEffect() bug 2
            gainCard(estate, state, 2, currentPlayer);
            //drawCard(currentPlayer, state);
        }

        //other players discard hand and redraw if hand size > 4
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                //minionEffect() bug 1
                if (state->handCount[i] > 5)
                // if ( state->handCount[i] > 4 )
                {
                    //discard hand
                    while (state->handCount[i] > 0)
                    {
                        discardCard(handPos, i, state, 0);
                    }

                    //draw 4
                    for (j = 0; j < 4; j++)
                    {
                        drawCard(i, state);
                    }
                }
            }
        }
    }
}*/