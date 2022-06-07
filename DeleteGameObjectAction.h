#pragma once
#include "Action.h"
class DeleteGameObjectAction :
    public Action
{
	CellPosition CellToEmpty;

public: 
	DeleteGameObjectAction(ApplicationManager* pApp);

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); //Deletes the Game Object in the cell if present


	virtual ~DeleteGameObjectAction(); // A Virtual Destructor
};

