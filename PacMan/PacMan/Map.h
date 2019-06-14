#pragma once
#include "TextureManager.h"
#include "Player.h"
#include "Coin.h"
#include "Monster.h"
#include "Wall.h"
#include<vector>
#include "Game.h"

class Game;

class Map
{
	SDL_Texture* MapTexture;
	SDL_Renderer *renderer;
	SDL_Rect srcRect, dstRect;
	Game* game;

	int width, height;
	int map[20][25];

	Player *player;
	std::vector<Monster*> monsters;
	std::vector<Coin*> coins;
	std::vector<Wall*> walls;

	int Search(const Objects& object, SDL_Point p);
	void GameOver();

public:
	Map(const char* MapName, SDL_Renderer *renderer, int w, int h, Game* game);
	~Map(void);
	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Update();
	void render();
	void Clean();
	void Delete(const Objects& object, const SDL_Point& p);
	void setPlayerMovement(Moves move);
};

