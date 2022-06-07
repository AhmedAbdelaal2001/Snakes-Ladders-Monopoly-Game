#include "PasteCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"
#include "Cell.h"
#include "CellPosition.h"
PasteCardAction::PasteCardAction(ApplicationManager* pApp):Action(pApp)
{

     }
void PasteCardAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();       // Get a Pointer to the Input / Output Interfaces
    pOut->PrintMessage("Click on the cell you want to paste the card to....");   //Tells the user to click on the card he wants to copy
    PasteCell = pIn->GetCellClicked();
    pOut->ClearStatusBar();     //Removes the messages from the Status Bar after
}
void PasteCardAction::Execute()
{
    ReadActionParameters();
    Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager.
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    if (PasteCell.IsValidCell() == false)
    {
        pOut->PrintMessage("Invalid Cell...");
        return;
    }

    Card * pasteCard = pGrid->GetClipboard();
    int newHCell = PasteCell.HCell();
    int newVCell = PasteCell.VCell();

    pasteCard->SetPosition(newVCell, newHCell);

    bool added = pGrid->AddObjectToCell(pasteCard);


    // if the GameObject cannot be added
    if (!added)
    {
        // Print an appropriate message
        pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
    }
    
}// Pastes the pre-Selected card to the Cell chosen
PasteCardAction::~PasteCardAction()
{

     }// A Virtual Destructor