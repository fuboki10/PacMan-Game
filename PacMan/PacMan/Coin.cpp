#include "Coin.h"
#include <iostream>

Coin::Coin(const char* fileName, SDL_Renderer* renderer, int x, int y, int p) : renderer(renderer)
{
	Coin_Text = TextureManager::LoadTexture(fileName, renderer);
	std::cout << "Coin Created .. \n";
	xpos = x;
	ypos = y;
	points = p;
	
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	dst.x = xpos;
	dst.y = ypos;
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
	
	xpos = dst.x;
	ypos = dst.y;

	TextureManager::Draw(Coin_Text, src, dst, renderer);
}

void Coin::Clean()
{
	SDL_DestroyTexture(Coin_Text);
}