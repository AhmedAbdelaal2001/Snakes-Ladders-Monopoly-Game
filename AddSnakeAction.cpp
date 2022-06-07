#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters



	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Snake* pSnake = new Snake(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	switch (pSnake->GetValidity())
	{
	case INVALID_START:
		pGrid->PrintErrorMessage("Error: Invalid Start Position... ");
		return;

	case INVALID_END:
		pGrid->PrintErrorMessage("Error: Invalid End Position... ");
		return;

	case INVALID_START_END:
		pGrid->PrintErrorMessage("Error: Invalid Start and End Positions... ");
		return;

	case NOT_SAME_COLUMN:
		pGrid->PrintErrorMessage("Error: Start Cell and End Cell Must Be in The Same Column...  ");
		return;

	case START_END_REVERSED:
		pGrid->PrintErrorMessage("Error: Start Cell Must Be Above End Cell... ");
		return;

	case COLUMN_AND_REVERSING_ERROR:
		pGrid->PrintErrorMessage("Error, Start Cell and End Cell Must Be in The Same Column, with Start Cell Above End Cell...");
		return;
	}

	if (pGrid->isOverlapping(pSnake)) {
		pGrid->PrintErrorMessage("Error: Overlapping Game Objects... ");
		return;
	}

	CellPosition SnakeEndPos = pSnake->GetEndPosition();
	bool check = pGrid->HasLadder(SnakeEndPos.VCell(), SnakeEndPos.HCell());
	if (check) {
		pGrid->PrintErrorMessage("Error: Overlapping Ladder and Snake... ");
		return;
	}

	// Add the ladder object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
