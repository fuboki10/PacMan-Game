#pragma once
#include "TextureManager.h"

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

	void Update(bool x = false, bool y = false);
	void Clean();
	void Draw(SDL_Rect dst);
};

