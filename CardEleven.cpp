#include "CardEleven.h"


int CardEleven::NumberOfCards = 0;
int CardEleven::fees = 0;
int CardEleven::price = 0;
Player* CardEleven::owner = NULL;

CardEleven::CardEleven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	
	NumberOfCards++;
	cardNumber = 11; // set the inherited cardNumber data member with the card number (11 here)

}

CardEleven::~CardEleven()
{
	NumberOfCards--;
}

void CardEleven::ReadCardParameters(Grid* pGrid)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	if (NumberOfCards == 1) {
		// 1- Get a Pointer to the Input / Output Interfaces from the Grid
		Input* pIn = pGrid->GetInput();
		Output* pOut = pGrid->GetOutput();

		// 2- Read an Integer from the user using the Input class and set the fees and price parameter with it

		pOut->PrintMessage("Enter Station Price: ");
		price = pIn->GetInteger(pOut);

		pOut->ClearStatusBar();

		pOut->PrintMessage("Enter Station Fees: ");
		fees = pIn->GetInteger(pOut);

		pOut->ClearStatusBar();
	}

}

void CardEleven::setOwner(Player* pPlayer) {
	owner = pPlayer;
}

Player* CardEleven::getOwner() const {
	return owner;
}

int CardEleven::getPrice() const {
	return price;
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	string msg, choice;
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// if owner is standing on the card nothing happens
	if (pPlayer == owner) {
		pOut->PrintMessage("This is your card!");
		return;
	}
	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);

	// 2-Checks for owner and if there is one and current player is not the owner it will deduct fees from the wallet
	// if there's no owner then it will ask if the player wants to purchase it

	if (owner && pPlayer != owner) {
		msg = "You must pay " + to_string(fees);
		pGrid->PrintErrorMessage(msg);
		int afterPaying = pPlayer->GetWallet() - fees;
		pPlayer->SetWallet(afterPaying);

		int afterReceivng = owner->GetWallet() + fees;
		owner->SetWallet(afterReceivng);
	}
	else if (!owner) {
		msg = "This station has price = " + to_string(price) + " and fees = " + to_string(fees) + ".... will you buy it (y/n)?";
		pOut->PrintMessage(msg);
		choice = pIn->GetString(pOut);

		if (choice == "y") {
			if (pPlayer->GetWallet() >= price) {
				pGrid->PrintErrorMessage("Congrats on your purchase! You are now the proud owner of all no." + to_string(cardNumber) + " cards. Click to continue...");
				owner = pPlayer;
				int afterPurchasing = pPlayer->GetWallet() - price;
				pPlayer->SetWallet(afterPurchasing);
			}
			else if (pPlayer->GetWallet() < price) {
				pGrid->PrintErrorMessage("Not enough coins...");
			}
		}
	}
}

void CardEleven::Save(ofstream& OutFile) {
	Card::Save(OutFile);
	static int count = 0;
	if (count == 0) {
		OutFile << price << "\t" << fees << endl;
	}
	else {
		OutFile << endl;
	}
	count++;

	if (count == NumberOfCards)
		count = 0;
}

void CardEleven::Load(ifstream& Infile) {
	Card::Load(Infile);
	if (NumberOfCards == 1) {
		Infile >> price >> fees;
	}
}

Card* CardEleven::Copy(Card* pCard) {
	CellPosition pos;
	CardEleven* copy = new CardEleven(pos);

	return copy;
}
