#include "Game.h"

bool Game::CanEat = false;

int lvl1 [20][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0},
	{0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0},
	{0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,4,0},
	{0,4,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,4,1,1,1,1,1,4,4,4,4,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,4,1,1,1,4,4,4,1,1,4,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,4,4,1,1,4,4,4,4,4,4,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,4,1,1,1,1,4,1,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,4,1,1,4,1,1,4,3,4,1,1,1,1,1,1,4,1,3,1,4,0},
	{0,4,1,1,4,1,1,4,1,1,4,1,4,1,1,1,4,1,1,4,1,1,1,4,0},
	{0,4,1,1,4,4,4,4,4,4,4,1,4,1,1,1,4,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,2,1,1,1,1,1,1,1,1,1,1,4,1,4,4,4,1,1,4,0},
	{0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0},
	{0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Game::Game(int w, int h) : FPS(60)
{
	CloseTheGame = false;
	Width = w;
	Height = h;
	frameDelay = 1000/FPS;
	GameIsRunning = false;
	map = nullptr;
	menu = nullptr;
	init("PacMan Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, 0);
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
				
				// Create Menu 
				menu = new Menu("Asserts/StartMenu.png", "Asserts/GameOver.png", renderer, w, h, this); 

				if (!menu)
					throw SDL_Error;

				StartGame(false);

			}
		}
	}
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				/* Check the SDLKey values and move change the coords */
				if (GameIsRunning)
					switch( event.key.keysym.sym ){
						case SDLK_LEFT:
						case SDLK_a:
							map->setPlayerMovement(Left);
							break;
						case SDLK_RIGHT:
						case SDLK_d:
							map->setPlayerMovement(Right);
							break;
						case SDLK_UP:
						case SDLK_w:
							map->setPlayerMovement(UP);
							break;
						case SDLK_DOWN:
						case SDLK_s:
							map->setPlayerMovement(Down);
							break;
						default:
							break;
					}
				if (!GameIsRunning)
					switch( event.key.keysym.sym ){
						case SDLK_p:
							menu->Play();
							break;
						case SDLK_q:
							menu->Exit();
							break;
						case SDLK_UP:
						case SDLK_w:
							menu->MoveSquare(0);
							break;
						case SDLK_DOWN:
						case SDLK_s:
							menu->MoveSquare(1);
							break;
						case SDLK_KP_ENTER:
						case SDLK_RETURN:
							menu->Enter();
							break;
						default:
							break;
					}
				break;
			case SDL_QUIT :
				GameIsRunning = false;
				CloseTheGame = true;
				break;
			default:
				break;
		}
	}
}
void Game::CloseGame(bool cg)
{
	CloseTheGame = cg;

	if (CloseTheGame)
		GameIsRunning = false;

}
void Game::update()
{
	if (GameIsRunning)
	{
		map->Update();
		
		if (!CanEat)
		{
			SDL_Delay(125);
		}

		SDL_Delay(125);
	}
	else
	{
		if (map)
			delete map;
		map = NULL;

		menu->Update();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// add stuff to render		
	if (GameIsRunning)
		map->render();
	else
		menu->render();

	SDL_RenderPresent(renderer);
}
void Game::StartGame(bool s)
{
	GameIsRunning = s;

	if (GameIsRunning)
	{
		map = new Map("Asserts/Background.png", renderer, Width, Height, this);
				
		if (!map)
			throw SDL_Error;

		map->LoadMap(lvl1);
	}
}

void Game::clean()
{
	if (map)
		delete map;

	if (menu)
		delete menu;

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	IMG_Quit();
	SDL_Quit();
	cout << "Game Cleaned \n";
}
bool Game::quit() const
{
	return CloseTheGame;
}
bool Game::GameLoop()
{
	while (running() || !quit())
	{
		this->frameStart = SDL_GetTicks();
		
		handleEvents();
		update();
		render();

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

void Game::GameOver(int Score)
{
	GameIsRunning = false;
	menu->GameOver(Score);
	StartGame(false);
}

void Game::Ultimate(bool eat)
{
	CanEat = eat;
}