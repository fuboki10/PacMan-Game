#pragma once
#include "TextureManager.h"
#include "Player.h"
#include "Coin.h"
#include "Monster.h"
#include <list>

class Map
{
	SDL_Texture* MapTexture;
	SDL_Renderer *renderer;
	SDL_Rect srcRect, dstRect;

	int width, height;
	int map[20][25];

	Player *player;
	std::list<Monster*> monsters;
	std::list<Coin*> coins;

public:
	Map(const char* MapName, SDL_Renderer *renderer, int w, int h);
	~Map(void);
	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Update();
	void render();
	void Clean();
};

