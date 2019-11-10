#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#define CARD_TEST "Tribute"

//gcc -o unittest5 dominion.c rngs.c unittest5.c .... /Desktop/cs362/CS362-F2019/projects/pfingstr/dominion

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
	int ErrCnt=1;
     int count, count2;
    count = count2 = 0;


    printf("TESTING - %s\n", CARD_TEST);

	// 1 Initialize a game state and player cards
	fakeAssert(initializeGame(numPlayers, k, seed, &basePlayer), 0, &ErrCnt);

	//Copy the game state of player to testPlayer
	memcpy(&testPlayer, &basePlayer, sizeof(struct gameState));

    // 2 Check deck count is equal for both
    fakeAssert( (*(int*)testPlayer.deckCount), (*(int*)basePlayer.deckCount), &ErrCnt);

    // 3 Confirm 5 cards in each players deck
    fakeAssert( (*(int*)testPlayer.deckCount), 5, &ErrCnt);

    //Add tribute card to players hand
    testPlayer.hand[player][testPlayer.handCount[player]] = tribute;
    testPlayer.handCount[player]++;

    // 4 Check that the tribute card count is +1 for testplayer
    for (i = 0; i < basePlayer.handCount[player]; i++){
        if(basePlayer.hand[player][i] = tribute);
			count++;
    } 
	
	for (i = 0; i < testPlayer.handCount[player]; i++){
        if(testPlayer.hand[player][i] = tribute);
			count2++;
    }
    fakeAssert(count, count2-1, &ErrCnt);
    
    // 5 See if hand count +1
    fakeAssert(basePlayer.handCount[player] + 1, testPlayer.handCount[player], &ErrCnt);
    
    //printf("%d\n", handCard(0, &testPlayer));
    
    //Play tribute card with no options
    cardEffect(tribute, 0, 0, 0, &testPlayer, handpos, &bonus);
	
    // 6 Check that TestPlayer hand count decresed by 1.
	fakeAssert(testPlayer.handCount[player]-1, basePlayer.deckCount[player], &ErrCnt);
	
    // 7 Check that card has been added to played card count. 
	fakeAssert(testPlayer.playedCardCount, basePlayer.playedCardCount+1, &ErrCnt);

    //Necessary to detect inserted bug, put gold and copper at top of baseplayers deck. 
    basePlayer.deck[player][(*(int*)basePlayer.deckCount) -1 ] = gold;
    basePlayer.deck[player][(*(int*)basePlayer.deckCount)] = copper;

    // 8 check that player only gained max +2 gold 
    fakeAssert(testPlayer.coins+2, basePlayer.coins, &ErrCnt);




}

/*
int refactoredTribute(struct gameState *state, int currentPlayer)
{
        int tributeRevealedCards[2] = {-1, -1};
        int nextPlayer = currentPlayer + 1;
        int i;
        if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
            if (state->deckCount[nextPlayer] > 0) {
                tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
                state->deckCount[nextPlayer]--;
            }
            else if (state->discardCount[nextPlayer] > 0) {
                tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
                state->discardCount[nextPlayer]--;
            }
            else {
                //No Card to Reveal
                if (DEBUG) {
                    printf("No cards to reveal\n");
                }
            }
        }

        else {
            if (state->deckCount[nextPlayer] == 0) {
                for (i = 0; i < state->discardCount[nextPlayer]; i++) {
                    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                    state->deckCount[nextPlayer]++;
                    state->discard[nextPlayer][i] = -1;
                    state->discardCount[nextPlayer]--;
                }     
            }
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
            state->deckCount[nextPlayer]--;
            tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
            state->deckCount[nextPlayer]--;
        }

        if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
            state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
            state->playedCardCount++;
            tributeRevealedCards[1] = -1;
        }

        for (i = 0; i <= 1; i ++) {
            if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
                state->coins += 2;
            }

            else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
                drawCard(currentPlayer, state);
                drawCard(currentPlayer, state);
            }
            else { //Action Card
                state->numActions = state->numActions + 2;
            }
        }

        return 0;
}*/