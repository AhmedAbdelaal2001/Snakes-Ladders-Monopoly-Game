#include "OpenGridAction.h"
#include "Grid.h"
#include "Ladder.h"
#include "Snake.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"

#include <fstream>

OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

OpenGridAction::~OpenGridAction()
{
}


void OpenGridAction::ReadActionParameters()
{
}


// Execute the action
void OpenGridAction::Execute()
{
	
	int numberOfObjects = 0;
	int startPos;
	int endPos;
	int cardNumber;
	GameObject* pGameObject = NULL;

	// Deleting current grid
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Grid Opened...");
	pGrid->RemoveAllObjects();

	// Just a check so that if the file is corrupt nothing happens
	ifstream InFile("Grid.txt");
	if (InFile.fail())
		return;

	// Reading from the file
	InFile >> numberOfObjects;
	for (int i = 0; i < numberOfObjects; i++)
	{
		CellPosition StartCellPosition(1);
		CellPosition EndCellPosition(13);
		pGameObject = new Ladder(StartCellPosition, EndCellPosition);
		pGameObject->Load(InFile);
		pGrid->AddObjectToCell(pGameObject);
	}

	InFile >> numberOfObjects;
	for (int i = 0; i < numberOfObjects; i++)
	{
		CellPosition StartCellPosition(13);
		CellPosition EndCellPosition(1);
		pGameObject = new Snake(StartCellPosition, EndCellPosition);
		pGameObject->Load(InFile);
		pGrid->AddObjectToCell(pGameObject);
	}
	
	InFile >> numberOfObjects;
	for (int i = 0; i < numberOfObjects; i++)
	{
		InFile >> cardNumber;
		CellPosition cardPos(1);
		switch(cardNumber)
		{
		case 1:
			pGameObject = new CardOne(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 2:
			pGameObject = new CardTwo(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 3:
			pGameObject = new CardThree(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 4:
			pGameObject = new CardFour(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 5:
			pGameObject = new CardFive(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 6:
			pGameObject = new CardSix(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 7:
			pGameObject = new CardSeven(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 8:
			pGameObject = new CardEight(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 9:
			pGameObject = new CardNine(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 10:
			pGameObject = new CardTen(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 11:
			pGameObject = new CardEleven(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		case 12:
			pGameObject = new CardTwelve(cardPos);
			pGameObject->Load(InFile);
			pGrid->AddObjectToCell(pGameObject);
			break;
		}

	}
}