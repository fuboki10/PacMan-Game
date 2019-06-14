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

bool Monster::Move(int row, int col, int map[20][25])
{
	if (map[row][col] == WALL || row >= 20 || row < 0 || col >= 25 || col < 0)
	{
		return 0;
	}
	if (map[row][col] == COIN || map[row][col] == MONSTER || map[row][col] == PLAYER)
	{
		return 0;
	}
	else if (map[row][col] == NOTHING)
	{
		map[row][col] = MONSTER;
		return 1;
	}


}

void Monster::Update(int map[20][25])
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
			
			if (this->Move(new_row, new_col, map)) 
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
			
			if (this->Move(new_row, new_col, map)) 
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
			
			if (this->Move(new_row, new_col, map)) 
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
			
			if (this->Move(new_row, new_col, map)) 
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
	SDL_DestroyTexture(Monster_Text);
	std::cout << "Monster Deleted .. \n";
}
	
void Monster::Draw(SDL_Rect dst)
{
	this->dst = dst;

	xpos = dst.x / 32;
	ypos = dst.y / 32;

	TextureManager::Draw(Monster_Text, src, dst, renderer);
}