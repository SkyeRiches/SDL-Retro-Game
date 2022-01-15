#ifndef _POWERUP_H_
#define _POWERUP_H_
#include "Graphics.h"
#include "GameEntity.h"
#include "Texture.h"
#include <Player.h>

class PowerUp
{
private:
	// Variables for the power up pellets
	Sprite* powerup;
	bool isCollected = false;
	bool powerReady = false;
	~PowerUp();

public:
	// Functions for the power up pellets
	PowerUp(Vector2 a_pos);
	Vector2 CentrePos();
	void RenderPowUp();
	bool PickupCheck(Player* player);
	Vector2 PowUpToPlayer(Player* player);
	float Pythag(Vector2 a_vec);
	bool GetCollected();
};


#endif // !_POWERUP_H_
