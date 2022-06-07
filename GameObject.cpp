#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position

	if (pos.IsValidCell())
		Validity = VALID_OBJECT;
	else
		Validity = INVALID_START;
}

void GameObject::SetPosition(int VCell, int HCell)
{
	position.SetHCell(HCell);
	position.SetVCell(VCell);
}

bool GameObject::IsOverlapping(GameObject* newObj) const
{
	return false;
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

GameObjectErrorType GameObject::GetValidity() const
{
	return Validity;
}


GameObject::~GameObject()
{
}