#ifndef _GUI_H_
#define _GUI_H_
#include "Graphics.h"
#include "Timer.h"
#include "GameEntity.h"
#include "Texture.h"
#include <string>

class GUI
{
private:
	// GUI variables
	static GUI* m_guiInstance;
	Sprite* m_sLives1;
	Sprite* m_sLives2;
	Sprite* m_sLives3;
	Sprite* m_sPickup;
	Sprite* m_sClock;
	Vector2 timePos = Vector2(500, 650);

	// Constructor and destructor
	GUI();
	~GUI();

public:
	// GUI functions
	static GUI* Instance();
	void RenderLives(int lives);
	void RenderScore();
	void RenderTime();
};

#endif // !_GUI_H_
