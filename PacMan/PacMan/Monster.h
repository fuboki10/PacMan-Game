#pragma once
#include "TextureManager.h"
#include "Utils.h"

class Monster
{
	SDL_Texture* Monster_Text;
	SDL_Texture* Spirit_Text;
	SDL_Renderer* renderer;
	int speed;
	int xpos, ypos;
	SDL_Rect srcMonster, srcSpirit, dst;
	SDL_Point last_move;

public:
	Monster(const char* monsterFileName, const char* spiritFileName, SDL_Renderer* renderer, int x, int y, int spd);
	~Monster(void);

	SDL_Point getPos() const;
	void Update(int map[20][25], Objects& object, int SP[20][25]);
	void Clean();
	void Draw(SDL_Rect dst);
	int Move(int row, int col, int map[20][25], Objects& object);
};

