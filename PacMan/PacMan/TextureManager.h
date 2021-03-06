#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
	static void Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dst, SDL_Renderer* renderer);
	static void DrawWithAngle(SDL_Texture* text, SDL_Rect src, SDL_Rect dst, SDL_Renderer* renderer, const double angle, const SDL_Point* center, SDL_RendererFlip flip);
	static void DrawText(const char* fontPath, const char* Text, SDL_Rect dst, SDL_Renderer* renderer, int fontSize);
};

