#pragma once
#include "TextureManager.h"
#include "Utils.h"

class Player
{
	SDL_Texture* Player_Tex1, *Player_Tex2;
	SDL_Renderer* renderer;

	int speed;
	int lifes;
	int score;
	int xpos, ypos;
	double angle;
	SDL_RendererFlip flip;
	Moves Direction;
	SDL_Rect srcRect, destRect;

public:
	Player(const char* fileName1, const char* fileName2, SDL_Renderer* renderer, int x = 0, int y = 0, int spd = 0);
	~Player(void);

	void setDirection(Moves Direction);
	void setLifes(int l);
	int getLifes();

	void Update(int map[20][25]);
	bool Move(int row, int col, int map[20][25]);
	void Clean();
	void Draw(SDL_Rect dst);
	void setScore(int sc);
	int getScore() const;

};

