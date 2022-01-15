#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "GameEntity.h"
#include "Graphics.h"

class Sprite : public GameEntity
{
private:
	// Variables
	SDL_Texture* m_tTexture;
	Graphics* m_gGraphics;

public:
	// Constructors and Destructors
	Sprite(std::string a_sPath, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot);
	Sprite(const char* text, const char* font, Vector2& pos, float sizeX, float sizeY, float rot, int wrap);
	~Sprite();

	// Functions for the textures
	void RedoText(const char* text, const char* font, int wrap);
	virtual void Render();
};

#endif // !_TEXTURE_H_
