/*Possible bug with the way duplicate "revealed cards" are handled for the Tribute card.  If 
tributeRevealedCards[0] is the same as tributeRevealedCards[1], the code sets tributeRevealedCards[1] 
to -1.  The loop that follows expects 2 entries in the array, which is fine - there are still two entries: index 0 
contains the card and index 1 contains -1.  What isn't fine is there is no condition to catch the -1.*/