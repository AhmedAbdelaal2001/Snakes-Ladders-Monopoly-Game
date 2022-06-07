#pragma once
#include "Card.h"
class CardThree :
    public Card
{
public:
	CardThree(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // no parameters

	virtual void Apply(Grid * pGrid, Player * pPlayer); // Applies the effect of CardTwo on the passed Player

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& Infile);

	virtual Card* Copy(Card* pCard);

	virtual ~CardThree(); // A Virtual Destructor
};


