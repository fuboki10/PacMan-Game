#include "Game.h"

bool Game::CanEat = false;

int lvl1 [20][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,-1,-1,-1,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,-1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0},
	{0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Game::Game(void) : FPS(60)
{
	frameDelay = 1000/FPS;
	GameIsRunning = false;
	init("PacMan Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
}
void Game::init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Game initialized ...\n";
		window = SDL_CreateWindow(title, xpos, ypos, w, h, flags);
		
		if (window)
		{
			cout << "Window is running..\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer)
			{
				cout << "renderer created .. \n";
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				GameIsRunning = true;
				 
				// Create Objects 
				map = new Map("Asserts/Background.png", renderer, w, h);

				map->LoadMap(lvl1);
				map->DrawMap();

			}
		}
	}
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		GameIsRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	map->Update();
	SDL_Delay(500);
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// add stuff to render		
	map->render();
	

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	map->Clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned \n";
}

bool Game::GameLoop()
{
	while (running())
	{
		this->frameStart = SDL_GetTicks();
		
		render();
		handleEvents();
		update();
		

		this->frameTime = SDL_GetTicks() - this->frameStart;

		if (this->frameDelay > this->frameTime)
		{
			SDL_Delay(this->frameDelay - this->frameTime);
		}
	}
	clean();
	return 0;
}

bool Game::canEat()
{
	return CanEat;
}

Game::~Game(void)
{
	clean();
}
