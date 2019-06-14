#include "Map.h"


Map::Map(const char* MapName, SDL_Renderer *renderer, int w, int h) : renderer(renderer)
{
	MapTexture = TextureManager::LoadTexture(MapName, renderer);
	width = w;
	height = h;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 2950;
	srcRect.h = 771;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.h = height;
	dstRect.w = width;

}


Map::~Map(void)
{
	Clean();
}
void Map::LoadMap(int arr[20][25])
{

	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			map[row][col] = arr[row][col];

			type = map[row][col];
			
			Coin* c;
			Monster* m;

			switch (type)
			{
			case 1 :
				c = new Coin("Asserts/Coin.png", renderer, row, col, 1);
				coins.push_back(c);
				break;
			case 2:
				player = new Player("Asserts/Pac1.png", "Asserts/Pac2.png", renderer, row , col); 
				break;
			case 3:
				m = new Monster("Asserts/Monster.png", renderer, row, col, 1);
				monsters.push_back(m);
				break;
			/*case -1:
				TextureManager::Draw(wall, src, dst, renderer);
				break;
			*/
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
	int type = 0;
	SDL_Rect dst;
	dst.h = 32;
	dst.w = 32;
	for (int row = 0; row < 20; row++)
	{
		for (int col = 0; col < 25; col++)
		{
			dst.y = row * 32;
			dst.x = col * 32;

			type = map[row][col];
			
			auto Coin_it = coins.begin();
			Coin* c;

			auto Monster_it = monsters.begin();
			Monster* m;

			switch (type)
			{
			case 1 :
				c = *Coin_it;
				c->Draw(dst);
				++Coin_it;
				break;
			case 2:
				player->Draw(dst);
				break;
			case 3:
				m = *Monster_it;
				m->Draw(dst);
				++Monster_it;
				break;
			/*case -1:
				TextureManager::Draw(wall, src, dst, renderer);
				break;*/
			default:
				break;
			}
			
		}
	}
}

void Map::Update()
{
	player->Update();
	for (auto monster : monsters)
	{
		monster->Update();
	}
}

void Map::render()
{
	DrawMap();
}

void Map::Clean()
{
	SDL_DestroyTexture(MapTexture);
	player->Clean();
	for (auto coin : coins)
	{
		coin ->Clean();
	}
	for (auto monster : monsters)
	{
		monster->Clean();
	}
}