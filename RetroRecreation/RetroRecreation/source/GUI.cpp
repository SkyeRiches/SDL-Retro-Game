#include "..\include\GameManager.h"

/// <summary>
/// checks for an instance of the GUI and creates one if there isnt
/// </summary>
/// <returns></returns>
GUI* GUI::Instance()
{
	if (m_guiInstance == NULL)
	{
		m_guiInstance = new GUI();
	}
	return m_guiInstance;
}

/// <summary>
/// Renders the icons that represent how many lives left
/// </summary>
/// <param name="lives"></param>
void GUI::RenderLives(int lives)
{
	if (lives > 0)
	{
		m_sLives1->Render();
	}
	if (lives > 1)
	{
		m_sLives2->Render();
	}
	if (lives > 2)
	{
		m_sLives3->Render();
	}
}

/// <summary>
/// Renders the players current score
/// </summary>
void GUI::RenderScore()
{
	m_sPickup->Render();
}

/// <summary>
/// Renders the time since the play scene was loaded
/// </summary>
void GUI::RenderTime()
{
	m_sClock->Render();
}

/// <summary>
/// Creates new instance of the GUI
/// </summary>
GUI::GUI()
{
	// File paths for the GUI images
	std::string sPathA = SDL_GetBasePath();
	std::string sPathB = SDL_GetBasePath();
	std::string sPathC = SDL_GetBasePath();
	std::string sPathD = SDL_GetBasePath();
	std::string sPathE = SDL_GetBasePath();
	sPathA.append("Assets/Pac_Man_Open.png");
	sPathB.append("Assets/Pac_Man_Open.png");
	sPathC.append("Assets/Pac_Man_Open.png");
	sPathD.append("Assets/Pickup.png");
	sPathE.append("Assets/Clock.png");

	Vector2 tempPos = Vector2(30, 650);
	Vector2 tempPos2 = Vector2(60, 650);
	Vector2 tempPos3 = Vector2(90, 650);
	Vector2 tempPos4 = Vector2(270, 650);

	// Creates the sprites for the GUI elements
	m_sLives1 = new Sprite(sPathA, tempPos, 40, 40, 180.0f);
	m_sLives2 = new Sprite(sPathB, tempPos2, 40, 40, 180.0f);
	m_sLives3 = new Sprite(sPathC, tempPos3, 40, 40, 180.0f);
	m_sPickup = new Sprite(sPathD, tempPos4, 40, 40, 0.0f);
	m_sClock = new Sprite(sPathE, timePos, 40, 40, 0);
}