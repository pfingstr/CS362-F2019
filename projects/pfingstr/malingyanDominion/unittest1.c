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
    // chand hand count is 5 for base player and 6 for test player.
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);
    
    ////////////////////PLAY CARD//////////////////////////////
    //Play ambassador card with a 3 for choice 1 and 3 for choice 2 
    cardEffect(ambassador, 3, 3, 0, &testPlayer, handpos, &bonus);
	
	// 4 Check the players hand count post play -4 from 6 for testplayer and -0 from 5 for baseplayer.
    fakeAssert(basePlayer.handCount[player], testPlayer.handCount[player] + 3, &ErrCnt);
    
    //Find Bug 2: commented out check for number of cards avaliable in hand
    // 5 Check to see that error -1 placed at hand index 4. 
    fakeAssert(testPlayer.hand[player][4], -1, &ErrCnt);
     // 6 Check to see that error -1 placed at hand index 5 
    fakeAssert(testPlayer.hand[player][5], -1, &ErrCnt);

    // Re Initialize a game state and player cards
    fakeAssert(initializeGame(numPlayers, k, seed, &basePlayer), 0, &ErrCnt);
	//Copy the game state of player to testPlayer
	memcpy(&testPlayer, &basePlayer, sizeof(struct gameState));
    //Add ambassador card to players hand
    testPlayer.hand[player][testPlayer.handCount[player]] = ambassador;
    testPlayer.handCount[player]++;
    
    /*for (i = 0; i < testPlayer.handCount[player]; i++){
        printf("T%d\n", testPlayer.hand[player][i]);
    }
    for (i = 0; i < basePlayer.handCount[player]; i++){
        printf("B%d\n", basePlayer.hand[player][i]);
    }*/
    ////////////////////PLAY CARD//////////////////////////////
    //Play ambassador card with a 3 for choice 1 and 0 for choice 2 
    cardEffect(ambassador, 3, 2, 0, &testPlayer, handpos, &bonus);
    
    /*for (i = 0; i < testPlayer.handCount[player]; i++){
        printf("t%d\n", testPlayer.hand[player][i]);
    }
    for (i = 0; i < basePlayer.handCount[player]; i++){
        printf("b%d\n", basePlayer.hand[player][i]);
    }*/

}

/*int ambassadorEffect(int choice1, int choice2, int handPos, struct gameState *state, int currentPlayer)
{
    int j = 0;
    int i;

    //used to check if player has enough cards to discard
    //
    //ambassadorEffect() bug 1
    if (choice2 > 2 && choice2 < 0)
    // if (choice2 > 2 || choice2 < 0)
    {
        return -1;
    }

    if (choice1 == handPos)
    {
        return -1;
    }

    for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
        if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
        {
            j++;
        }
    }

    //ambassadorEffect() bug 2
    //
    // if (j < choice2)
    // {
    //   return -1;
    //}

    if (DEBUG)
        printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

    //increase supply count for choosen card by amount being discarded
    state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

    //each other player gains a copy of revealed card
    for (i = 0; i < state->numPlayers; i++)
    {
        if (i != currentPlayer)
        {
            gainCard(state->hand[currentPlayer][choice1], state, 0, i);
        }
    }

    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //trash copies of cards returned to supply
    for (j = 0; j < choice2; j++)
    {
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
            {
                discardCard(i, currentPlayer, state, 1);
                break;
            }
        }
    }
    return 0;
}*/