#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	NumberOfLadders = 0;
	NumberOfSnakes = 0;
	NumberOfCards = 0;
	
	LadderArr = SnakeArr = CardArr = NULL;

	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if(pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
        CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);

		if (CellList[pos.VCell()][pos.HCell()]->HasLadder())
			NumberOfLadders++;
		else if (CellList[pos.VCell()][pos.HCell()]->HasSnake())
			NumberOfSnakes++;
		else if (CellList[pos.VCell()][pos.HCell()]->HasCard())
			NumberOfCards++;

		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
int Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell() && CellList[pos.VCell()][pos.HCell()]->GetGameObject()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		if (CellList[pos.VCell()][pos.HCell()]->HasLadder())
			NumberOfLadders--;
		else if (CellList[pos.VCell()][pos.HCell()]->HasSnake())
			NumberOfSnakes--;
		else if (CellList[pos.VCell()][pos.HCell()]->HasCard())
			NumberOfCards--;
	
		delete CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
		return 1;

	}
	else if (pos.IsValidCell() && !CellList[pos.VCell()][pos.HCell()]->GetGameObject())
		return 0;
	else
		return -1;

}

void Grid::RemoveAllObjects()
{
	// if grid has no gameobjects it should return
	if (NumberOfCards == 0 && NumberOfSnakes == 0 && NumberOfLadders == 0)
		return;

	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
		}
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


bool Grid::isOverlapping(GameObject* newGameObj) const
{
	bool OverlappingCheck = false;
	GameObject* pGameObj;
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			pGameObj = CellList[i][j]->GetGameObject();
			if (pGameObj) {
				OverlappingCheck = pGameObj->IsOverlapping(newGameObj);
				if (OverlappingCheck)
					return true;
			}
		}
	}

	return false;
}



// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

Player* Grid::getPoorestPlayer() const {
	Player* poorest = NULL;
	if (currPlayerNumber != 0)
		poorest = PlayerList[0];
	else
		poorest = PlayerList[1];

	for (int i = 0; i < MaxPlayerCount; i++) {
		if (i == currPlayerNumber)
			continue;
		else if (PlayerList[i]->GetWallet() < poorest->GetWallet())
			poorest = PlayerList[i];
	}
	return poorest;
}

bool Grid::HasCard(CellPosition pos) {
	if (CellList[pos.VCell()][pos.HCell()]->HasCard())
		return true;
	else
		return false;
}

void Grid::SetClipboard(CellPosition pos) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Card* original = CellList[pos.VCell()][pos.HCell()]->HasCard();
	Clipboard = original->Copy(original);
}

void Grid::SetClipboard(Card* pCard)
{
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

int Grid::getCurrPlayerNumber() const {
	return currPlayerNumber;
}

int Grid::GetNumberOfCards() const {
	return NumberOfCards;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

bool Grid::HasLadder(int V, int H)
{
	if (CellList[V][H]->HasLadder())
		return true;
	else
		return false;
}

bool Grid::HasSnake(int V, int H)
{
	if (CellList[V][H]->HasSnake())
		return true;
	else
		return false;
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder())
				return CellList[i][j]->HasLadder();
			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

Player* Grid::getNextPlayer(Player* pPlayer)const {

	Player* nextPlayer;
	int currentPos = pPlayer->GetCell()->GetCellPosition().GetCellNum();
	int min = 101;
	int diff;

	for (int i = 0; i < MaxPlayerCount; i++) {
		if (PlayerList[i] == pPlayer)
			continue;

		diff = PlayerList[i]->GetCell()->GetCellPosition().GetCellNum() - currentPos;

		if (diff < min && diff > 0) {
			min = diff;
			nextPlayer = PlayerList[i];
		}

	}

	return nextPlayer;
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


void Grid::LocateAllGameObjects()
{
	int LadderIndex = 0;
	int SnakeIndex = 0;
	int CardIndex = 0;

	// Deletes old gameobject arrays
	if (LadderArr)
		delete[] LadderArr;
	if (SnakeArr)
		delete[] SnakeArr;
	if (CardArr)
		delete[] CardArr;

	// Creating new arrays with the updated gameobjects on the grid
	LadderArr = new GameObject * [NumberOfLadders];
	SnakeArr = new GameObject * [NumberOfSnakes];
	CardArr = new GameObject * [NumberOfCards];

	for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // left to right
		{
			if (CellList[i][j]->HasLadder())
				LadderArr[LadderIndex++] = CellList[i][j]->GetGameObject();
			else if (CellList[i][j]->HasSnake())
				SnakeArr[SnakeIndex++] = CellList[i][j]->GetGameObject();
			else if (CellList[i][j]->HasCard())
				CardArr[CardIndex++] = CellList[i][j]->GetGameObject();
		}
	}
}


void Grid::SavetoFile(ofstream& OutFile) {

	// Getting the gameobjects on the grid and adding each gameobject to its specificied array

	LocateAllGameObjects();
	OutFile << NumberOfLadders << endl;
	for (int i = 0; i < NumberOfLadders; i++)
	{
		LadderArr[i]->Save(OutFile);
	}
	OutFile << NumberOfSnakes << endl;
	for (int i = 0; i < NumberOfSnakes; i++)
	{
		SnakeArr[i]->Save(OutFile);
	}
	OutFile << NumberOfCards << endl;
	for (int i = 0; i < NumberOfCards; i++)
	{
		CardArr[i]->Save(OutFile);
	}
}

void Grid::Restart() {
	CellPosition startPos(8, 0);
	for (int i = 0; i < MaxPlayerCount; i++) {
		UpdatePlayerCell(PlayerList[i], startPos);
		PlayerList[i]->SetWallet(100);
		PlayerList[i]->SetTurnCount(0);
	}
	currPlayerNumber = 0;
	CardNine* card9 = new CardNine(startPos);
	CardTen* card10 = new CardTen(startPos);
	CardEleven* card11 = new CardEleven(startPos);
	card9->setOwner(NULL);
	card10->setOwner(NULL);
	card11->setOwner(NULL);
	delete card9;
	delete card10;
	delete card11;
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	delete[] LadderArr;
	delete[] SnakeArr;
	delete[] CardArr;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			if (CellList[i][j]->GetGameObject())
				delete CellList[i][j]->GetGameObject();
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}