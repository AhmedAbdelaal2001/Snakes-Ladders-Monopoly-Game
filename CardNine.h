#pragma once

#include "Card.h"

// [ CardNine ] Summary:
// Its Apply() Function: Decrements the fees of the card from the player currently standing on the card and gives it to the owner
// Its Parameters: The price of station and fees and owner

class CardNine : public Card
{
	// CardNine Parameters:
	static Player* owner; // owner of all cards from the CardNine class
	static int price; // the price of the station
	static int fees; // fees that will be deducted from the players and given to the owner
	static int NumberOfCards;

public:
	CardNine(const CellPosition& pos); // A Constructor takes card position

	void setOwner(Player* pPlayer);

	Player* getOwner() const ;

	int getPrice() const;

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardNine which is: price and fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardNine on the passed Player
													  // by decrementing the player's wallet by the fees data member and adding it to the owners wallet

	virtual void Save(ofstream& OutFile);

	virtual void Load(ifstream& Infile);

	virtual Card* Copy(Card* pCard);

	virtual ~CardNine(); // A Virtual Destructor
};