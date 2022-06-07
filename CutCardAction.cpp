#include "CutCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"
#include "Cell.h"
#include "CellPosition.h"
#include "CopyCardAction.h"

CutCardAction::CutCardAction(ApplicationManager* pApp):Action(pApp)
{
}

void CutCardAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();       // Get a Pointer to the Input / Output Interfaces
    pOut->PrintMessage("Click on the card you want to Cut....");   //Tells the user to click on the card he wants to Cut
    CutCell = pIn->GetCellClicked();

    pOut->ClearStatusBar();
}// Reads CutCardAction action parameters Cell Position

void CutCardAction::Execute()
{
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    if (CutCell.IsValidCell() == false)
    {
        pOut->PrintMessage("Invalid Cell...");
    }

    else if (!(pGrid->HasCard(CutCell)))
    {
        pOut->PrintMessage("The Cell selected has no Card....");
    }
    else if (pGrid->HasCard(CutCell) && CutCell.IsValidCell())         //Check if the cell chosen has a card or not.
    {
        pGrid->SetClipboard(CutCell);   //Sets the ClipBoard with the cell position of the cell the player clicked onto

        /*Card* pCard = new Card(0);
        *pCard = *pGrid->GetClipboard();*/

        pOut->PrintMessage("Card Cut Succesfully....");
        pGrid->RemoveObjectFromCell(CutCell);

        /*Card* CutCard = pGrid->GetClipboard();
        CutCard->SetPosition(7, 2);

        int action;
        action = pGrid->RemoveObjectFromCell(CutCell);
        */
    }
   
}// Cuts the card from the cell selected
CutCardAction::~CutCardAction()
{

     }// A Virtual Destructor
