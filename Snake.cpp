#include "Snake.h"
#include "Ladder.h"
#include "Player.h"
#include <iostream>

using namespace std;

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation

	if (Validity == VALID_OBJECT)
	{
		if (position.HCell() != endCellPos.HCell() && endCellPos.VCell() <= position.VCell())
			Validity = COLUMN_AND_REVERSING_ERROR;
		else if (position.HCell() != endCellPos.HCell())
			Validity = NOT_SAME_COLUMN;
		else if (endCellPos.VCell() <= position.VCell())
			Validity = START_END_REVERSED;


		if (!endCellPos.IsValidCell())
			Validity = INVALID_END;
	}
	else if (!endCellPos.IsValidCell())
		Validity = INVALID_START_END;
}

bool Snake::IsOverlapping(GameObject* newObj) const
{
	Snake* pSnake = dynamic_cast<Snake*>(newObj);
	if (pSnake)
	{
		int HPosition1 = position.HCell();
		int HPosition2 = newObj->GetPosition().HCell();

		int VStartPosition1 = position.VCell();
		int VEndPosition1 = endCellPos.VCell();
		int VStartPosition2 = newObj->GetPosition().VCell();
		int VEndPosition2 = pSnake->GetEndPosition().VCell();

		if (HPosition1 == HPosition2 && ((VStartPosition2 > VStartPosition1 && VStartPosition2 <= VEndPosition1) || (VStartPosition1 > VStartPosition2 && VStartPosition1 <= VEndPosition2)))
			return true;
	}
	else {
		Ladder* pLadder = dynamic_cast<Ladder*>(newObj);
		if (pLadder) {
			int LadderVStartCell = pLadder->GetPosition().VCell();
			int LadderHStartCell = pLadder->GetPosition().HCell();

			int SnakeVEndCell = endCellPos.VCell();
			int SnakeHEndCell = endCellPos.HCell();

			if (LadderVStartCell == SnakeVEndCell && LadderHStartCell == SnakeHEndCell)
				return true;
		}
	}
	return false;
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	int x, y;
	int move;
	Player* currPlayer;

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a snake. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a snake. Click to continue ...");

	// 2- Apply the snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	move = endCellPos.GetCellNum() - position.GetCellNum();
	currPlayer = pGrid->GetCurrentPlayer();
	currPlayer->Move(pGrid, move);

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << "\t" << endCellPos.GetCellNum() << endl;
}

void Snake::Load(ifstream& InFile)
{
	int startPos, endPos;
	InFile >> startPos >> endPos;
	CellPosition StartCellPosition(startPos);
	CellPosition EndCellPosition(endPos);
	position = StartCellPosition;
	endCellPos = EndCellPosition;
}

Snake::~Snake()
{
}
