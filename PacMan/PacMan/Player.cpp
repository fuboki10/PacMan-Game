#include "Player.h"
#include <iostream>

Player::Player(const char* fileName1, const char* fileName2, SDL_Renderer* renderer, int x, int y, int spd) : renderer(renderer)
{
	xpos = x;
	ypos = y;
	speed = 1;

	Player_Tex1 = TextureManager::LoadTexture(fileName1, renderer);
	if (Player_Tex1)
	{
		std::cout << "Player Texture 1 Created .. \n";
	}
	Player_Tex2 = TextureManager::LoadTexture(fileName2, renderer);
	if (Player_Tex2)
	{
		std::cout << "Player Texture 2 Created .. \n";
	}
}

void Player::Clean()
{
	SDL_DestroyTexture(Player_Tex1);
	SDL_DestroyTexture(Player_Tex2);
	std::cout << "Player Destroyed .. \n";
}

Player::~Player(void)
{
	Clean();
}

void Player::Draw(SDL_Rect dst)
{
	destRect = dst;
	
	xpos = dst.x;
	ypos = dst.y;

	TextureManager::Draw(Player_Tex1, srcRect, destRect, renderer);
}

void Player::Update(bool x, bool y)
{
	xpos+= x * speed;
	ypos+= y * speed;

	srcRect.h = 600;
	srcRect.w = 600;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = srcRect.h / 15;
	destRect.w = srcRect.w / 15;
	destRect.x = xpos;
	destRect.y = ypos;
}
	
void Player::render()
{
	TextureManager::Draw(Player_Tex1, srcRect, destRect, renderer);
}
