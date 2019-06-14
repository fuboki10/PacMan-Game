#pragma once
#include "TextureManager.h"
#include "Utils.h"

class Player
{
	SDL_Texture* Player_Tex1, *Player_Tex2;
	int speed;
	int score;
	int xpos, ypos;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

public:
	Player(const char* fileName1, const char* fileName2, SDL_Renderer* renderer, int x = 0, int y = 0, int spd = 0);
	~Player(void);

	void Update(int map[20][25]);
	bool Move(int row, int col, int map[20][25]);
	void Clean();
	void Draw(SDL_Rect dst);
	void setScore(int sc);
	int getScore() const;

};

