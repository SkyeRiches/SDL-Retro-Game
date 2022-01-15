#include "Map.h"
#include <string>
#include <iostream>

/// <summary>
/// checks if there is an instance of the map and creates one if there isnt
/// </summary>
/// <returns></returns>
Map* Map::Instance()
{
    if (m_MInstance == NULL)
    {
        m_MInstance = new Map();
    }
    return m_MInstance;
}

/// <summary>
/// assigns the sprites to the values in the map array
/// </summary>
void Map::CreateMap()
{
    // Array that denotes a tile map
    // 29 tiles x 32 tiles

    // Use an embedded for loop to go through rows and columns 
    // and set the appropriate sprite

    Vector2 mapPos = Vector2(0, 0);

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 29; j++)
        {
            int spriteValue = mapRender[i][j];

            switch (spriteValue)
            {
            case 0:
                SetTile(cS, mapPos.x, mapPos.y, i, j);
                break;

            case 1:
                SetTile(topLT, mapPos.x, mapPos.y, i, j);
                break;

            case 2:
                SetTile(topS, mapPos.x, mapPos.y, i, j);
                break;

            case 3:
                SetTile(topRT, mapPos.x, mapPos.y, i, j);
                break;

            case 4:
                SetTile(lS, mapPos.x, mapPos.y, i, j);
                break;

            case 5:
                SetTile(cC, mapPos.x, mapPos.y, i, j);
                break;

            case 6:
                SetTile(rS, mapPos.x, mapPos.y, i, j);
                break;

            case 7:
                SetTile(botLT, mapPos.x, mapPos.y, i, j);
                break;

            case 8:
                SetTile(botS, mapPos.x, mapPos.y, i, j);
                break;

            case 9:
                SetTile(botRT, mapPos.x, mapPos.y, i, j);
                break;

            default:
                break;
            }

            mapPos.x += 20;
        }

        mapPos.x = 0;
        mapPos.y += 20;
    }
}

/// <summary>
/// Renders each tile of the map
/// </summary>
void Map::RenderMap()
{
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 29; j++)
        {
            sprites[i][j]->Render();
        }
    }
}

/// <summary>
/// Creates the new instance of the map
/// </summary>
Map::Map()
{
    // file paths for the map tiles
    topLT.append("Assets/TLT.png");
    topS.append("Assets/TS.png");
    topRT.append("Assets/TRT.png");
    lS.append("Assets/LS.png");
    cC.append("Assets/CC.png");
    rS.append("Assets/RS.png");
    botLT.append("Assets/BLT.png");
    botS.append("Assets/BS.png");
    botRT.append("Assets/BRT.png");
    cS.append("Assets/CS.png");
}

/// <summary>
/// creates a new sprite at the positon of the point in the map array, according to the value in the array
/// </summary>
void Map::SetTile(std::string path, int x, int y, int i, int j)
{
    Vector2 spritePos = Vector2(x, y);
    sprites[i][j] = new Sprite(path, spritePos, 20, 20, 0.0f);
    sprites[i][j]->TranslatePos(i - (0+i), j - (0+j));
    sprites[i][j]->Render();
}

/// <summary>
/// Destroys current instance of the map
/// </summary>
Map::~Map()
{
    delete m_MInstance;
    m_MInstance = NULL;
}