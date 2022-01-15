#ifndef _PELLET_H_
#define _PELLET_H_
#include "Graphics.h"
#include "GameEntity.h"
#include "Texture.h"

class Pellet
{
private:
	// Variables for the pellets
	Sprite* pellet;
	bool isCollected = false;

	// Destructor
	~Pellet();

public:
	// Functions for the pellets
	Pellet(Vector2 a_pos);
	Vector2 CentrePos();
	void RenderPellet();
	bool PickupCheck(Player* player);
	Vector2 PelletToPlayer(Player* player);
	float Pythag(Vector2 a_vec);
};

#endif // !_PELLET_H_

