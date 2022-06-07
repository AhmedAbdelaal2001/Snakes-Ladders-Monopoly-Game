#include "ToPlayModeAction.h"
#include "Grid.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

ToPlayModeAction::~ToPlayModeAction()
{
}

void ToPlayModeAction::ReadActionParameters()
{
}


// Execute the action
void ToPlayModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	pGrid->GetOutput()->CreatePlayModeToolBar();
	pGrid->PrintErrorMessage("Welcome to Play Mode! Click Anywhere to Continue... ");
}
