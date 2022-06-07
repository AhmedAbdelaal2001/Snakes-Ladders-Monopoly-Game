#pragma once
#include "Action.h"

class SaveGridAction : public Action
{
public:

	SaveGridAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); 

	virtual void Execute(); // Saves the Grid to file


	virtual ~SaveGridAction(); // Virtual Destructor
};

