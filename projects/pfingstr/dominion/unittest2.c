#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARD_TEST "Baron"

//gcc -o unittest2 dominion.c rngs.c unittest2.c

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

/* +1 Buy
You may discard an Estate for +$4. If you don't, gain an Estate. 
int supplyCount(int card, struct gameState *state); -How many of given card are left in supply-
*/

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

    //Add baron card to players hand at position 6
    testPlayer.hand[player][testPlayer.handCount[player]] = baron;
    testPlayer.handCount[player]++;

    // 3 Check that the baron card count is +1 for testplayer
    for (i = 0; i < basePlayer.handCount[player]; i++){
        if(basePlayer.hand[player][i] = baron);
			count++;
    }	
	for (i = 0; i < testPlayer.handCount[player]; i++){
        if(testPlayer.hand[player][i] = baron);
			count2++;
    }
    fakeAssert(count+1, count2, &ErrCnt);
    
    // 4 Check that hand count +1
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);

    //Add estate card to players hand at position 7
    testPlayer.hand[player][testPlayer.handCount[player]] = estate;
    testPlayer.handCount[player]++;
    
    // 5 Check that card was added to hand count
    fakeAssert(basePlayer.handCount[player] + 2, testPlayer.handCount[player], &ErrCnt);
    
    //Play baron card with estate discard option
    cardEffect(baron, 1, 0, 0, &testPlayer, handpos, &bonus);
	
	///////////////////////////////////////////
	
	// 6 Check the players hand count decreased after playing card
    fakeAssert(basePlayer.handCount[player], testPlayer.handCount[player]-2, &ErrCnt);
    

    // 7 Check gold count is +4 : its oddly +6
    fakeAssert(testPlayer.coins-4, basePlayer.coins, &ErrCnt);
    
    // 8 Check discard pile
    fakeAssert(testPlayer.playedCardCount-2, basePlayer.playedCardCount, &ErrCnt);
}

/*
int refactoredBaron(struct gameState *state, int choice1, int currentPlayer)
{
    state->numBuys--;//Increase buys by 1!
        if (choice1 > 0) { //Boolean true or going to discard an estate
            int p = 0;//Iterator for hand!
            int card_not_discarded = 1;//Flag for discard set!
            while(card_not_discarded) {
                if (state->hand[currentPlayer][p] == estate) { //Found an estate card!
                    state->coins += 4;//Add 4 coins to the amount of coins
                    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
                    state->discardCount[currentPlayer]++;
                    for (; p < state->handCount[currentPlayer]; p++) {
                        state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
                    }
                    state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
                    state->handCount[currentPlayer]--;
                    card_not_discarded = 0;//Exit the loop
                }
                else if (p > state->handCount[currentPlayer]) {
                    if(DEBUG) {
                        printf("No estate cards in your hand, invalid choice\n");
                        printf("Must gain an estate if there are any\n");
                    }
                    if (supplyCount(estate, state) > 0) {
                        gainCard(estate, state, 0, currentPlayer);

                        state->supplyCount[estate]++;
                        if (supplyCount(estate, state) == 0) {
                            isGameOver(state);
                        }
                    }
                    card_not_discarded = 0;//Exit the loop
                }

                else {
                    p++;//Next card
                }
            }
        }

        else {
            if (supplyCount(estate, state) > 0) {
                gainCard(estate, state, 0, currentPlayer);//Gain an estate

                state->supplyCount[estate]--;//Decrement Estates
                if (supplyCount(estate, state) == 0) {
                    isGameOver(state);
                }
            }
        }


        return 0;
}*/