#include "CardFour.h"
#include "ApplicationManager.h"

CardFour::CardFour(const CellPosition& pos) :Card(pos)
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (4 here)
}// A Constructor takes card position

void CardFour::ReadCardParameters(Grid* pGrid)  //No parameters to be read
{

}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pPlayer->SetStop(1);
}
// Applies the effect of CardFour on the passed Player

void CardFour::Save(ofstream& OutFile) {
	Card::Save(OutFile);
}

void CardFour::Load(ifstream& Infile) {
	Card::Load(Infile);
}

Card* CardFour::Copy(Card* pCard) {
	CellPosition pos;
	CardFour* copy = new CardFour(pos);
	
	return copy;
}

CardFour::~CardFour()// A Virtual Destructor
{

}