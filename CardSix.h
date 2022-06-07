#pragma once
#include "Card.h"
class CardSix: public Card
{
	int CellNum;          //The Cell the Player will go to after the card.
public:
	CardSix(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid);

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardSix on the passed Player

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& Infile);

	virtual Card* Copy(Card* pCard);

	virtual ~CardSix(); // A Virtual Destructor
};

