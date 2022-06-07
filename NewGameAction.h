#pragma once
#include "Action.h"

class NewGameAction : public Action
{
public:
	NewGameAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute(); // Saves the Grid to file


	virtual ~NewGameAction(); // Virtual Destructor
};

