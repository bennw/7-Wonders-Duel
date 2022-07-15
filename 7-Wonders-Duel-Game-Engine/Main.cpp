#include "Game.h"
#include "GameStateStart.h"

int main()
{
	Game* game = new Game();

	game->pushState(new GameStateStart(game));
	game->gameLoop();

	delete game;
	return 0;
}