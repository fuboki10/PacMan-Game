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

void TextureManager::DrawWithAngle(SDL_Texture* text, SDL_Rect src, SDL_Rect dst, SDL_Renderer* renderer, const double angle, const SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, text, &src, &dst, angle, center, flip);
}

