#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // A Constructor takes card position
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}

void CardSeven::ReadCardParameters(Grid* pGrid) // Reads the parameters of CardSeven
{

}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)// Applies the effect of CarSeven on the passed Player
{
	Card::Apply(pGrid, pPlayer);
	Player* nextPlayer = pGrid->getNextPlayer(pPlayer);
	CellPosition startPos(8, 0);

	pGrid->UpdatePlayerCell(nextPlayer, startPos);
}

void CardSeven::Save(ofstream& OutFile) {
	Card::Save(OutFile);
}

void CardSeven::Load(ifstream& Infile) {
	Card::Load(Infile);
}

Card* CardSeven::Copy(Card* pCard) {
	CellPosition pos;
	CardSeven* copy = new CardSeven(pos);
	
	return copy;
}

CardSeven:: ~CardSeven()// A Virtual Destructor
{
}