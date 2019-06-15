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

	player = nullptr;
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
	CleanObjects();

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
				c = new Coin("Asserts/Coin.png", renderer, col, row, 1);
				coins.push_back(c);
				break;
			case PLAYER:
				player = new Player("Asserts/Pac1.png", "Asserts/Pac2.png", renderer, col , row, 1, 1); 
				break;
			case MONSTER:
				m = new Monster("Asserts/Monster.png", "Asserts/Spirit.png", renderer, col, row, 1);
				monsters.push_back(m);
				break;
			case WALL:
				w = new Wall("Asserts/Wall.png", renderer, col, row);
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
				if (player)
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

bool Map::valid(const SDL_Point& p) const
{
	if (p.y >= 20 || p.y < 0 || p.x >= 25 || p.x < 0)
	{
		return 0;
	}

	if (SP[p.y][p.x] != -1)
	{
		return 0;
	}

	if (map[p.y][p.x] == WALL)
	{
		return 0;
	}

	return 1;
}

void Map::BFS()
{
	std::queue<SDL_Point> q;
	SDL_Point p = player->getPos();

	q.push(p);
	SP[p.y][p.x] = 0;

	while (!q.empty())
	{
		SDL_Point cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			SDL_Point u;
			u.x = cur.x + dx[i];
			u.y = cur.y + dy[i];
			
			if (valid(u))
			{
				SP[u.y][u.x] = SP[cur.y][cur.x] + 1;
				q.push(u);
			}
		}
	}
}

void Map::Update()
{
	memset(SP, -1, sizeof SP);

	Objects object = NOTHING;

	if (player)
		player->Update(map, object);

	if (object != NOTHING)
	{
		if (player)
			Delete(object, player->getPos());
		if (!game->running())
			return;
	}

	// SP for Monsters AI
	BFS();

	for (auto monster : monsters)
	{
		object = NOTHING;
		if (monster)
			monster->Update(map, object, SP);
		if (object != NOTHING)
		{
			if (monster)
			{
				Delete(object, monster->getPos());
				break;
			}
		}
	}

	if (coins.size() == 0)
		game->Ultimate(1);
	if (monsters.size() == 0)
		GameOver();
}

void Map::render()
{
	DrawMap();
}

void Map::CleanObjects()
{
	if (player)
		delete player;
	player = NULL;

	for (auto coin : coins)
	{
		if (coin)
			delete coin;
		coin = NULL;
	}
	coins.clear();

	for (auto monster : monsters)
	{
		if (monster)
			delete monster;
		monster = NULL;
	}
	monsters.clear();

	for (auto wall : walls)
	{
		if (wall)
			delete wall;
		wall = NULL;
	}
	walls.clear();
}

void Map::Clean()
{
	SDL_DestroyTexture(MapTexture);
	
	CleanObjects();
}

void Map::GameOver()
{
	if (player->getLifes() == 1)
	{
		int score = player->getScore();
		game->GameOver(score);
	}
	else
	{
		player->setLifes(player->getLifes() - 1);
	}
}