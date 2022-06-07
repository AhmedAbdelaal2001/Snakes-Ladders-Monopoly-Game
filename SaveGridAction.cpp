#include "SaveGridAction.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include <fstream>

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

SaveGridAction::~SaveGridAction()
{
}


void SaveGridAction::ReadActionParameters()
{
}


// Execute the action
void SaveGridAction::Execute()
{
	// Opens/Creates the file that we will save to
	ofstream OutFile("Grid.txt");
	
	// Getting grid info
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Grid Saved...");
	pGrid->SavetoFile(OutFile);
	
}