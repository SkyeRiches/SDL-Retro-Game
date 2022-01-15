#include "GameManager.h"

/// <summary>
/// Main function of the game, sets the game into motion
/// </summary>
int main(int argc, char* argv[])
{
	GameManager* game = GameManager::Instance(); // create instance of the game manager

	game->Run(); // runs the game loop

	GameManager::Release(); // destroys instance of the game manager upon quitting
	game = NULL;


	return 0;
}