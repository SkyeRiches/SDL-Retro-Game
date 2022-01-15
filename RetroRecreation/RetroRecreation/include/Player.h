#ifndef _Player_H_
#define _Player_H_
#include "Graphics.h"
#include "Timer.h"
#include "GameEntity.h"
#include "Texture.h"

class Player
{
	// Variables for the player
private:
	static Player* m_PInstance;
	Sprite* m_sPacman;
	Sprite* m_sPacman2;
	SDL_Event m_sdlEvent;
	const int FRAME_RATE = 60;
	Timer* m_tTimer;
	bool hasQuit = false;

	// File path for the leaderboard
	std::string lPath;

	// Player Vector variables
	Vector2 vTranslation = Vector2(0, 0);
	Vector2 startPos = Vector2(300, 370);
	Vector2 vPosition;
	Vector2 vPosition2;

	// Variables for managing endgame and scoring
	int lives = 3;
	int score = 0;
	int highScores[10];

	bool isOpen = true;	// determines the point in the animation

	// Variables for determining if player can move
	bool canMoveL = true;
	bool canMoveR = true;
	bool canMoveU = true;
	bool canMoveD = true;

	float animTime = 0.0f;

public:
	// Player functions
	static Player* Instance();
	void UpdatePacman();
	void RenderPlayer();
	Vector2 GetPosition();
	Vector2 CentrePos();
	Vector2 GetTranslation();
	bool GetQuit();
	void SetCanMoveLeft(bool canGoLeft);
	void SetCanMoveUp(bool canGoUp);
	void SetCanMoveDown(bool canGoDown);
	void SetCanMoveRight(bool canGoRight);
	void PacmanDeath(bool hasDied);
	int GetLives();
	void IncrementScore(int score);
	int GetScore();

private:
	// COnstructor and destructor
	Player();
	~Player();

};
#endif // !_Player_H_
