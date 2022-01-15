#include "Graphics.h"

Graphics* Graphics::m_sInstance = NULL;
bool Graphics::m_bInitialised = false;

/// <summary>
/// Checks for instance of graphics and creates one if there isnt
/// </summary>
/// <returns></returns>
Graphics* Graphics::Instance()
{
    if (m_sInstance == NULL)
    {
        m_sInstance = new Graphics();
    }
    return m_sInstance;
}

/// <summary>
/// delets the instance of graphics
/// </summary>
void Graphics::Release()
{
    delete m_sInstance;
    m_sInstance = NULL;
    m_bInitialised = false;
}

/// <summary>
/// returns if the graphics have been initialised
/// </summary>
/// <returns></returns>
bool Graphics::Initialised()
{
    return m_bInitialised;
}

/// <summary>
/// Renders the graphics
/// </summary>
void Graphics::Render()
{
    SDL_RenderPresent(m_rRenderer);
}

/// <summary>
/// loads the sprite of the sprite that has called this function
/// </summary>
SDL_Texture* Graphics::LoadSprite(std::string a_sPath)
{
    SDL_Texture* tTexture = NULL;

    SDL_Surface* sSurface = IMG_Load(a_sPath.c_str());
    if (sSurface == NULL)
    {
        printf("Image Load Error: Path(%s), Error(%s\n", a_sPath.c_str(), IMG_GetError());

        return tTexture;
    }

    tTexture = SDL_CreateTextureFromSurface(m_rRenderer, sSurface);
    if (tTexture == NULL)
    {
        printf("Texture Create Error: %s\n", IMG_GetError());
    }

    SDL_FreeSurface(sSurface);
    return tTexture;
}

/// <summary>
/// removes all images that have been displayed
/// </summary>
void Graphics::ClearBackBuffer()
{
    SDL_RenderClear(m_rRenderer);
}

/// <summary>
/// draws the sprite on screen ad the given position
/// </summary>
void Graphics::DrawSprite(SDL_Texture* a_tTexture, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot)
{
    SDL_Rect renderQuad = { a_vPos.x, a_vPos.y, a_iWidth, a_iHeight };
    SDL_RendererFlip rFlip = SDL_FLIP_NONE;

    SDL_RenderCopyEx(m_rRenderer, a_tTexture, NULL, &renderQuad, a_fRot, NULL, rFlip);
}

/// <summary>
/// constructor
/// </summary>
Graphics::Graphics() 
{
    m_bBackBuffer = NULL;
    m_bInitialised = Init();
}

/// <summary>
/// Destructor
/// </summary>
Graphics::~Graphics()
{
    SDL_DestroyWindow(m_wWindow);
    m_wWindow = NULL;

    SDL_DestroyRenderer(m_rRenderer);
    m_rRenderer = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

/// <summary>
/// Initialises the graphics instance
/// </summary>
/// <returns></returns>
bool Graphics::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Initialisation Error: %s\n", SDL_GetError());
        return false;
    }
    if (TTF_Init() < 0)
    {
        printf("Initialisation Error: %\n", SDL_GetError());
        return false;
    }
    m_wWindow = SDL_CreateWindow("Retro Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (m_wWindow == NULL)
    {
        printf("Window Creation Error: %s\n", SDL_GetError());
        return false;
    }

    m_rRenderer = SDL_CreateRenderer(m_wWindow, -1, SDL_RENDERER_ACCELERATED);
    if (m_rRenderer == NULL)
    {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(m_rRenderer, 0x00, 0x00, 0x00, 0x00);

    int iFlag = IMG_INIT_PNG;
    if (!(IMG_Init(iFlag) & iFlag))
    {
        printf("Image Initialisation Error: %s\n", IMG_GetError());
        return false;
    }

    m_bBackBuffer = SDL_GetWindowSurface(m_wWindow);
    return true;
}

/// <summary>
/// returns the buffer that the images are being displayed on
/// </summary>
/// <returns></returns>
SDL_Surface* Graphics::GetBackBuffer()
{
    return m_bBackBuffer;
}

/// <summary>
/// loads the text sprite that called this
/// </summary>
SDL_Texture* Graphics::LoadText(const char* text, const char* font, int wrap)
{
    SDL_Texture* texture = NULL;
    TTF_Font* textFont = TTF_OpenFont(std::string(SDL_GetBasePath()).append(font).c_str(), 25); // gets the font to use for the text
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(textFont, text, textColor, wrap);

    if (surface == NULL)
    {
        printf("Text load error: (%s)\n", text);
        return texture;
    }

    texture = SDL_CreateTextureFromSurface(m_rRenderer, surface);
    if (texture == NULL)
    {
        printf("Text Create Error: %s\n", IMG_GetError());
    }
    SDL_FreeSurface(surface);
    return texture;
}
