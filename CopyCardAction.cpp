#include "CopyCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"
#include "Cell.h"
#include "CellPosition.h"

CopyCardAction::CopyCardAction(ApplicationManager* pApp):Action(pApp)
{

}

void CopyCardAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();       // Get a Pointer to the Input / Output Interfaces
    pOut->PrintMessage("Click on the card you want to copy....");   //Tells the user to click on the card he wants to copy
    CardCell= pIn->GetCellClicked();      

    pOut->ClearStatusBar();     //Removes the messages from the Status Bar after
} 

void CopyCardAction::Execute()    // Creates a copy  of the specific Card Number
{
    ReadActionParameters();
    Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager.
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    
    if (CardCell.IsValidCell() == false)
    {
        pOut->PrintMessage("Invalid Cell...");
    }

    else if(!(pGrid->HasCard(CardCell)))
    {
        pOut->PrintMessage("The Cell selected has no Card....");
       
    }
    else if(pGrid->HasCard(CardCell) && CardCell.IsValidCell())         //Check if the cell chosen has a card or not.
    {
        pGrid->SetClipboard(CardCell);   //Sets the ClipBoard with the cell position of the cell the player clicked onto
        pOut->PrintMessage("Card Copied....");
    }
    
} 

CopyCardAction::~CopyCardAction()
{

} // A Virtual Destructor
