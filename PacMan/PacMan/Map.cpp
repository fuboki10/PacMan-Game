#include "Map.h"
#include <iostream>

Map::Map(const char* MapName, SDL_Renderer *renderer, int w, int h, Game* game) : renderer(renderer), game(game)
{
	MapTexture = TextureManager::LoadTexture(MapName, renderer);
	width = w;
	height = h;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 1920;
	srcRect.h = 1080;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.h = height;
	dstRect.w = width;

}

void Map::setPlayerMovement(Moves move)
{
	player->setDirection(move);
}

Map::~Map(void)
{
	Clean();
}
void Map::LoadMap(int arr[20][25])
{

	Objects type = NOTHING;
	
	Coin* c;
	Monster* m;
	Wall* w;

	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			map[row][col] = arr[row][col];

			type = Objects(map[row][col]);

			switch (type)
			{
			case COIN:
				c = new Coin("Asserts/Coin.png", renderer, row, col, 1);
				coins.push_back(c);
				break;
			case PLAYER:
				player = new Player("Asserts/Pac1.png", "Asserts/Pac2.png", renderer, row , col, 1, 1); 
				break;
			case MONSTER:
				m = new Monster("Asserts/Monster.png", renderer, row, col, 1);
				monsters.push_back(m);
				break;
			case WALL:
				w = new Wall("Asserts/Wall.png", renderer, row, col);
				walls.push_back(w);
				break;
			default:
				break;
			}
		}
	}
}

/*
           0       =====>        Nothing
		   1       =====>        Coin
		   2       =====>        Player
		   3       =====>        Monster
		   -1      =====>        Obstacle
*/

void Map::DrawMap()
{

	//TextureManager::Draw(MapTexture, srcRect, dstRect, renderer);

	Objects type = NOTHING;
	SDL_Rect dst;
	dst.h = 32;
	dst.w = 32;
	int cIdx = 0;
	Coin* c;

	int mIdx = 0;
	Monster* m;

	int wIdx = 0;
	Wall* w;

	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			dst.y = row * 32;
			dst.x = col * 32;

			type = Objects(map[row][col]);

			switch (type)
			{
			case COIN :
				c = coins[cIdx];
				c->Draw(dst);
				++cIdx;
				break;
			case PLAYER:
				player->Draw(dst);
				break;
			case MONSTER:
				m = monsters[mIdx];
				m->Draw(dst);
				++mIdx;
				break;
			case WALL:
				w = walls[wIdx];
				w->Draw(dst);
				++wIdx;
				break;
			default:
				break;
			}
			
		}
	}
}

int Map::Search(const Objects& object, SDL_Point p)
{
	SDL_Point p2;
	if (object == COIN)
	{
		for (int i = 0; i < coins.size(); i++)
		{
			p2 = coins[i]->getPos();
			if (p2.x == p.x && p2.y == p.y)
			{
				return i;
			}
		}
	}

	if (object == MONSTER)
	{
		for (int i = 0; i < monsters.size(); i++)
		{
			p2 = monsters[i]->getPos();
			if (p2.x == p.x && p2.y == p.y)
			{
				player->setScore(player->getScore() + 5);
				return i;
			}
		}
	}
}

void Map::Delete(const Objects& object, const SDL_Point& p)
{
	int index = -1;

	Coin* c;
	Monster* m;


	switch (object)
	{
	case COIN:
		index = Search(object, p);
		c = coins[index];
		coins.erase(coins.begin() + index);
		delete c;
		break;
	case MONSTER:
		index = Search(object, p);
		m = monsters[index];
		monsters.erase(monsters.begin() + index);
		delete m;
		break;
	case PLAYER:
		GameOver();
		break;
	default:
		break;
	}
}

void Map::Update()
{
	Objects object = NOTHING;

	if (player)
		player->Update(map, object);

	if (object != NOTHING)
	{
		if (player)
			Delete(object, player->getPos());
	}

	for (auto monster : monsters)
	{
		if (monster)
			monster->Update(map);
	}

	if (player)
		std::cout << "Player Score : " << player->getScore() << std::endl;
}

void Map::render()
{
	DrawMap();
}

void Map::Clean()
{
	SDL_DestroyTexture(MapTexture);
	
	if (player)
		player->Clean();
	
	for (auto coin : coins)
	{
		if (coin)
			coin->Clean();
	}
	
	for (auto monster : monsters)
	{
		if (monster)
			monster->Clean();
	}
	
	for (auto wall : walls)
	{
		if (wall)
			wall->Clean();
	}
}

void Map::GameOver()
{
	if (player->getLifes() == 1)
	{
		int score = player->getScore();
		delete player;
		player = NULL;
		game->GameOver(score);
	}
	else
	{
		player->setLifes(player->getLifes() - 1);
	}
}