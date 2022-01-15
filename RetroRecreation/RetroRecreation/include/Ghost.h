#ifndef _Ghost_H_
#define _Ghost_H_
#include "Graphics.h"
#include "Timer.h"
#include "GameEntity.h"
#include "Texture.h"
#include <string>

class Ghost
{
private:
	// Variables for the ghosts
	std::string name;
	float speed;
	Vector2 vStartPos;
	Vector2 vTransform;
	Vector2 vRoute[8];
	Vector2 vPrison;
	bool scaredState = false;
	int routePos;
	bool deathState = false;
	Sprite* m_sGhost;
	Sprite* m_sScared;

	// Destructor
	~Ghost();

public:
	// Constructor
	Ghost(std::string path, Vector2 startPos, std::string a_name, float a_speed, Vector2 a_route[8]);

	// Functions for the ghosts
	void Move();
	void Reset();
	void Respawn();
	void RenderGhost();
	void SetScared(bool isScared);
	Vector2 GhostPos();
	bool PlayerColCheck(Player* player);
	Vector2 GhostToPlayer(Player* player);
	float Pythag(Vector2 a_vec);
	
};

#endif // !_Ghost_H_