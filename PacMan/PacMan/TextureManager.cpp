#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren)
{
	SDL_Surface* surf = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,surf);
	SDL_free(surf);
	return tex;
}
