#include "Player.h"
#include <iostream>
#include "Game.h"

Player::Player(const char* fileName1, const char* fileName2, SDL_Renderer* renderer, int x, int y, int spd) : renderer(renderer)
{
	Direction = Stop; // Count means stop

	xpos = x;
	ypos = y;
	speed = 1;
	score = 0;

	srcRect.x = srcRect.y = 0;
	srcRect.h = 600;
	srcRect.w = 541;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = destRect.w = 32;

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
	
	xpos = dst.x / 32;
	ypos = dst.y / 32;

	TextureManager::Draw(Player_Tex1, srcRect, destRect, renderer);
}

bool Player::Move(int row, int col, int map[20][25])
{
	if (map[row][col] == -1 || row >= 20 || row < 0 || col >= 25 || col < 0)
	{
		return 0;
	}
	// Coin
	if (map[row][col] == 1)
	{
		score += 1;
		map[row][col] = 2;
		return 1;
	}
	// monst
	if (map[row][col] == 3)
	{
		if (Game::canEat())
		{
			std::cout << "Ate Monster ....\n";
			return 1;
		}
		return 0;
	}

	map[row][col] = 2;
	return 1;


}

void Player::Update(int map[20][25])
{
	int row = ypos;
	int col = xpos;	
	int new_row, new_col;

	if (Direction == Right)
	{
		new_row = row;
		new_col = col + 1;
			
		if (this->Move(new_row, new_col, map)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = 0;

			destRect.x = xpos;
			destRect.y = ypos;
		}

	}
	if (Direction == Left)
	{
		new_row = row;
		new_col = col - 1;
			
		if (this->Move(new_row, new_col, map)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = 0;

			destRect.x = xpos;
			destRect.y = ypos;
		}
	}
	else if (Direction == UP)
	{
		new_row = row - 1;
		new_col = col;

		if (this->Move(new_row, new_col, map)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = 0;

			destRect.x = xpos;
			destRect.y = ypos;
		}
	}
	else if (Direction == Down)
	{
		new_row = row + 1;
		new_col = col;

		if (this->Move(new_row, new_col, map)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = 0;

			destRect.x = xpos;
			destRect.y = ypos;
		}
	}
}

void Player::setDirection(Moves Direction)
{ 
	this->Direction = Direction;
}

void Player::setScore(int sc)
{
	score = sc;
}
	
int Player::getScore() const
{
	return score;
}

