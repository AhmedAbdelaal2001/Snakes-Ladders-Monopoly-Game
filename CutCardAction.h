#pragma once
#include "Action.h"
class CutCardAction :
    public Action
{
	CellPosition CutCell;

public:
	CutCardAction(ApplicationManager* pApp);

	virtual void ReadActionParameters(); // Reads CutCardAction action parameters Cell Position

	virtual void Execute(); // Cuts the card from the cell selected


	virtual ~CutCardAction(); // A Virtual Destructor
};

