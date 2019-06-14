#pragma once
#include "TextureManager.h"
#include "Game.h"

class Game;
class Menu
{
	SDL_Texture* startMenu;
	SDL_Texture* gameOverMenu;
	SDL_Renderer* renderer;
	SDL_Rect src, dst;

public:
	Menu(const char* startFileName, const char* gameOverFileName, SDL_Renderer* renderer);
	~Menu(void);

	void GameOver(int Score);
	void Clean();
};

