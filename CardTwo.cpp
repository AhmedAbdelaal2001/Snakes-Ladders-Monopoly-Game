#include "CardTwo.h"
#include "Cell.h"
#include "Ladder.h"
#include "Grid.h"





CardTwo::CardTwo(const CellPosition& pos):Card(pos)
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (2 here)
}

void CardTwo::ReadCardParameters(Grid* pGrid)
{
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)// Applies the effect of CardTwo on the passed Player
{
	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	Ladder*lad=pGrid->GetNextLadder(position); //Checks the prescence of a ladder in the remaining cells.
	if (lad == NULL)         //if there was no ladder found.
	{
		int x, y;
		
		pOut->PrintMessage("No ladder, Click to continue.... ");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		
	}
	else                  //if a ladder was found start moving the player to it.
	{
		int run;
		run = lad->GetPosition().GetCellNum() - pPlayer->GetCell()->GetCellPosition().GetCellNum();
		pPlayer->Move(pGrid, run);

	}
	pPlayer->SetTurnCount(pPlayer->GetTurnCount() - 1);
}

Card* CardTwo::Copy(Card* pCard) {
	CellPosition pos;
	CardTwo* copy = new CardTwo(pos);
	
	return copy;
}

void CardTwo::Save(ofstream& OutFile) {
	Card::Save(OutFile);
}

void CardTwo::Load(ifstream& Infile) {
	Card::Load(Infile);
}

CardTwo::~CardTwo()
{

}// A Virtual Destructor
