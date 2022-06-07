#include "CardSix.h"

CardSix::CardSix(const CellPosition& pos):Card(pos)
{
    cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
     }
void CardSix::ReadCardParameters(Grid* pGrid)
{
    Input* pIn = pGrid->GetInput();
    Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Enter the Cell number to go to..... ");    //Tell the user to input a Cell
	CellNum = pIn->GetInteger(pOut);     //Gets Input to the cell that the card will take the player to
	pOut->ClearStatusBar();     //Clears the message printed out to the user
}
void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
    Card::Apply(pGrid, pPlayer);

   // int num = CellNum - pPlayer->GetCell()->GetCellPosition().GetCellNum();
    pPlayer->Move(pGrid, CellNum - pPlayer->GetCell()->GetCellPosition().GetCellNum());
}// Applies the effect of CardSix on the passed Player
void CardSix::Save(ofstream& OutFile) {
    Card::Save(OutFile);
    OutFile << CellNum;
}

void CardSix::Load(ifstream& Infile) {
    Card::Load(Infile);
    Infile >> CellNum;
}

Card* CardSix::Copy(Card* pCard) {
    CellPosition pos;
    CardSix* copy = new CardSix(pos);
   
    copy->CellNum = CellNum;
    return copy;
}

CardSix::~CardSix()
{

     }// A Virtual Destructor