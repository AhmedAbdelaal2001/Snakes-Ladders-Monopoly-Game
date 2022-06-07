#include "Player.h"

#include "GameObject.h"

Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum), justRolledDiceNum(0)
{
	this->pCell = pCell;
	this->turnCount = 0;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

int Player::getPlayerNum() const {
	return playerNum;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet;
	// Make any needed validations
}
void Player::SetTurnCount(int turnCount)
{
	this->turnCount = turnCount;
}

void Player::SetJustRolledDiceNum(int justRolledDiceNum)
{
	this->justRolledDiceNum = justRolledDiceNum;
}
int Player::GetJustRolledDiceNum() const
{
	return justRolledDiceNum;
}

void Player::SetPrison(int s)
{
	if (s > 0)
		Prison = s;
	else
		Prison = 0;
}
int  Player::GetPrison() const
{
	return Prison;
}

void Player::SetStop(int s)
{
	if (s > 0)
		Stop = s;
	else
		Stop = 0;
}
int  Player::GetStop() const
{
	return Stop;
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);

	///TODO: use the appropriate output function to draw the player with "playerColor"
	//DONE

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);

	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	//DONE
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	//DONE

	if (Prison > 0)
	{
		Prison--;
		return;
	}

	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	if (!(pCell->HasLadder() || pCell->HasSnake()))
		turnCount++;

	if (Stop > 0 && turnCount == 3)
	{
		turnCount = 0;
		Stop--;
		return;
	}
	else if (Stop > 0)

	{
		Stop--;
		return;
	}
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount == 3) {
		wallet += diceNumber * 10;
		turnCount = 0;
		return;
	}

	// 3- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum = diceNumber;

	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"

	//Freezes the player until wallet is recharged
	if (wallet <= 0)
		return;
	CellPosition pos = pCell->GetCellPosition();
	pos.AddCellNum(diceNumber);

	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this, pos);

	// 6- Apply() the game object of the reached cell (if any)
	if (pCell->GetGameObject())
		pCell->GetGameObject()->Apply(pGrid, this);

	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (pCell->GetCellPosition().GetCellNum() == 99)
		pGrid->SetEndGame(true);

}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}