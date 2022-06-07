#pragma once

#include "Card.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"

// [ CardTwelve ] Summary:
// Its Apply() Function: Moves the ownership of the most expensive station that the current player owns and gives it to the poorest player
// Its Parameters: Dummy cards

class CardTwelve : public Card
{
	// CardTwelve Parameters:
	
	CardNine* card9;
	CardTen* card10;
	CardEleven* card11;

public:
	CardTwelve(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardTwelve which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwelve on the passed Player                    
													  // by decrementing the player's wallet by the walletAmount data member

	void Save(ofstream& OutFile);

	void Load(ifstream& Infile);

	virtual Card* Copy(Card* pCard);

	virtual ~CardTwelve(); // A Virtual Destructor
};

