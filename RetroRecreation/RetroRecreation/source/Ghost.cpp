#include "..\include\GameManager.h"
#include <string>

/// <summary>
/// moves the ghost around its route around its area of the map
/// </summary>
void Ghost::Move()
{
    if (!deathState)
    {
        // if the position for the route isnt zero (shouldnt ever be false but its to catch out errors)
        if (vRoute[routePos].x != 0 && vRoute[routePos].y != 0)
        {
            if (vRoute[routePos].x < GhostPos().x) // if the next position if to the left
            {
                vTransform.x = -speed;
            }

            if (vRoute[routePos].x > GhostPos().x) // if the next position is to the right
            {
                vTransform.x = speed;
            }

            if (vRoute[routePos].y < GhostPos().y) // if the next position below the ghost
            {
                vTransform.y = speed;
            }

            if (vRoute[routePos].y > GhostPos().y) // if the next position is above the ghost
            {
                vTransform.y = -speed;
            }

            if (vRoute[routePos].y == GhostPos().y) // if the height is equal with the next position
            {
                vTransform.y = 0;
            }

            if (vRoute[routePos].x == GhostPos().x) // if the ghost is same x axis as the next position
            {
                vTransform.x = 0;
            }


            if (vRoute[routePos].x == GhostPos().x && vRoute[routePos].y == GhostPos().y) // if the ghost is in the same position as the next node, increment the position
            {
                routePos++;
            }
        }
        else
        {
            routePos = 0;
        }
    }
    else
    {
        // if in death state, go to the centre prison and wait
        vTransform = Vector2(0, 0);
        Vector2 tempPos = Vector2(270, 300);
        m_sGhost->Pos(tempPos);
        m_sScared->Pos(tempPos);
    }
}

/// <summary>
/// Returns the ghost back to its original position and resets the route for it
/// </summary>
void Ghost::Respawn()
{
    m_sGhost->Pos(vStartPos);
    m_sScared->Pos(vStartPos);
    routePos = 0;
    Reset();
}

/// <summary>
/// Resets the ghosts death state
/// </summary>
void Ghost::Reset()
{
    deathState = !deathState;
}

/// <summary>
/// sets whether the ghost is in its scared (killable) state or not
/// </summary>
/// <param name="isScared"></param>
void Ghost::SetScared(bool isScared)
{
    scaredState = isScared;
}

/// <summary>
/// Draws the ghost on screen
/// </summary>
void Ghost::RenderGhost()
{
    m_sGhost->TranslatePos(vTransform.x, vTransform.y);
    m_sScared->TranslatePos(vTransform.x, vTransform.y);

    if (scaredState)
    {
        m_sScared->Render();
    }
    if (!scaredState)
    {
        m_sGhost->Render();
    }
}

/// <summary>
/// Returns the position of the centre of the ghost
/// </summary>
Vector2 Ghost::GhostPos()
{
    // 25x25
    Vector2 pos = m_sGhost->GetPos();
    float posX = pos.x + 12;
    float posY = pos.y + 12;
    return Vector2(posX, posY);
}

/// <summary>
/// Checks if the player is colliding with the ghost
/// </summary>
bool Ghost::PlayerColCheck(Player* player)
{
    Vector2 vGhostToPlayer = GhostToPlayer(player); // Gets the vector between the player and the ghost
    float ghostVectorsqr = Pythag(vGhostToPlayer);  // Gets the hypotenuse of the vector between them
    float ghostRadSqrd = 13 * 13;                   // Square of the radius of the ghost
    if (ghostVectorsqr <= ghostRadSqrd)             // if the distance between them is less than the radius squared
    {
        return true;
    }

    return false;
}

/// <summary>
/// Returns the vector for the distance between the ghost and player
/// </summary>
Vector2 Ghost::GhostToPlayer(Player* player)
{
    Vector2 v2A = player->CentrePos();
    Vector2 v2B = GhostPos();
    Vector2 v2C = v2B - v2A;
    return v2C;
}

/// <summary>
/// Gets the hypotenuse of the vector between the ghost and player
/// </summary>
/// <param name="a_vec"></param>
/// <returns></returns>
float Ghost::Pythag(Vector2 a_vec)
{
    float xSqr = a_vec.x * a_vec.x;
    float ySqr = a_vec.y * a_vec.y;
    return (xSqr + ySqr);
}

/// <summary>
/// creates a new instance of the ghost
/// </summary>
Ghost::Ghost(std::string a_path, Vector2 a_startpos, std::string a_name, float a_speed, Vector2 a_route[8]) :
    vStartPos(a_startpos), name(a_name), speed(a_speed)
{
    // the path the ghost will follow
    for (int i = 0; i < 8; i++)
    {
        vRoute[i] = a_route[i];
    }

    // path for the ghost sprites
    std::string sPathA = SDL_GetBasePath();
    std::string sPathB = SDL_GetBasePath();
    sPathA.append("Assets/" + a_path);
    sPathB.append("Assets/Ghost_Dead.png");
    // creates new sprites for the images
    m_sGhost = new Sprite(sPathA, vStartPos, 25, 25, 0.0f);
    m_sScared = new Sprite(sPathB, vStartPos, 25, 25, 0.0f);
}

/// <summary>
/// Destructor
/// </summary>
Ghost::~Ghost()
{
    delete this;
}

