#pragma once
#include "Action.h"
class PasteCardAction :
    public Action
{
	CellPosition PasteCell;
public:
	PasteCardAction(ApplicationManager* pApp);   //Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Pastes the pre-Selected card to the Cell chosen


	virtual ~PasteCardAction(); // A Virtual Destructor
};

