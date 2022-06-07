#include "InputDiceValueAction.h"
#include "Grid.h"
#include "Player.h"

InputDiceValueAction::InputDiceValueAction(ApplicationManager* pApp) : Action(pApp)
{
	diceNumber = 0;
}

void InputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Input Dice Value: ");
	diceNumber = pIn->GetInteger(pGrid->GetOutput());

}

void InputDiceValueAction::Execute()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (pGrid->GetEndGame())
	{
		pGrid->PrintErrorMessage("Game Ended! hahaha");
		return;
	}
	int Prisons = pGrid->GetCurrentPlayer()->GetPrison();
	if (Prisons > 0)
	{
		Output* pOut = pGrid->GetOutput();
		pOut->PrintMessage("You are still in Prison!!");
	}
	else
	{
		ReadActionParameters();    // 2 - Read the needed parameters from the user
	}
	// -- If not ended, do the following --:


	// 3- Get the "current" player from pGrid
	Player* pPlayer = pGrid->GetCurrentPlayer();

	// 4- Move the currentPlayer using function Move of class player
	int currentPos = pPlayer->GetCell()->GetCellPosition().GetCellNum();
	if (currentPos + diceNumber >= 99)
	{
		pGrid->SetEndGame(true);
		pPlayer->Move(pGrid, 99 - currentPos);
		pGrid->PrintErrorMessage("Game has ended! Player " + to_string(pGrid->getCurrPlayerNumber()) + " has won!! Click for Options..");
		pOut->PrintMessage("You can restart or go to design mode...");
		return;
	}
	pPlayer->Move(pGrid, diceNumber);

	// 5- Advance the current player number of pGrid
	pGrid->AdvanceCurrentPlayer();


	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

InputDiceValueAction::~InputDiceValueAction()
{
}