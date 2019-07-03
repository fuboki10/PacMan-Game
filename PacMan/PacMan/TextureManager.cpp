#include "TextureManager.h"
#include <iostream>

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

void TextureManager::DrawText(const char* fontPath, const char* Text, SDL_Rect dst, SDL_Renderer* renderer, int fontSize)
{
	int t_width = 0; // width of the loaded font-texture
	int t_height = 0; // height of the loaded font-texture
	SDL_Color text_color = {255,255,255};
	TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
	SDL_Texture* ftexture = NULL; // our font-texture

	// check to see that the font was loaded correctly
	if (font == NULL) {
		std::cerr << "Failed the load the font!\n";
		std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
	}
	else {
		// now create a surface from the font
		SDL_Surface* text_surface = TTF_RenderText_Solid(font, Text, text_color);

		// render the text surface
		if (text_surface == NULL) {
			std::cerr << "Failed to render text surface!\n";
			std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
		}
		else {
			// create a texture from the surface
			ftexture = SDL_CreateTextureFromSurface(renderer, text_surface);

			if (ftexture == NULL) {
				std::cerr << "Unable to create texture from rendered text!\n";
			}
			else {
				t_width = text_surface->w; // assign the width of the texture
				t_height = text_surface->h; // assign the height of the texture

				// clean up after ourselves (destroy the surface)
				SDL_FreeSurface(text_surface);
			}
		}
	}
	dst.w = t_width;
	dst.h = t_height;

	SDL_RenderCopy(renderer, ftexture, 0, &dst);
}