#include "DeleteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"
#include "Cell.h"
#include "CellPosition.h"
DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp):Action(pApp)
{

     }
void DeleteGameObjectAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();       // Get a Pointer to the Input / Output Interfaces
    pOut->PrintMessage("Click on the card you want to Delete....");   //Tells the user to click on the card he wants to Delete
    CellToEmpty = pIn->GetCellClicked();
    pOut->ClearStatusBar();     //Removes the messages from the Status Bar after
}
void DeleteGameObjectAction::Execute()       //Deletes the Game Object in the cell if present
{
    ReadActionParameters();
    Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager.
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    int action;
    action=pGrid->RemoveObjectFromCell(CellToEmpty);

    switch (action)
    {
    case 1:
    
        pOut->PrintMessage("Object Deleted Successfully...");
        break;
    
    case 0:
    
        pOut->PrintMessage("The Selected Cell was already Empty");
        break;
    
    case -1:
        pOut->PrintMessage("Invalid Cell");
        break;
    }
}
DeleteGameObjectAction::~DeleteGameObjectAction()// A Virtual Destructor
{

 }