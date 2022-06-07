#include "CardFive.h"

#include "Player.h"


CardFive::CardFive(const CellPosition& pos):Card(pos)
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (5 here)
}

void CardFive::ReadCardParameters(Grid* pGrid)
{
	
}
	
void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	
	pPlayer->Move(pGrid,(-1* pPlayer->GetJustRolledDiceNum())); //Moving in the negative direction with the just rolled dice number
}// Applies the effect of CardFive on the passed Player
	
void CardFive::Save(ofstream& OutFile) {
	Card::Save(OutFile);
}

void CardFive::Load(ifstream& Infile) {
	Card::Load(Infile);
}

Card* CardFive::Copy(Card* pCard) {
	CellPosition pos;
	CardFive* copy = new CardFive(pos);
	
	return copy;
}

CardFive::~CardFive()
{

	 }// A Virtual Destructor