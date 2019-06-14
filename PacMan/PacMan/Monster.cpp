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
	if (map[row][col] == -1 || row >= 20 || row < 0 || col >= 25 || col < 0)
	{
		return 0;
	}
	if (map[row][col] == 1 || map[row][col] == 3 || map[row][col] == 2)
	{
		return 0;
	}
	else if (map[row][col] == 0)
	{
		map[row][col] = 3;
		return 1;
	}


}

void Monster::Update(int map[20][25])
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
				xpos = new_col * 32;
				ypos = new_row * 32;

				map[row][col] = 0;

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
				xpos = new_col * 32;
				ypos = new_row * 32;

				map[row][col] = 0;

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
				xpos = new_col * 32;
				ypos = new_row * 32;

				map[row][col] = 0;

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
	TextureManager::Draw(Monster_Text, src, dst, renderer);
}