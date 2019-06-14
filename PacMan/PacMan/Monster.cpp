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

	dst.x = xpos;
	dst.y = ypos;
	dst.h = dst.w = 32;

	speed = spd;

}


Monster::~Monster(void)
{
	Clean();
}

bool Monster::Move(int row, int col, int map[20][25], Objects& object)
{
	if (map[row][col] == WALL || row >= 20 || row < 0 || col >= 25 || col < 0)
	{
		return 0;
	}
	if (map[row][col] == COIN || map[row][col] == MONSTER)
	{
		return 0;
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


void Monster::Update(int map[20][25], Objects& object)
{
	int row = ypos;
	int col = xpos;
	
	for (int i = Right; i < MOVES_NUM; i++)
	{
		int Move = rand() % MOVES_NUM;
		int new_row, new_col;
		if (Move == Right)
		{
			new_row = row;
			new_col = col + 1;
			
			if (this->Move(new_row, new_col, map, object)) 
			{
				xpos = new_col;
				ypos = new_row;

				map[row][col] = NOTHING;
				
				dst.x = xpos;
				dst.y = ypos;
				
				break;
			}

		}
		else if (Move == Left)
		{
			new_row = row;
			new_col = col - 1;
			
			if (this->Move(new_row, new_col, map, object)) 
			{
				xpos = new_col;
				ypos = new_row;

				map[row][col] = NOTHING;
				
				dst.x = xpos;
				dst.y = ypos;
				
				break;
			}
		}
		else if (Move == UP)
		{
			new_row = row - 1;
			new_col = col;
			
			if (this->Move(new_row, new_col, map, object)) 
			{
				xpos = new_col;
				ypos = new_row;

				map[row][col] = NOTHING;
				
				dst.x = xpos;
				dst.y = ypos;
				
				break;
			}
		}
		else if (Move == Down)
		{
			new_row = row + 1;
			new_col = col;
			
			if (this->Move(new_row, new_col, map, object)) 
			{
				xpos = new_col;
				ypos = new_row;

				map[row][col] = NOTHING;
				
				dst.x = xpos;
				dst.y = ypos;
				
				break;
			}
		}
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

	TextureManager::Draw(Monster_Text, src, dst, renderer);
}