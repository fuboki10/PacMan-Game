#pragma once
#include "TextureManager.h"

class Map
{
	SDL_Texture* MapTexture;
	SDL_Renderer *renderer;
	SDL_Rect srcRect, dstRect;

	int width, height;

public:
	Map(const char* MapName, SDL_Renderer *renderer, int w, int h);
	~Map(void);
	void Update();
	void render();
	void Clean();
};

