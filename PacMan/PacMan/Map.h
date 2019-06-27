#pragma once
#include "TextureManager.h"
#include "Player.h"
#include "Coin.h"
#include "Monster.h"
#include "Wall.h"
#include <vector>
#include <queue>
#include "Game.h"

class Game;

class Map
{
	SDL_Texture* MapTexture, *HeartText;
	SDL_Renderer *renderer;
	SDL_Rect srcRect, dstRect, srcHeartRect;
	Game* game;

	int width, height;
	int map[20][25];

	Player *player;
	std::vector<Monster*> monsters;
	std::vector<Coin*> coins;
	std::vector<Wall*> walls;

	int Search(const Objects& object, SDL_Point p);
	void GameOver();
	void CleanObjects();

	/* SP for Monsters AI */
	
	int SP[20][25];
	void BFS();
	bool valid(const SDL_Point& p) const;
	
	////////////////////////

public:
	
	Map(const char* MapName, const char* HeartName, SDL_Renderer *renderer, int w, int h, Game* game);
	~Map(void);
	void LoadMap(int arr[20][25]);
	void DrawMap();
	void Update();
	void render();
	void Clean();
	void Delete(const Objects& object, const SDL_Point& p);
	void setPlayerMovement(Moves move);
};

