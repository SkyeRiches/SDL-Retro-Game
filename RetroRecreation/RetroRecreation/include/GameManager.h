#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "Graphics.h"
#include "Timer.h"
#include "GameEntity.h"
#include "Texture.h"
#include "Player.h"
#include "Map.h"
#include "Collision.h"
#include "Ghost.h"
#include "GUI.h"
#include "Pellet.h"
#include "PowerUp.h"
#include "Splash.h"
#include <iostream>
#include <fstream>
#include <string>

class GameManager
{
private:
	enum GAME_STATE
	{
		SPLASH,
		MENU,
		PLAY,
		LEADERBOARD,
		CREDITS,
	};

	GAME_STATE currentGameState = SPLASH;
	static GameManager* m_sInstance;
	const int FRAME_RATE = 60;
	Timer* m_tTimer;
	float timePassed;
	float totalTime;
	bool pacmanDied = false;
	bool powerActivated = false;
	bool blinkyDied;
	bool inkyDied;
	bool pinkyDied;
	bool clydeDied;
	float powerDuration = 5.0f;

	// Splash screen variables
	Splash* splashScreen;

	// Menu variables
	Sprite* menuBackground;
	Sprite* menuText;
	Vector2 menuPos = Vector2(50, 50);

	// LeaderBoard variables
	std::string lPath = SDL_GetBasePath();
	int highScores[10];
	std::string leaderboard;

	// Credits Variables
	std::string credits = "Sprites: Danny Lee Backgrounds/ Programming/ Design: Joshua Riches";

	// Game entities used during runtime
	Graphics* m_gGraphics;
	Pellet* pellets[119];
	PowerUp* powUps[6];
	SDL_Event m_sdlEvent;
	Player* player;
	Collision* collision;
	GUI* gui;
	Ghost* blinky;
	Ghost* inky;
	Ghost* pinky;
	Ghost* clyde;
	Vector2 scorePos = Vector2(280, 685);
	Vector2 timePos = Vector2(550, 640);
	Sprite* scoreText;
	Sprite* timeText;
	Vector2 playerPos;

	// Array of vectors for the positions of the pellets
	Vector2 pelletPos[119] = {
		// First row of pellets
		Vector2(60, 30), Vector2(100, 30), Vector2(140, 30), Vector2(180, 30), Vector2(220, 30), Vector2(250, 30), Vector2(310, 30), Vector2(340, 30), Vector2(380, 30),
		Vector2(420, 30), Vector2(460, 30), Vector2(500, 30), 
		// Second row of pellets
		Vector2(20, 75), Vector2(130, 75), Vector2(250, 75), Vector2(310, 75), Vector2(430, 75), Vector2(530, 75),
		// Third row of pellets
		Vector2(20, 110), Vector2(60, 110), Vector2(100, 110), Vector2(140, 110), Vector2(180, 110), Vector2(220, 110), Vector2(250, 110), Vector2(310, 110), Vector2(340, 110), Vector2(380, 110),
		Vector2(420, 110), Vector2(460, 110), Vector2(500, 110), Vector2(530, 110),
		// Fourth row of pellets
		Vector2(20, 160), Vector2(60, 160), Vector2(100, 160), Vector2(130, 160), Vector2(210, 160), Vector2(250, 160), Vector2(310, 160), Vector2(350, 160), Vector2(430, 160), Vector2(470, 160),
		Vector2(500, 160), Vector2(530, 160),
		// Fith row of pellets
		Vector2(130, 200), Vector2(250, 210), Vector2(310, 210), Vector2(430, 200),
		// Sixth row of pellets
		Vector2(130, 240), Vector2(210, 250), Vector2(250, 250), Vector2(310, 250), Vector2(350, 250), Vector2(430, 250),
		// Seventh row of pellets
		Vector2(130, 280), Vector2(430, 280),
		// Eighth row of pellets
		Vector2(20, 310), Vector2(60, 310), Vector2(100, 310), Vector2(170, 310), Vector2(210, 310), Vector2(350, 310), Vector2(390, 310), Vector2(460, 310),
		Vector2(500, 310), Vector2(540, 310), 
		// Ninth row of pellets
		Vector2(130, 340), Vector2(210, 340), Vector2(350, 340), Vector2(430, 340),
		// Tenth row of pellets
		Vector2(130, 380), Vector2(210, 380), Vector2(350, 380), Vector2(430, 380),
		// Eleventh row of pellets
		Vector2(130, 420), Vector2(210, 420), Vector2(350, 420), Vector2(430, 420),
		// Twelth row of pellets
		Vector2(60, 450), Vector2(100, 450), Vector2(140, 450), Vector2(180, 450), Vector2(220, 450), Vector2(250, 450), Vector2(310, 450), Vector2(340, 450), Vector2(380, 450),
		Vector2(420, 450), Vector2(460, 450), Vector2(500, 450),
		// Thirteenth row of pellets
		Vector2(20, 510), Vector2(70, 510), Vector2(130, 510), Vector2(170, 510), Vector2(210, 510), Vector2(250, 510), Vector2(310, 510), Vector2(350, 510), Vector2(390, 510), Vector2(430, 510),
		Vector2(490, 510), Vector2(530, 510),
		// Fourteenth row of pellets
		Vector2(70, 550), Vector2(130, 550), Vector2(190, 550), Vector2(370, 550), Vector2(430, 550), Vector2(490, 550),
		// Fifteenth row of pellets
		Vector2(80, 590), Vector2(120, 590), Vector2(160, 590), Vector2(200, 590), Vector2(240, 590), Vector2(280, 590), Vector2(320, 590), Vector2(360, 590), Vector2(400, 590), Vector2(440, 590),
		Vector2(480, 590)
	};

	// Array of vectors for the positions of the powerups
	Vector2 powUpsPos[6] = {
		Vector2(20, 30), Vector2(530, 30), Vector2(130, 310), Vector2(430, 310), Vector2(20, 450), Vector2(530, 450),
	};

	// Arrays of vectors for the routes that the different ghosts will follow
	Vector2 routeA[8] = {
		Vector2(40, 30),
		Vector2(160, 30),
		Vector2(260, 30),
		Vector2(260, 100),
		Vector2(260, 120),
		Vector2(140, 120),
		Vector2(140, 180),
		Vector2(40, 180)
	};

	Vector2 routeB[8] = {
		Vector2(550, 30),
		Vector2(320, 30),
		Vector2(320, 110),
		Vector2(320, 120),
		Vector2(400, 120),
		Vector2(440, 120),
		Vector2(440, 170),
		Vector2(550, 170)
	};

	Vector2 routeC[8] = {
		Vector2(200, 600),
		Vector2(200, 520),
		Vector2(260, 520),
		Vector2(260, 460),
		Vector2(40, 460),
		Vector2(40, 520),
		Vector2(80, 520),
		Vector2(80, 600)
	};

	Vector2 routeD[8] = {
		Vector2(380, 600),
		Vector2(380, 520),
		Vector2(320, 520),
		Vector2(320, 460),
		Vector2(540, 460),
		Vector2(540, 520),
		Vector2(500, 520),
		Vector2(500, 600)
	};

public:
	static GameManager* Instance();
	static void Release();

	void Initialise();
	void RenderElements();
	bool m_bQuit = false;

	void Run();
private:
	GameManager();
	~GameManager();
};

#endif // !_GAMEMANAGER_H_
