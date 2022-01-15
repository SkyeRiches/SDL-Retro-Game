#include "..\include\GameManager.h"

/// <summary>
/// creates a new instance of the pellets
/// </summary>
/// <param name="a_pos"></param>
Pellet::Pellet(Vector2 a_pos)
{
	std::string sPathA = SDL_GetBasePath();
	sPathA.append("Assets/Pickup.png");
	pellet = new Sprite(sPathA, a_pos, 20, 20, 0.0f);
}

/// <summary>
/// draws the pellet on screen
/// </summary>
void Pellet::RenderPellet()
{
	if (!isCollected)
	{
		pellet->Render();
	}
}

/// <summary>
/// returns the postion of the centre of the pellet rather than the top left corner
/// </summary>
/// <returns></returns>
Vector2 Pellet::CentrePos()
{
	Vector2 pos = pellet->GetPos();
	float posX = pos.x + 10;
	float posY = pos.y + 10;
	return Vector2(posX, posY);
}

/// <summary>
/// checks if the player and pellet are colliding
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
bool Pellet::PickupCheck(Player* player)
{
	Vector2 vPelletToPlayer = PelletToPlayer(player); // Gets the vector between the player and the pellet
	float pelletVectorsqr = Pythag(vPelletToPlayer);  // Gets the hypotenuse of the vector between them
	float pelletRadSqrd = 10 * 10;                   // Square of the radius of the pellet
	if (pelletVectorsqr <= pelletRadSqrd)             // if the distance between them is less than the radius squared
	{
		if (!isCollected)
		{
			player->IncrementScore(10); // increase the players score
		}
		isCollected = true;
		return true;
	}

	return false;
}

/// <summary>
/// vector distance between the player and the pellet
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
Vector2 Pellet::PelletToPlayer(Player* player)
{
	Vector2 v2A = player->CentrePos();
	Vector2 v2B = CentrePos();
	Vector2 v2C = v2B - v2A;
	return v2C;
}

/// <summary>
/// returns the hypotenuse of the vector between the player and pellet
/// </summary>
/// <param name="a_vec"></param>
/// <returns></returns>
float Pellet::Pythag(Vector2 a_vec)
{
	float xSqr = a_vec.x * a_vec.x;
	float ySqr = a_vec.y * a_vec.y;
	return (xSqr + ySqr);
}

Pellet::~Pellet()
{
	delete this;
}