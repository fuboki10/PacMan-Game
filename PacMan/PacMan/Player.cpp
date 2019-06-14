#include "Player.h"
#include <iostream>
#include "Game.h"

Player::Player(const char* fileName1, const char* fileName2, SDL_Renderer* renderer, int x, int y, int spd, int lifes) : renderer(renderer)
{
	Direction = Stop; // stop
	angle = 0.0;
	flip = SDL_FLIP_NONE;

	xpos = x;
	ypos = y;
	speed = 1;
	score = 0;
	this->lifes = lifes;

	srcRect.x = srcRect.y = 0;
	srcRect.h = 600;
	srcRect.w = 541;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = destRect.w = 32;

	Player_Tex1 = TextureManager::LoadTexture(fileName1, renderer);
	Player_Tex2 = TextureManager::LoadTexture(fileName2, renderer);
}

void Player::Clean()
{
	SDL_DestroyTexture(Player_Tex1);
	SDL_DestroyTexture(Player_Tex2);
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

	TextureManager::DrawWithAngle(Player_Tex1, srcRect, destRect, renderer, angle, NULL, flip);
}

SDL_Point Player::getPos() const
{
	SDL_Point P;
	
	P.x = xpos;
	P.y = ypos;
	
	return P;
}

bool Player::Move(int row, int col, int map[20][25], Objects& object)
{
	if (map[row][col] == WALL || row >= 20 || row < 0 || col >= 25 || col < 0)
	{
		return 0;
	}
	// Coin
	if (map[row][col] == COIN)
	{
		score += 1;
		map[row][col] = PLAYER;
		object = COIN;
		return 1;
	}
	// monst
	if (map[row][col] == MONSTER)
	{
		if (Game::canEat())
		{
			object = MONSTER;
			std::cout << "Ate Monster ....\n";
		}
		else
		{
			object = PLAYER;
			std::cout << "Game Over ....\n";
		}
		map[row][col] = PLAYER;
		return 1;
	}

	map[row][col] = PLAYER;
	return 1;


}

void Player::Update(int map[20][25], Objects& object)
{
	int row = ypos;
	int col = xpos;	
	int new_row, new_col;

	if (Direction == Right)
	{
		new_row = row;
		new_col = col + 1;
			
		if (this->Move(new_row, new_col, map, object)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = NOTHING;

			destRect.x = xpos;
			destRect.y = ypos;

			angle = 0.0;
			flip = SDL_FLIP_NONE;
		}

	}
	if (Direction == Left)
	{
		new_row = row;
		new_col = col - 1;
			
		if (this->Move(new_row, new_col, map, object)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = NOTHING;

			destRect.x = xpos;
			destRect.y = ypos;

			angle = 0.0;
			flip = SDL_FLIP_HORIZONTAL;
		}
	}
	else if (Direction == UP)
	{
		new_row = row - 1;
		new_col = col;

		if (this->Move(new_row, new_col, map, object)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = NOTHING;

			destRect.x = xpos;
			destRect.y = ypos;

			angle = 270.0;
			flip = SDL_FLIP_NONE;
		}
	}
	else if (Direction == Down)
	{
		new_row = row + 1;
		new_col = col;

		if (this->Move(new_row, new_col, map, object)) 
		{
			xpos = new_col;
			ypos = new_row;

			map[row][col] = NOTHING;

			destRect.x = xpos;
			destRect.y = ypos;

			angle = 90.0;
			flip = SDL_FLIP_NONE;
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

void Player::setLifes(int l)
{
	lifes = l;
}
	
int Player::getLifes()
{
	return lifes;
}
