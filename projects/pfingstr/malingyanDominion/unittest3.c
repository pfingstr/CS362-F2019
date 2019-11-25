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

int main() 
{
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
    
    // 3 Check that the hand count increased
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);
    
    testPlayer.hand[player][0] = copper;
    
    int l;
    //Play mine card with out of bound '26' to detect bug 1
    l = cardEffect(mine, copper, 26, 0, &testPlayer, handpos, &bonus);
	printf("%d\n", l);
    //Cant find bug 1 because this should return -1 dont know why it isnt. 

    //BUG 2 block
    fakeAssert(initializeGame(numPlayers, k, seed, &basePlayer), 0, &ErrCnt);
	//Copy the game state of player to testPlayer
	memcpy(&testPlayer, &basePlayer, sizeof(struct gameState));
    // Check deck count is equal for both
    fakeAssert( (*(int*)testPlayer.deckCount), (*(int*)basePlayer.deckCount), &ErrCnt);
    //Add minion card to players hand at position 6
    testPlayer.hand[player][testPlayer.handCount[player]] = mine;
    testPlayer.handCount[player]++;
    cardEffect(mine, 0, treasure_map, 0, &testPlayer, handpos, &bonus);
    //Detect Bug 2: mine card is never being discarded. 
    fakeAssert(mine, testPlayer.hand[player][0],&ErrCnt); 

    return 0;
}

/*int mineEffect(int choice1, int choice2, int currentPlayer, int handPos, struct gameState *state)
{
    int j;
    int i;
    j = state->hand[currentPlayer][choice1]; //store card we will trash

    if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
    {
        return -1;
    }

    //mineEffect() bug 1
    //
    if (choice2 > gold || choice2 < curse)

    // if (choice2 > treasure_map || choice2 < curse)
    {
        return -1;
    }

    if ((getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2))
    {
        return -1;
    }

    gainCard(choice2, state, 2, currentPlayer);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //discard trashed card
    //
    //mineEffect() bug 2
    for (i = 0; i <= state->handCount[currentPlayer]; i++)
    // for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
        if (state->hand[currentPlayer][i] == j)
        {
            discardCard(i, currentPlayer, state, 0);
            break;
        }
    }

    return 0;
}*/