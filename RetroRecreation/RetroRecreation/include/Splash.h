#ifndef _SPLASH_H_
#define _SPLASH_H_
#include "Graphics.h"
#include "Timer.h"
#include "GameEntity.h"
#include "Texture.h"

class Splash
{
private:
	// Variables for the splash screen
	static Splash* m_sInstance;
	Timer* m_tTimer;
	float animTime = 0.0f;
	Vector2 vTranslation = Vector2(0, -3);
	bool isOpen = true;
	Sprite* background;
	Sprite* pacmanOpen;
	Sprite* pacmanClosed;
	Sprite* box;

	// File paths for the images
	std::string sPathA = SDL_GetBasePath();
	std::string sPathB = SDL_GetBasePath();
	std::string sPathC = SDL_GetBasePath();
	std::string sPathD = SDL_GetBasePath();

	// Constructor and destructor
	Splash();
	~Splash();

public:
	// Functions for the splash screen
	static Splash* Instance();
	void PlayAnimation();
};

#endif // !_SPLASH_H_

