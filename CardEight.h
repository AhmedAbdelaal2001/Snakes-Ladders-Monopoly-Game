#pragma once

#include "Card.h"



class CardEight : public Card
{
	// CardEight Parameters:
	int PrisonMoney;
	

public:
	CardEight(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardEight

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardEight on the passed Player
		
	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& Infile);

	virtual Card* Copy(Card* pCard);

	virtual ~CardEight(); // A Virtual Destructor
};

