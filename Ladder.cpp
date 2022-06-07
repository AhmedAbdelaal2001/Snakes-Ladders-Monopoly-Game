#include "Ladder.h"
#include "Player.h"
#include "Snake.h"

#include <iostream>
using namespace std;

Ladder::Ladder(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
	if (Validity == VALID_OBJECT)
	{
		if (position.HCell() != endCellPos.HCell() && endCellPos.VCell() >= position.VCell())
			Validity = COLUMN_AND_REVERSING_ERROR;
		else if (position.HCell() != endCellPos.HCell())
			Validity = NOT_SAME_COLUMN;
		else if (endCellPos.VCell() >= position.VCell())
			Validity = START_END_REVERSED;


		if (!endCellPos.IsValidCell())
			Validity = INVALID_END;
	}
	else if (!endCellPos.IsValidCell())
		Validity = INVALID_START_END;
}

bool Ladder::IsOverlapping(GameObject* newObj) const
{
	Ladder* pLadder = dynamic_cast<Ladder*>(newObj);
	if (pLadder)
	{
		int HPosition1 = position.HCell();
		int HPosition2 = newObj->GetPosition().HCell();

		int VStartPosition1 = position.VCell();
		int VEndPosition1 = endCellPos.VCell();
		int VStartPosition2 = newObj->GetPosition().VCell();
		int VEndPosition2 = pLadder->GetEndPosition().VCell();

		if (HPosition1 == HPosition2 && ((VStartPosition2 < VStartPosition1 && VStartPosition2 >= VEndPosition1) || (VStartPosition1 < VStartPosition2 && VStartPosition1 >= VEndPosition2)))
			return true;

	}
	else {
		Snake* pSnake = dynamic_cast<Snake*>(newObj);
		if (pSnake) {
			int SnakeVStartCell = pSnake->GetPosition().VCell();
			int SnakeHStartCell = pSnake->GetPosition().HCell();

			int LadderVEndCell = endCellPos.VCell();
			int LadderHEndCell = endCellPos.HCell();

			if (SnakeVStartCell == LadderVEndCell && SnakeHStartCell == LadderHEndCell)
				return true;
		}
	}


	return false;
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	int move;
	Player* currPlayer;

	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");


	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	move = endCellPos.GetCellNum() - position.GetCellNum();
	currPlayer = pGrid->GetCurrentPlayer();
	currPlayer->Move(pGrid, move);
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

void Ladder::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << "\t" << endCellPos.GetCellNum() << endl;
}

void Ladder::Load(ifstream& InFile) 
{
	int startPos, endPos;
	InFile >> startPos >> endPos;
	CellPosition StartCellPosition(startPos);
	CellPosition EndCellPosition(endPos);
	position = StartCellPosition;
	endCellPos = EndCellPosition;
}

Ladder::~Ladder()
{
}
