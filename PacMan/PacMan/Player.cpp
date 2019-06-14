#include "Player.h"
#include <iostream>

Player::Player(const char* fileName1, const char* fileName2, SDL_Renderer* renderer, int x, int y, int spd) : renderer(renderer)
{
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
	
	xpos = dst.x;
	ypos = dst.y;

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

	map[row][col] = 2;
	return 1;


}

void Player::Update(int map[20][25])
{
	int row = ypos / 32;
	int col = xpos / 32;
	
	for (int Move = Right; Move < Count; Move++)
	{
		int new_row, new_col;
		if (Move == Right)
		{
			new_row = row;
			new_col = col + 1;
			
			if (this->Move(new_row, new_col, map)) 
			{
				xpos = new_col * 32;
				ypos = new_row * 32;

				map[row][col] = 0;

				destRect.x = xpos;
				destRect.y = ypos;

				break;
			}

		}
		else if (Move == Left)
		{
			std::cout << " left \n";
			new_row = row;
			new_col = col - 1;
			if (this->Move(new_row, new_col, map)) 
			{
				xpos = new_col * 32;
				ypos = new_row * 32;

				map[row][col] = 0;

				destRect.x = xpos;
				destRect.y = ypos;

				break;
			}
		}
		else if (Move == UP)
		{
			new_row = row - 1;
			new_col = col;

			if (this->Move(new_row, new_col, map)) 
			{
				xpos = new_col * 32;
				ypos = new_row * 32;

				map[row][col] = 0;

				destRect.x = xpos;
				destRect.y = ypos;

				break;
			}
		}
		else if (Move == Down)
		{
			new_row = row + 1;
			new_col = col;

			if (this->Move(new_row, new_col, map)) 
			{
				xpos = new_col * 32;
				ypos = new_row * 32;

				map[row][col] = 0;

				destRect.x = xpos;
				destRect.y = ypos;

				break;
			}
		}
	}
}

void Player::setScore(int sc)
{
	score = sc;
}
	
int Player::getScore() const
{
	return score;
}

void Player::render()
{
	TextureManager::Draw(Player_Tex1, srcRect, destRect, renderer);
}
