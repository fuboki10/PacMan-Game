#pragma once
#include "TextureManager.h"
#include "Utils.h"

class Monster
{
	SDL_Texture* Monster_Text;
	SDL_Renderer* renderer;
	int speed;
	int xpos, ypos;
	SDL_Rect src, dst;

public:
	Monster(const char* fileName, SDL_Renderer* renderer, int x, int y, int spd);
	~Monster(void);

	void Update(int map[20][25]);
	void Clean();
	void Draw(SDL_Rect dst);
	bool Move(int row, int col, int map[20][25]);
};

