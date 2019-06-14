#include "Monster.h"
#include <iostream>

Monster::Monster(const char* fileName, SDL_Renderer* renderer, int x, int y, int spd) : renderer(renderer)
{
	Monster_Text = TextureManager::LoadTexture(fileName, renderer);
	
	xpos = x;
	ypos = y;

	src.x = src.y = 0;
	src.h = src.w = 256;

	dst.x = xpos;
	dst.y = ypos;
	dst.h = dst.w = 32;

	speed = spd;

	std::cout << "Monster Created ..\n";
}


Monster::~Monster(void)
{
	Clean();
}


void Monster::Update(bool x, bool y)
{

}
	
void Monster::Clean()
{
	SDL_DestroyTexture(Monster_Text);
	std::cout << "Monster Deleted .. \n";
}
	
void Monster::Draw(SDL_Rect dst)
{
	TextureManager::Draw(Monster_Text, src, dst, renderer);
}