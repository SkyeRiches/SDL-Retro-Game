#include "..\include\GameManager.h"

/// <summary>
/// Creates an instance of the splash screen if one does not already exist
/// </summary>
/// <returns></returns>
Splash* Splash::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new Splash();
	}
	return m_sInstance;
}

/// <summary>
/// Constructor for the splash screen
/// </summary>
Splash::Splash()
{
	// file paths for the images on the splash screen
	sPathA.append("Assets/Pac_Man_Open.png");
	sPathB.append("Assets/Pac_Man_Closed.png");
	sPathC.append("Assets/box.png");
	sPathD.append("Assets/Splash.png");

	// creates the images as sprites
	Vector2 tempPos = Vector2(0, 0);
	background = new Sprite(sPathD, tempPos, 580, 715, 0);
	tempPos = Vector2(0, -1450);
	box = new Sprite(sPathC, tempPos, 580, 1400, 0);
	tempPos = Vector2(220, -100);
	pacmanClosed = new Sprite(sPathB, tempPos, 125, 125, 270);
	pacmanOpen = new Sprite(sPathA, tempPos, 125, 125, 270);

	m_tTimer = Timer::Instance();
}

/// <summary>
/// Controls the animation on the splashscreen
/// </summary>
void Splash::PlayAnimation()
{
	// moves and renders the sprites
	background->Render();
	box->TranslatePos(vTranslation.x, vTranslation.y);
	box->Render();
	pacmanOpen->TranslatePos(vTranslation.x, vTranslation.y);
	pacmanClosed->TranslatePos(vTranslation.x, vTranslation.y);

	// alternates the version of pacman in order to create an animation of him chomping
	if (animTime >= 0.25f)
	{
		isOpen = false;
		pacmanClosed->Render();
	}
	else
	{
		isOpen = true;
		pacmanOpen->Render();
	}

	if (animTime >= 0.5f)
	{
		animTime = 0.0f;
	}

	animTime += m_tTimer->DeltaTime();
}

Splash::~Splash()
{

}
