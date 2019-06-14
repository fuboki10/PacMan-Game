#pragma once
#include "TextureManager.h"

class Coin
{
	SDL_Texture* Coin_Text;
	SDL_Renderer* renderer;
	SDL_Rect src, dst;

	int points;
	int xpos, ypos;
public:
	Coin(const char* fileName, SDL_Renderer* renderer, int x = 0, int y = 0, int p = 0);
	~Coin(void);

	void Draw(SDL_Rect dst);
	void Clean();
};

