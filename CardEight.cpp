#include "CardEight.h"

CardEight::CardEight(const CellPosition& pos) :Card(pos) //Sets the Cell Position of Card.
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (8 here)
}
void CardEight::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Enter Amount of Money to get out of Prison.....");
	PrisonMoney = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();

}// Reads the parameters of CardEight which is: PrisonMoney
void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Choose ""1"" to pay money and get out of prison or ""2"" to stay.....");
	int choice = pIn->GetInteger(pOut);
	if (choice == 1)
	{
		if ((pPlayer->GetWallet() >= PrisonMoney))
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - PrisonMoney);
		}
		else
		{

			pOut->PrintMessage("No enough money to be paid");
		}
	}
	else
	{
		pPlayer->SetPrison(3);
	}

}// Applies the effect of CardEight on the passed Player

void CardEight::Save(ofstream& OutFile) {
	Card::Save(OutFile);
	OutFile << PrisonMoney;
}

void CardEight::Load(ifstream& Infile) {
	Card::Load(Infile);
	Infile >> PrisonMoney;
}

Card* CardEight::Copy(Card* pCard) {
	CellPosition pos;
	CardEight* copy = new CardEight(pos);
	
	copy->PrisonMoney = PrisonMoney;
	return copy;
}

	CardEight::~CardEight()
	{

	}