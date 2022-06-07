#pragma once
#include "Card.h"
class CardFive :
    public Card
{
    //Moves the player backward with the same number of steps that he just rolled.
    //If he reaches a ladder, a snake, or a card at the end of moving, take it.
public:
	CardFive(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardFive which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFive on the passed Player
		
	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& Infile);

	virtual Card* Copy(Card* pCard);

	virtual ~CardFive(); // A Virtual Destructor
};


