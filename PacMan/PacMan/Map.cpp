#include "Map.h"


Map::Map(const char* MapName, SDL_Renderer *renderer, int w, int h) : renderer(renderer)
{
	MapTexture = TextureManager::LoadTexture(MapName, renderer);
	width = w;
	height = h;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 2950;
	srcRect.h = 771;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.h = height;
	dstRect.w = width;
}


Map::~Map(void)
{
	Clean();
}

void Map::Update()
{
}

void Map::render()
{
	SDL_RenderCopy(renderer, MapTexture, &srcRect, &dstRect);
}

void Map::Clean()
{
	SDL_DestroyTexture(MapTexture);
}