#include "ToDesignModeAction.h"
#include "Grid.h"

ToDesignModeAction::ToDesignModeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

ToDesignModeAction::~ToDesignModeAction()
{
}

void ToDesignModeAction::ReadActionParameters()
{
}


// Execute the action
void ToDesignModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	pGrid->GetOutput()->CreateDesignModeToolBar();
	pGrid->Restart();
	pGrid->PrintErrorMessage("Welcome back to Design Mode! Click Anywhere to Continue... ");
}
