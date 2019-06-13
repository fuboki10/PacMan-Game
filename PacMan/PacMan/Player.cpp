#include "Player.h"
#include <iostream>

Player::Player(SDL_Renderer* renderer, int x, int y) : renderer(renderer)
{
	xpos = x;
	ypos = y;

	Player_Tex1 = TextureManager::LoadTexture("Asserts/Pac1.png", renderer);
	if (Player_Tex1)
	{
		std::cout << "Player Texture 1 Created .. \n";
	}
	Player_Tex2 = TextureManager::LoadTexture("Asserts/Pac2.png", renderer);
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


void Player::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = srcRect.h * 2;
	destRect.w = srcRect.w * 2;
	destRect.x = xpos;
	destRect.y = ypos;
}
	
void Player::render()
{
	SDL_RenderCopy(renderer, Player_Tex1, &srcRect, &destRect);
}
