#pragma once
#include "Action.h"

class ToPlayModeAction : public Action
{
public:
	ToPlayModeAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); 

	virtual void Execute(); 

	virtual ~ToPlayModeAction(); // A Virtual Destructor
};

