#pragma once
#include "TextureManager.h"


class Wall
{
	SDL_Texture* Wall_Text;
	SDL_Renderer* renderer;
	int xpos, ypos;
	SDL_Rect src, dst;

public:
	Wall(const char* fileName, SDL_Renderer* renderer, int x = 0, int y = 0);
	~Wall(void);

	void Draw(SDL_Rect dst);
	void Clean();
};

