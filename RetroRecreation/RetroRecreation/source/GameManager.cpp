#include "..\include\GameManager.h"

/// <summary>
/// set instances of the game objects as null
/// </summary>
#pragma region NULLIFY_INSTANCES
GameManager* GameManager::m_sInstance = NULL;
Player* Player::m_PInstance = NULL;
Map* Map::m_MInstance = NULL;
Collision* Collision::m_CInstance = NULL;
GUI* GUI::m_guiInstance = NULL;
Splash* Splash::m_sInstance = NULL;
#pragma endregion

/// <summary>
/// Checks for instance of game manager and creates one if there isnt
/// </summary>
/// <returns></returns>
GameManager* GameManager::Instance()
{
    if (m_sInstance == NULL)
    {
        m_sInstance = new GameManager();
    }
    return m_sInstance;
}

/// <summary>
/// Remove the current instance of the game manager
/// </summary>
void GameManager::Release()
{
    delete m_sInstance;
    m_sInstance = NULL;

    Timer::Release();
}

/// <summary>
/// main game loop
/// </summary>
void GameManager::Run()
{
    // create the instance of the map
    Map* map = Map::Instance();
    map->CreateMap();

    // initialise all objects
    Initialise();

     m_gGraphics->ClearBackBuffer();

    while (!m_bQuit) // while the game still runs
    {
        switch (currentGameState)
        {
#pragma region SPLASH_STATE
            // splash screen game state
        case GameManager::SPLASH:

            m_tTimer->Update();

            while (SDL_PollEvent(&m_sdlEvent) != 0)
            {
                if (m_sdlEvent.type == SDL_QUIT)
                {
                    // if the player closes the window
                    m_bQuit = true;
                }
            }

            if (m_tTimer->DeltaTime() >= 1.0f / FRAME_RATE)
            {
                // play the animation for the splash screen and check the time passed
                m_gGraphics->ClearBackBuffer();
                splashScreen->PlayAnimation();
                m_gGraphics->Render();

                timePassed += m_tTimer->DeltaTime();
                if (timePassed >= 6)
                {
                    // after 6 seconds load the menu scene
                    timePassed = 0;
                    currentGameState = MENU;
                }

                m_tTimer->Reset();
            }

            break;
#pragma endregion

#pragma region MENU_STATE
            // main menu game state
        case GameManager::MENU:
            // render the menu
            m_gGraphics->ClearBackBuffer();
            menuBackground->Render();
            menuText->Render();
            m_gGraphics->Render();

            while (SDL_PollEvent(&m_sdlEvent) != 0)
            {
                if (m_sdlEvent.type == SDL_QUIT)
                {
                    // if they close the window
                    m_bQuit = true;
                }

                if (m_sdlEvent.type == SDL_KEYDOWN)
                {
                    switch (m_sdlEvent.key.keysym.sym)
                    {
                    case SDLK_1: // if they press '1'
                        // load the main game
                        currentGameState = PLAY;
                        m_tTimer->Reset();
                        break;

                    case SDLK_2: // if they press '2'
                        // rewrite the menu text to show the leaderboard and then load leaderboard state
                        leaderboard = std::to_string(highScores[0]) + " " + std::to_string(highScores[1]) + " " + std::to_string(highScores[2]) + " " +
                            std::to_string(highScores[3]) + " " + std::to_string(highScores[4]) + " " + std::to_string(highScores[5]) + " " +
                            std::to_string(highScores[6]) + " " + std::to_string(highScores[7]) + " " + std::to_string(highScores[8]) + " " + std::to_string(highScores[9]);

                        menuText->RedoText(std::string("").append(leaderboard).c_str(), "arial.ttf", 80);

                        currentGameState = LEADERBOARD;
                        break;

                    case SDLK_3: // if they press '3'
                        // rewrite menu text and load the credits state
                        menuText->RedoText(std::string("").append(credits).c_str(), "arial.ttf", 160);

                        currentGameState = CREDITS;
                        break;

                    case SDLK_4: // if they press '4'
                        // quit the game
                        m_bQuit = true;
                        break;
                    }
                }
            }

            break;
#pragma endregion

#pragma region PLAY_STATE
            // main game state
        case GameManager::PLAY:

            if (player->GetLives() <= 0)
            {
                // return to menu if the player has died
                currentGameState = MENU;
            }

            m_bQuit = player->GetQuit();

            // update the game objects, checking states and moving them
            m_tTimer->Update();
            playerPos = player->GetPosition();
            collision->CheckMapPos(playerPos, player);
            player->UpdatePacman();
            blinky->Move();
            inky->Move();
            pinky->Move();
            clyde->Move();
            blinky->SetScared(powerActivated);
            inky->SetScared(powerActivated);
            pinky->SetScared(powerActivated);
            clyde->SetScared(powerActivated);

            // check for player picking up the pellets and powerups
            for (int i = 0; i < 119; i++)
            {
                pellets[i]->PickupCheck(player);
            }
            for (int i = 0; i < 6; i++)
            {
                if (powUps[i]->PickupCheck(player))
                {
                    powerActivated = true;
                }
            }

            pacmanDied = false;

            // check for collisions with the ghosts and player
            if (clyde->PlayerColCheck(player))
            {
                pacmanDied = true;
                if (powerActivated)
                {
                    // if the player has a power upactive, kill the ghost instead
                    player->IncrementScore(200);
                    clyde->Reset();
                    clydeDied = true;
                }
            }
            if (pinky->PlayerColCheck(player))
            {
                pacmanDied = true;
                if (powerActivated)
                {
                    player->IncrementScore(200);
                    pinky->Reset();
                    pinkyDied = true;
                }
            }
            if (inky->PlayerColCheck(player))
            {
                pacmanDied = true;
                if (powerActivated)
                {
                    player->IncrementScore(200);
                    inky->Reset();
                    inkyDied = true;
                }
            }
            if (blinky->PlayerColCheck(player))
            {
                pacmanDied = true;
                if (powerActivated)
                {
                    player->IncrementScore(200);
                    blinky->Reset();
                    blinkyDied = true;
                }
            }

            if (pacmanDied && !powerActivated)
            {
                player->PacmanDeath(pacmanDied); // trigger the pacman death function upon a collision with the ghosts, if vulnerable
            }

            // if the ghosts have been killed, and theyve been dead a certain time, respawn them
            if (blinkyDied)
            {
                if (timePassed >= powerDuration)
                {
                    blinky->Respawn();
                    blinkyDied = false;
                }
            }
            if (inkyDied)
            {
                if (timePassed >= powerDuration)
                {
                    inky->Respawn();
                    inkyDied = false;
                }
            }
            if (pinkyDied)
            {
                if (timePassed >= powerDuration)
                {
                    pinky->Respawn();
                    pinkyDied = false;
                }
            }
            if (clydeDied)
            {
                if (timePassed >= powerDuration)
                {
                    clyde->Respawn();
                    clydeDied = false;
                }
            }

            if (m_tTimer->DeltaTime() >= 1.0f / FRAME_RATE)
            {
                // Render the game elements
                totalTime += m_tTimer->DeltaTime();
                m_gGraphics->ClearBackBuffer();
                map->RenderMap();
                RenderElements();

                // increment power duration if it is currently active
                if (powerActivated || timePassed >= 5)
                {
                    timePassed += m_tTimer->DeltaTime();
                }
                if (timePassed >= powerDuration)
                {
                    powerActivated = false;
                }
                if (timePassed >= 6)
                {
                    timePassed = 0;
                }

                m_tTimer->Reset();
            }
            break;
#pragma endregion

#pragma region LEADERBOARD_STATE
            // leaderboard state
        case GameManager::LEADERBOARD:
            // render the leaderboard
            m_gGraphics->ClearBackBuffer();
            menuBackground->Render();
            menuText->Render();
            m_gGraphics->Render();

            while (SDL_PollEvent(&m_sdlEvent) != 0)
            {
                if (m_sdlEvent.type == SDL_QUIT)
                {
                    // if they close the window, quit
                    m_bQuit = true;
                }

                if (m_sdlEvent.type == SDL_KEYDOWN)
                {
                    if (m_sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                    {
                        // if they press escape return to menu
                        menuText->RedoText(std::string("").append("1. PLAY 2.LEADERBOARD 3.CREDITS 4.QUIT").c_str(), "arial.ttf", 210);
                        currentGameState = MENU;
                    }
                }
            }
            break;
#pragma endregion

#pragma region CREDITS_STATE
            // credits state
        case GameManager::CREDITS:
            // render the credits
            m_gGraphics->ClearBackBuffer();
            menuBackground->Render();
            menuText->Render();
            m_gGraphics->Render();

            while (SDL_PollEvent(&m_sdlEvent) != 0)
            {
                if (m_sdlEvent.type == SDL_QUIT)
                {
                    // if they close the window, quit
                    m_bQuit = true;
                }

                if (m_sdlEvent.type == SDL_KEYDOWN)
                {
                    if (m_sdlEvent.key.keysym.sym == SDLK_ESCAPE)
                    {
                        // if they press escape return back to the menu state
                        menuText->RedoText(std::string("").append("1. PLAY 2.LEADERBOARD 3.CREDITS 4.QUIT").c_str(), "arial.ttf", 210);
                        currentGameState = MENU;
                    }
                }
            }
            break;
#pragma endregion

        default:
            break;
        }
          
    }
}

/// <summary>
/// Initialise all of the entities needed in the game
/// </summary>
void GameManager::Initialise()
{
    // Instances of the player related items
    player = Player::Instance();
    collision = Collision::Instance();
    gui = GUI::Instance();

    // creates the 4 ghosts for the game
    blinky = new Ghost("blinky.png", routeA[0], "Blinky", 1, routeA);
    inky = new Ghost("Inky.png", routeB[0], "Inky", 2, routeB);
    pinky = new Ghost("Pinky.png", routeC[0], "Pinky", 1, routeC);
    clyde = new Ghost("Clyde.png", routeD[0], "Clyde", 2, routeD);

    // creates the text needed in the game
    scoreText = new Sprite("1000", "BRLNSR.ttf", scorePos, 25.0f, 25.0f, 0.0f, 200);
    timeText = new Sprite("1000", "BRLNSR.ttf", timePos, 25.0f, 50.0f, 0.0f, 200);
    menuText = new Sprite("1.PLAY 2.LEADERBOARD 3.CREDITS 4.QUIT", "arial.ttf", menuPos, 300, 300, 0, 210);

    // creates an instance of the splash screen
    splashScreen = Splash::Instance();

    // creates the menu background
    std::string sPathA = SDL_GetBasePath();
    sPathA.append("Assets/Menu.png"); // Change to background image when its been made
    Vector2 tempPos = Vector2(0, 0);
    menuBackground = new Sprite(sPathA, tempPos, 580, 715, 0);

    // creates the pellets and power ups that appear in the maze
    for (int i = 0; i < 119; i++)
    {
        pellets[i] = new Pellet(pelletPos[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        powUps[i] = new PowerUp(powUpsPos[i]);
    }

    // reads the contents of the leaderboard file into a high score array
    lPath.append("Assets/Leaderboard.txt");
    std::ifstream leaderBoardTxt(lPath);
    for (int i = 0; i < 10; i++)
    {
        std::string line;
        std::getline(leaderBoardTxt, line);
        
        highScores[i] = std::stoi(line);
    }
}

/// <summary>
/// Renders all of the game objects in the main game loop
/// </summary>
void GameManager::RenderElements()
{
    // renders pellets and powerups
    for (int i = 0; i < 119; i++)
    {
        pellets[i]->RenderPellet();
    }
    for (int i = 0; i < 6; i++)
    {
        powUps[i]->RenderPowUp();
    }

    player->RenderPlayer();

    // render ghosts
    blinky->RenderGhost();
    inky->RenderGhost();
    pinky->RenderGhost();
    clyde->RenderGhost();

    // render the gui
    gui->RenderLives(player->GetLives());
    gui->RenderScore();
    gui->RenderTime();

    // rewrite and render all the gui text
    scoreText->RedoText(std::string("").append(std::to_string(player->GetScore())).c_str(), "BRLNSR.ttf", 200);
    timeText->RedoText(std::string("").append(std::to_string((int)totalTime)).c_str(), "BRLNSR.ttf", 200);
    scoreText->Render();
    timeText->Render();

    m_gGraphics->Render();
}

/// <summary>
/// Create a new instance of the game manager
/// </summary>
GameManager::GameManager()
{
    m_bQuit = false;
    m_gGraphics = Graphics::Instance();

    if (!Graphics::Initialised())
    {
        m_bQuit = true;
    }
    m_tTimer = Timer::Instance();
}

/// <summary>
/// Deconstructor for the game manager
/// </summary>
GameManager::~GameManager()
{
    Graphics::Release();
    m_gGraphics = NULL;
}
