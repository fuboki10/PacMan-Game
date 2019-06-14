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
	Game* game;

	MENU mode;

public:
	Menu(const char* startFileName, const char* gameOverFileName, SDL_Renderer* renderer, int w, int h, Game* game);
	~Menu(void);

	void GameOver(int Score);
	void Play();
	void Exit();
	void Clean();
	void render();
	MENU Mode() const;
	void Update();
};

