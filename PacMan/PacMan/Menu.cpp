#include "Menu.h"


Menu::Menu(const char* startFileName, const char* gameOverFileName, SDL_Renderer* renderer) : renderer(renderer)
{
	startMenu = TextureManager::LoadTexture(startFileName, renderer);
	gameOverMenu = TextureManager::LoadTexture(gameOverFileName, renderer);
}


Menu::~Menu(void)
{
	Clean();
}

void Menu::GameOver(int Score)
{
	TextureManager::Draw(gameOverMenu, src, dst, renderer);
}

void Menu::Clean()
{
	SDL_DestroyTexture(startMenu);
	SDL_DestroyTexture(gameOverMenu);
}
