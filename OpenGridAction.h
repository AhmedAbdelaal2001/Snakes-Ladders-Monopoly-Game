#pragma once
#include "Action.h"

class OpenGridAction : public Action
{
public:

	OpenGridAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddLadderAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Ladder Object 
							// then Sets this Ladder object to the GameObject Pointer of its Cell


	virtual ~OpenGridAction(); // Virtual Destructor
};

