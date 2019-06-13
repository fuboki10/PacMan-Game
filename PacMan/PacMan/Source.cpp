#include "Game.h"

Game *game = nullptr;

int main(int args, char** argv)
{
	game = new Game();

	if (!game->GameLoop())
	{
		return 0;
	}
}