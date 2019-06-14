#include "Coin.h"
#include <iostream>

Coin::Coin(const char* fileName, SDL_Renderer* renderer, int x, int y, int p) : renderer(renderer)
{
	Coin_Text = TextureManager::LoadTexture(fileName, renderer);
	
	xpos = x;
	ypos = y;
	points = p;
	
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	dst.x = xpos * 32;
	dst.y = ypos * 32;
	dst.h = 32;
	dst.w = 32;
}


Coin::~Coin(void)
{
	Clean();
}


void Coin::Draw(SDL_Rect dst)
{
	this->dst = dst;
	
	xpos = dst.x / 32;
	ypos = dst.y / 32;

	TextureManager::Draw(Coin_Text, src, dst, renderer);
}

void Coin::Clean()
{
	SDL_DestroyTexture(Coin_Text);
}

SDL_Point Coin::getPos() const
{
	SDL_Point P;
	
	P.x = xpos;
	P.y = ypos;
	
	return P;
}
