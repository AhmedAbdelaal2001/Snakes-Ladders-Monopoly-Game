#pragma once
#include "Action.h"

class ToDesignModeAction : public Action
{
public:
	ToDesignModeAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~ToDesignModeAction(); // A Virtual Destructor
};


