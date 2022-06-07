#include "CardTwelve.h"
#include <iostream>


using namespace std;

CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	

	cardNumber = 12; // set the inherited cardNumber data member with the card number (12 here)
}

CardTwelve::~CardTwelve(void)
{
	

}

void CardTwelve::ReadCardParameters(Grid* pGrid)
{
	// No parameters will be read
}

Card* CardTwelve::Copy(Card* pCard) {
	CellPosition pos;
	CardTwelve* copy = new CardTwelve(pos);

	return copy;
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	CellPosition invalidPos(-1, -1);
	card9 = new CardNine(invalidPos);
	card10 = new CardTen(invalidPos);
	card11 = new CardEleven(invalidPos);
	int maxValue, maxIndex;
	int prices[3] = { -1,-1,-1 };
	// Getting poorest player on the grid (not including currPlayer)
	Player* poorestPlayer = pGrid->getPoorestPlayer();
	

	if (card9->getOwner() != pPlayer)
		card9 = NULL;
	if (card10->getOwner() != pPlayer)
		card10 = NULL;
	if (card11->getOwner() != pPlayer)
		card11 = NULL;


	if (!(card9 || card10 || card11)) {
		return;
	}

	if (card9)
		prices[0] = card9->getPrice();
	if (card10)
		prices[1] = card10->getPrice();
	if (card11)
		prices[2] = card11->getPrice();

	maxValue = prices[0];
	maxIndex = 0;
	for (int i = 1; i < 3; i++) {
		if (prices[i] > maxValue) {
			maxIndex = i;
			maxValue = prices[i];
		}
	}

	switch (maxIndex) {
	case 0:
		card9->setOwner(poorestPlayer);
		pGrid->PrintErrorMessage("You just lost your most expensive card (Card 9) to player number " + to_string(poorestPlayer->getPlayerNum()) + "....");
		break;
	case 1:
		card10->setOwner(poorestPlayer);
		pGrid->PrintErrorMessage("You just lost your most expensive card (Card 10) to player number " + to_string(poorestPlayer->getPlayerNum()) + "....");
		break;
	case 2:
		card11->setOwner(poorestPlayer);
		pGrid->PrintErrorMessage("You just lost your most expensive card (Card 11) to player number " + to_string(poorestPlayer->getPlayerNum()) + "....");
		break;
	}

	delete card9;
	delete card10;
	delete card11;
}


void CardTwelve::Save(ofstream& OutFile)
{
	Card::Save(OutFile);
}

void CardTwelve::Load(ifstream& InFile)
{
	Card::Load(InFile);
}
