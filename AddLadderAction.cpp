#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

    

	///TODO: Make the needed validations on the read parameters

	

	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder * pLadder = new Ladder(startPos, endPos);

	Grid * pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	switch (pLadder->GetValidity())
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
		pGrid->PrintErrorMessage("Error: Start Cell and End Cell Must Be in The Same Column... ");
		return;

	case START_END_REVERSED:
		pGrid->PrintErrorMessage("Error: Start Cell Must Be Below End Cell... ");
		return;

	case COLUMN_AND_REVERSING_ERROR:
		pGrid->PrintErrorMessage("Error, Start Cell and End Cell Must Be in The Same Column, with Start Cell Below End Cell...");
		return;
	}
	
	if (pGrid->isOverlapping(pLadder)) {
		pGrid->PrintErrorMessage("Error: Overlapping Game Objects... ");
		return;
	}

	CellPosition LadderEndPos = pLadder->GetEndPosition();
	bool check = pGrid->HasSnake(LadderEndPos.VCell(), LadderEndPos.HCell());
	if (check) {
		pGrid->PrintErrorMessage("Error: Overlapping Ladder and Snake... ");
		return;
	}
	// Add the ladder object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (! added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
