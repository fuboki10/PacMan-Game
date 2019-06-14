#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* ren)
{
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
	{
		throw SDL_Error;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,surf);
	if (!tex)
	{
		throw SDL_Error;
	}
	SDL_free(surf);
	return tex;
}


void TextureManager::Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dst, SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, text, &src, &dst);

}