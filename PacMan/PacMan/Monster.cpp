#include "Monster.h"
#include "Game.h"
#include <iostream>

Monster::Monster(const char* fileName, SDL_Renderer* renderer, int x, int y, int spd) : renderer(renderer)
{
	Monster_Text = TextureManager::LoadTexture(fileName, renderer);
	
	xpos = x;
	ypos = y;

	src.x = src.y = 0;
	src.h = src.w = 256;

	dst.x = xpos * 32;
	dst.y = ypos * 32;
	dst.h = dst.w = 32;

	speed = spd;

	last_move.x = -1;
	last_move.y = -1;

}


Monster::~Monster(void)
{
	Clean();
}

int Monster::Move(int row, int col, int map[20][25], Objects& object)
{
	if (map[row][col] == WALL || row >= 20 || row < 0 || col >= 25 || col < 0)
	{
		return 0;
	}
	if (map[row][col] == MONSTER)
	{
		return 0;
	}
	if (map[row][col] == COIN)
	{
		map[row][col] = MONSTER;
		return 2;
	}
	if (map[row][col] == PLAYER)
	{
		if (Game::canEat())
		{
			object = MONSTER;
		}
		else
		{
			object = PLAYER;
			map[row][col] = MONSTER;
		}
		return 1;
	}
	else if (map[row][col] == NOTHING)
	{
		map[row][col] = MONSTER;
		return 1;
	}


}

SDL_Point Monster::getPos() const
{
	SDL_Point P;
	
	P.x = xpos;
	P.y = ypos;
	
	return P;
}


void Monster::Update(int map[20][25], Objects& object, int SP[20][25])
{
	int col = xpos;
	int row = ypos;
	int new_row, new_col;

	SDL_Point min_p;
	int min = INT_MAX;

	for (int i = Right; i < Stop; i++)
	{
		new_col = col + dx[i];
		new_row = row + dy[i];

		if (min > SP[new_row][new_col] && SP[new_row][new_col] != -1)
		{
			min = SP[new_row][new_col];
			min_p.x = new_col;
			min_p.y = new_row;
		}
	}

	new_row = min_p.y;
	new_col = min_p.x;

	int mv = this->Move(new_row, new_col, map, object);
	if (mv) 
	{
		xpos = new_col;
		ypos = new_row;

		map[row][col] = NOTHING;
				
		if (last_move.x != -1 && last_move.y != -1)
		{
			map[last_move.y][last_move.x] = COIN;
			last_move.x = last_move.y = -1;
		}
		
		if (mv == 2)
		{
			last_move.x = new_col;
			last_move.y = new_row;
		}

		dst.x = xpos * 32;
		dst.y = ypos * 32;
				
	}
}
	
void Monster::Clean()
{
	if (Monster_Text)
		SDL_DestroyTexture(Monster_Text);
}
	
void Monster::Draw(SDL_Rect dst)
{
	this->dst = dst;

	xpos = dst.x / 32;
	ypos = dst.y / 32;

	TextureManager::Draw(Monster_Text, src, this->dst, renderer);
}