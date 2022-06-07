#include "NewGameAction.h"
#include "Grid.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

NewGameAction::~NewGameAction()
{
}

void NewGameAction::ReadActionParameters()
{
}


// Execute the action
void NewGameAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("Game has been restarted... Goodluck!");
	pGrid->Restart();
}