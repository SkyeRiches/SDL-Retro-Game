#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "MathUtility.h"

class Graphics
{
public:
	// Window size
	static const int SCREEN_WIDTH = 580;
	static const int SCREEN_HEIGHT = 715;

private:
	// Variables for the graphics
	static Graphics* m_sInstance;
	static bool m_bInitialised;
	SDL_Window* m_wWindow;
	SDL_Surface* m_bBackBuffer;
	SDL_Renderer* m_rRenderer;

public:
	//\======================================================================
	// Methods
	//\======================================================================
	static Graphics* Instance();
	static void Release();
	static bool Initialised();

	void Render();

	SDL_Texture* LoadSprite(std::string a_sPath);

	SDL_Texture* LoadText(const char* text, const char* font, int wrap);

	void ClearBackBuffer();
	SDL_Surface* GetBackBuffer();

	void DrawSprite(SDL_Texture* a_tTexture, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot);

private:
	//\======================================================================
	// Constructors and deconstructors
	//\======================================================================
	Graphics();
	~Graphics();

	bool Init();
};

#endif // !_GRPAHICS_H_