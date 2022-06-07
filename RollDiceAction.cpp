#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager* pApp) : Action(pApp)
{

}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
	int diceNumber = 0;
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (pGrid->GetEndGame())
	{
		
		return;
	}
	int Prisons = pGrid->GetCurrentPlayer()->GetPrison();
	if (Prisons > 0)
	{
		pGrid->GetOutput()->PrintMessage("You are still in Prison!!");
	}
	int Stops = pGrid->GetCurrentPlayer()->GetStop();
	if (Stops > 0)
	{
		pGrid->GetOutput()->PrintMessage("You can't play this turn!!");
	}
	else
	{
		srand((int)time(NULL)); // time is for different seed each run
		diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed
		string msg = "Dice Number: " + to_string(diceNumber);
		pOut->PrintMessage(msg);

	}

	// -- If not ended, do the following --:

	// 2- Generate a random number from 1 to 6 --> This step is done for you


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

RollDiceAction::~RollDiceAction()
{
}
