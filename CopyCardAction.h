#pragma once
#include "Action.h"
class CopyCardAction : public Action
{

	CellPosition CardCell; //cell position of the card the player wants to copy

public:
	CopyCardAction(ApplicationManager* pApp);

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a copy  of the specific Card Number
	

	virtual ~CopyCardAction(); // A Virtual Destructor
};

