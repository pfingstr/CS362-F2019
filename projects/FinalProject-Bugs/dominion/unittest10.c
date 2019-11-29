/*In the dominion.c cardEffect function, ambassador case, line 1100 to 1106, the program goes through the 
currentPlayer's hand, and tries to find copies of choice1 card.  In this loop, if the i-th card is not 
"ambassador", the same kind of card as the choice1-th card and "i != choice1", count up "j".  But this line 
compares the position "i" with the card in choice1-th position.*/