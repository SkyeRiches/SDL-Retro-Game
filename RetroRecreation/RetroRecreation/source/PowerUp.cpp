#include "..\include\GameManager.h"

/// <summary>
/// Creates a new instance of the power up pellet
/// </summary>
/// <param name="a_pos"></param>
PowerUp::PowerUp(Vector2 a_pos)
{
	std::string sPathA = SDL_GetBasePath();
	sPathA.append("Assets/Power.png");
	powerup = new Sprite(sPathA, a_pos, 20, 20, 0.0f);
}

/// <summary>
/// Renders the powerup if it hasnt been collected by the player
/// </summary>
void PowerUp::RenderPowUp()
{
	if (!isCollected)
	{
		powerup->Render();
	}
}

/// <summary>
/// Returns the Vector for the centre of the sprite rather than the top left corner
/// </summary>
/// <returns></returns>
Vector2 PowerUp::CentrePos()
{
	Vector2 pos = powerup->GetPos();
	float posX = pos.x + 10;
	float posY = pos.y + 10;
	return Vector2(posX, posY);
}

/// <summary>
/// Checks if the player has picked up the powerup, they can only pick it up and gain score if they havent already
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
bool PowerUp::PickupCheck(Player* player)
{
	Vector2 vPowUpToPlayer = PowUpToPlayer(player); // Gets the vector between the player and the pellet
	float powUpVectorsqr = Pythag(vPowUpToPlayer);  // Gets the hypotenuse of the vector between them
	float powUpRadSqrd = 10 * 10;                   // Square of the radius of the pellet
	if (powUpVectorsqr <= powUpRadSqrd)             // if the distance between them is less than the radius squared
	{
		if (!isCollected)
		{
			player->IncrementScore(50); // Increases players score
			powerReady = true;
			isCollected = true;
			return true;
		}
		powerReady = false;
	}
	return false;
}

/// <summary>
/// distance between the powerup and the player
/// </summary>
/// <param name="player"></param>
/// <returns></returns>
Vector2 PowerUp::PowUpToPlayer(Player* player)
{
	Vector2 v2A = player->CentrePos();
	Vector2 v2B = CentrePos();
	Vector2 v2C = v2B - v2A;
	return v2C;
}

/// <summary>
/// Finds the square of the hypotenuse of the vector between the player and the pellet
/// </summary>
/// <param name="a_vec"></param>
/// <returns></returns>
float PowerUp::Pythag(Vector2 a_vec)
{
	float xSqr = a_vec.x * a_vec.x;
	float ySqr = a_vec.y * a_vec.y;
	return (xSqr + ySqr);
}

/// <summary>
/// returns if the powerup instance has been collected
/// </summary>
/// <returns></returns>
bool PowerUp::GetCollected()
{
	return powerReady;
}

PowerUp::~PowerUp()
{
	
}