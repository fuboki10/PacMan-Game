#pragma once
#include "TextureManager.h"
#include "Utils.h"

class Player
{
	SDL_Texture* Player_Tex1, *Player_Tex2, *Player_Tex3;
	SDL_Renderer* renderer;

	bool Ult;
	int speed;
	int lifes;
	int score;
	int xpos, ypos;
	double angle;
	SDL_RendererFlip flip;
	Moves Direction;
	SDL_Rect srcRect, destRect;

	int move;

public:
	Player(const char* fileName1, const char* fileName2, const char* fileName3, SDL_Renderer* renderer, int x = 0, int y = 0, int spd = 0, int lifes = 3);
	~Player(void);

	void setDirection(Moves Direction);
	void setLifes(int l);
	int getLifes();

	void Update(int map[20][25], Objects& object);
	bool Move(int row, int col, int map[20][25], Objects& object);
	void Clean();
	void Draw(SDL_Rect dst);
	void setScore(int sc);
	void Ultimate(bool f) {Ult = f;};
	int getScore() const;
	SDL_Point getPos() const;
};

