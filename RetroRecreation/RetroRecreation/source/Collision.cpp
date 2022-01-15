#include "..\include\GameManager.h"
#include <string>
#include <iostream>

/// <summary>
/// checks if there is an instance of the collision system and creates one if there isnt
/// </summary>
/// <returns></returns>
Collision* Collision::Instance()
{
	if (m_CInstance == NULL)
	{
		m_CInstance = new Collision();
	}

	return m_CInstance;
}

/// <summary>
/// checks the position of the player and converts it into a position on the collision array
/// if the value of the position in the array is a 1, then the player cant move there
/// </summary>
void Collision::CheckMapPos(Vector2 playerPos, Player* player)
{
	int y = playerPos.y / 20;
	int x = playerPos.x / 20;

	int posLeft = playerPos.y + 12;

	int posTop = playerPos.x + 12;
	Vector2 posBottom = Vector2(playerPos.x + 12, playerPos.y + 24);
	int xBottom = posBottom.x / 20;
	int yBottom = posBottom.y / 20;

	Vector2 posRight = Vector2(playerPos.x + 24, playerPos.y + 12);
	int posRightY = posRight.y / 20;
	int posRightX = posRight.x / 20;
	
	if (mapCollision[y][posTop / 20] == 1)
	{
		player->SetCanMoveUp(false);

	}
	else
	{
		player->SetCanMoveUp(true);

	}

	if (mapCollision[yBottom][xBottom] == 1)
	{
		player->SetCanMoveDown(false);

	}
	else
	{
		player->SetCanMoveDown(true);

	}

	if (mapCollision[posLeft / 20][x] == 1)
	{
		player->SetCanMoveLeft(false);

	}
	else
	{
		player->SetCanMoveLeft(true);

	}

	if (mapCollision[posRightY][posRightX] == 1)
	{
		player->SetCanMoveRight(false);

	}
	else
	{
		player->SetCanMoveRight(true);

	}
}

/// <summary>
/// Constructor
/// </summary>
Collision::Collision()
{

}

/// <summary>
/// Destructor
/// </summary>
Collision::~Collision()
{

}