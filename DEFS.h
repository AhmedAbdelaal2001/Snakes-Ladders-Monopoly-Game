#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.


enum GameObjectErrorType // The potential errors that might occur when creating a game object.
{
	VALID_OBJECT,	//The Object is Valid and has no errors
	INVALID_START,	//The object has an invalid start cell position
	INVALID_END,	//The object has an invalid end cell position
	INVALID_START_END,	//The object has invalid start and end cell positions
	NOT_SAME_COLUMN,	//In the case of ladders or snakes, the object is not on one vertical line
	START_END_REVERSED,	//In the case of ladders or snakes, the start and end positions are reversed
	COLUMN_AND_REVERSING_ERROR	//Both the previous errors occured simultaneously
};

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode

	ADD_LADDER,		// Add Ladder Action
	ADD_SNAKE,		// Add Snake Action	
	ADD_CARD,		// Add Card Action	
	TO_PLAY_MODE,	// Go to Play Mode
	EXIT,			// Exit Application
	COPY_CARD,
	CUT_CARD,
	PASTE_CARD,
	DELETE_GAME_OBJECT,
	SAVE_GRID,
	OPEN_GRID,
	
	///TODO: Add more action types of Design Mode
	//DONE

	//  [2] Actions of Play Mode

	ROLL_DICE,		// Roll Dice Action
	TO_DESIGN_MODE,	// Go to Design Mode

	///TODO: Add more action types of Play Mode
	//DONE

	INPUT_DICE_VALUE,
	NEW_GAME,

	//  [3] Others

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS 				// Inside StatusBar Area
};

#endif