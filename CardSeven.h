#pragma once
#include "Card.h"
class CardSeven :
    public Card

{
		// CardSeven Parameters:
public:
	CardSeven(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardSeven

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CarSeven on the passed Player
		
	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& Infile);

	virtual Card* Copy(Card* pCard);

	virtual ~CardSeven(); // A Virtual Destructor
	
};

