#include "CardThree.h"
#include "AddCardAction.h"
#include "RollDiceAction.h"
#include "Action.h"
#include "ApplicationManager.h"
CardThree::CardThree(const CellPosition& pos):Card(pos)
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
	 }
void CardThree::ReadCardParameters(Grid* pGrid)
{

}// Reads the parameters of CardTwo which is: walletAmount
void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	for (int i = 0; i < 3; i++)
	{
		pGrid->AdvanceCurrentPlayer();
	}
	
	pPlayer->SetTurnCount(pPlayer->GetTurnCount() - 1);
}// Applies the effect of CardTwo on the passed Player

void CardThree::Save(ofstream& OutFile) {
	Card::Save(OutFile);
}

void CardThree::Load(ifstream& Infile) {
	Card::Load(Infile);
}

Card* CardThree::Copy(Card* pCard) {
	CellPosition pos;
	CardThree* copy = new CardThree(pos);
	
	return copy;
}

CardThree::~CardThree()
{

}// A Virtual Destructor
