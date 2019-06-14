#include "Wall.h"


Wall::Wall(const char* fileName, SDL_Renderer* renderer, int x, int y) : renderer(renderer)
{
	Wall_Text = TextureManager::LoadTexture(fileName, renderer);

	xpos = x;
	ypos = y;

	src.x = src.y = 0;
	src.h = src.w = 32;

	dst.x = xpos;
	dst.y = ypos;
	dst.h = dst.w = 32;

}


Wall::~Wall(void)
{
	Clean();
}



void Wall::Draw(SDL_Rect dst)
{
	this->dst = dst;
	xpos = dst.x;
	ypos = dst.y;

	TextureManager::Draw(Wall_Text, src, dst, renderer);
}
	
void Wall::Clean()
{
	SDL_DestroyTexture(Wall_Text);
}