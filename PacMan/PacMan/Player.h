#pragma once
#include "TextureManager.h"

class Player
{
	SDL_Texture* Player_Tex1, *Player_Tex2;
	int speed;
	int score;
	int xpos, ypos;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

public:
	Player(SDL_Renderer* renderer, int x = 0, int y = 0);
	~Player(void);

	void Update();
	void render();
	void Clean();

};

