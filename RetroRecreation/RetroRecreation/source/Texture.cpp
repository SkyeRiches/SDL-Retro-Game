#include "..\include\Texture.h"

/// <summary>
/// Creates a new sprite with the given parameters
/// </summary>
Sprite::Sprite(std::string a_sPath, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot)
{
	m_gGraphics = Graphics::Instance(); // Creates new instance of the graphics for the new sprite

	m_vPos = a_vPos;
	m_iWidth = a_iWidth;
	m_iHeight = a_iHeight;
	m_fRotation = a_fRot;

	// creates the sprite on screen
	m_tTexture = m_gGraphics->LoadSprite(a_sPath);
}

/// <summary>
/// Destroys the current instance of the sprite
/// </summary>
Sprite::~Sprite()
{
	SDL_DestroyTexture(m_tTexture);
	m_tTexture = NULL;
	m_gGraphics = NULL;
}

/// <summary>
/// Draws the sprite on scene
/// </summary>
void Sprite::Render()
{
	m_gGraphics->DrawSprite(m_tTexture, m_vPos, m_iWidth, m_iHeight, m_fRotation);
}

/// <summary>
/// Creates a new Text sprite. the wrap parameter is the point at which text will wrap over to the next line
/// </summary>
Sprite::Sprite(const char* text, const char* font, Vector2& pos, float sizeX, float sizeY, float rot, int wrap)
{
	m_gGraphics = Graphics::Instance();

	m_vPos = pos;
	m_iWidth = sizeX;
	m_iHeight = sizeY;
	m_fRotation = rot;

	m_tTexture = m_gGraphics->LoadText(text, font, wrap);
}

/// <summary>
/// rewrites the text in the text sprite
/// </summary>
void Sprite::RedoText(const char* text, const char* font, int wrap)
{
	m_tTexture = m_gGraphics->LoadText(text, font, wrap);
}
