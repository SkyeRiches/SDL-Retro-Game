#include "..\include\GameManager.h"

/// <summary>
/// if there is not already an instance of the player, this creates one
/// </summary>
/// <returns></returns>
Player* Player::Instance()
{
    if (m_PInstance == NULL)
    {
        m_PInstance = new Player();
    }
    return m_PInstance;
}

/// <summary>
/// gets the input from player and adjusts pacmans rotation and trajectory accordingly
/// </summary>
void Player::UpdatePacman()
{
    while (SDL_PollEvent(&m_sdlEvent) != 0)
    {

        if (m_sdlEvent.type == SDL_QUIT)
        {
            hasQuit = true;
        }

        if (m_sdlEvent.type == SDL_KEYDOWN)
        {
            switch (m_sdlEvent.key.keysym.sym)
            {
            case SDLK_w:
                if (canMoveU)
                {
                    vTranslation.y = 1;
                }
                else
                {
                    vTranslation.y = 0;
                }

                vTranslation.x = 0;
                m_sPacman->Rotation(90);

                break;
            case SDLK_a:
                if (canMoveL)
                {
                    vTranslation.x = -1;
                }
                else
                {
                    vTranslation.x = 0;
                }

                vTranslation.y = 0;
                m_sPacman->Rotation(0);

                break;
            case SDLK_s:
                if (canMoveD)
                {
                    vTranslation.y = -1;
                }
                else
                {
                    vTranslation.y = 0;
                }

                vTranslation.x = 0;
                m_sPacman->Rotation(270);

                break;
            case SDLK_d:
                if (canMoveR)
                {
                    vTranslation.x = 1;
                }
                else
                {
                    vTranslation.x = 0;
                }

                vTranslation.y = 0;
                m_sPacman->Rotation(180);

                break;

            default:
                break;
            }
        }
    }
}

/// <summary>
/// moves the player and draws them on screen
/// </summary>
void Player::RenderPlayer()
{
    m_sPacman->TranslatePos(vTranslation.x, vTranslation.y);
    m_sPacman2->TranslatePos(vTranslation.x, vTranslation.y);

    // alternates between open and closed pacman to create an animation
    if (animTime >= 0.25f)
    {
        isOpen = false;
        m_sPacman2->Render();
    }
    else
    {
        isOpen = true;
        m_sPacman->Render();
    }

    if (animTime >= 0.5f)
    {
        animTime = 0.0f;
    }

    animTime += m_tTimer->DeltaTime();
}

/// <summary>
/// determines if the player can move left
/// </summary>
/// <param name="canGoL"></param>
void Player::SetCanMoveLeft(bool canGoL)
{
    canMoveL = canGoL;
    if (!canMoveL && vTranslation.x == -1)
    {
        vTranslation.x = 0;
    }
}

/// <summary>
/// determines if the player can move up
/// </summary>
/// <param name="canGoU"></param>
void Player::SetCanMoveUp(bool canGoU)
{
    canMoveU = canGoU;
    if (!canMoveU && vTranslation.y == 1)
    {
        vTranslation.y = 0;
    }
}

/// <summary>
/// determines if the player can move down
/// </summary>
/// <param name="canGoD"></param>
void Player::SetCanMoveDown(bool canGoD)
{
    canMoveD = canGoD;
    if (!canMoveD && vTranslation.y == -1)
    {
        vTranslation.y = 0;
    }
}

/// <summary>
/// determines if the player can move right
/// </summary>
/// <param name="canGoR"></param>
void Player::SetCanMoveRight(bool canGoR)
{
    canMoveR = canGoR;
    if (!canMoveR && vTranslation.x == 1)
    {
        vTranslation.x = 0;
    }
}

/// <summary>
/// Returns the position of the player
/// </summary>
/// <returns></returns>
Vector2 Player::GetPosition()
{
    vPosition = m_sPacman->GetPos();
    vPosition2 = m_sPacman2->GetPos();
    
    if (isOpen)
    {
        return vPosition;
    }
    else
    {
        return vPosition2;
    }
}

/// <summary>
/// returns the position of the centre of the player rather then the top left corner
/// </summary>
/// <returns></returns>
Vector2 Player::CentrePos()
{
    Vector2 pos = GetPosition();
    float posX = pos.x + 12;
    float posY = pos.y + 12;
    return Vector2(posX, posY);
}

/// <summary>
/// Get the change in movement of the player
/// </summary>
/// <returns></returns>
Vector2 Player::GetTranslation()
{
    return vTranslation;
}

/// <summary>
/// returns if the player has opted to quit
/// </summary>
/// <returns></returns>
bool Player::GetQuit()
{
    return hasQuit;
}

/// <summary>
/// checks if pacman has died and deducts a life
/// if the player is at zero lives, it gets their score, 
/// and checks it against the leaderboard, and rewrites the leaderboard if they beat one of the scores
/// </summary>
/// <param name="hasDied"></param>
void Player::PacmanDeath(bool hasDied)
{
    if (hasDied)
    {
        m_sPacman->Pos(startPos);
        m_sPacman2->Pos(startPos);
        lives--;
    }

    if (lives <= 0)
    {
        std::ofstream leaderBoard(lPath);

        for (int i = 0; i < 10; i++)
        {
            if (score > highScores[i] && score < highScores[i - 1] && i != 0)
            {
                for (int j = 0; j < i; j++)
                {
                    highScores[9 - j] = highScores[9 - (j + 1)];
                }
                highScores[i] = score;
            }
            if (score > highScores[i] && i == 0)
            {
                for (int j = 9; j > i; j--)
                {
                    highScores[9 - (9 - j)] = highScores[9 - (9 - (j - 1))];
                }
                highScores[i] = score;
            }

            if (leaderBoard.is_open())
            {
                leaderBoard << highScores[i] << std::endl;
            }
        }
        leaderBoard.close();
    }
}

/// <summary>
/// returns the amount of lives the player has left
/// </summary>
/// <returns></returns>
int Player::GetLives()
{
    return lives;
}

/// <summary>
/// increases the players score by the given amount
/// </summary>
/// <param name="a_score"></param>
void Player::IncrementScore(int a_score)
{
    score += a_score;
}

/// <summary>
/// Returns the players current score
/// </summary>
/// <returns></returns>
int Player::GetScore()
{
    return score;
}

/// <summary>
/// constructor
/// Creates a new instance of the player
/// </summary>
Player::Player()
{
    // file paths for the images and the leaderboard
    std::string sPathA = SDL_GetBasePath();
    std::string sPathB = SDL_GetBasePath();
    lPath = SDL_GetBasePath();
    lPath.append("Assets/Leaderboard.txt");
    sPathA.append("Assets/Pac_Man_Open.png");
    sPathB.append("Assets/Pac_Man_Closed.png");

    // creates the player sprites using the images
    Vector2 vTempPos = Vector2(300, 370);
    m_sPacman = new Sprite(sPathA, vTempPos, 25, 25, 0.0f);
    m_sPacman2 = new Sprite(sPathB, vTempPos, 25, 25, 0.0f);

    m_tTimer = Timer::Instance(); // new instance of the timer, confined to this script

    // opens the leaderboard text file and writes each line to an element in the highscore array
    std::ifstream leaderBoardTxt(lPath);
    for (int i = 0; i < 10; i++)
    {
        std::string line;
        std::getline(leaderBoardTxt, line);
        highScores[i] = std::stoi(line);
    }
}

Player::~Player()
{
    delete m_sPacman;
    m_sPacman = NULL;
}