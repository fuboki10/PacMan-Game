#include "Game.h"

bool Game::CanEat = false;

/*
           0       =====>        Nothing
		   1       =====>        Coin
		   2       =====>        Player
		   3       =====>        Monster
		   4      =====>        Obstacle
*/

int lvl1 [20][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0},
	{0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0},
	{0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0},
	{0,4,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,4,1,1,1,1,1,4,4,4,4,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,4,1,1,1,4,4,4,1,1,4,1,1,3,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,4,4,1,1,4,4,4,4,4,4,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,4,1,1,1,1,1,1,1,1,4,1,1,4,1,1,1,4,0},
	{0,4,1,1,1,1,1,4,1,1,1,1,4,1,1,1,1,1,1,4,1,1,1,4,0},
	{0,4,1,1,4,1,1,4,1,1,4,1,4,1,1,1,1,1,1,4,1,1,1,4,0},
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
				menu = new Menu("Assets/Images/StartMenu.png", "Assets/Images/GameOver.png", renderer, w, h, this); 

				if (!menu)
					throw SDL_Error;

				StartGame(false);

			}
		}
		if (TTF_Init() != 0){	
			throw SDL_Error;
			SDL_Quit();
		}
		
        //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
			throw SDL_Error;
			printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			SDL_Quit();
		}
		if(!LoadMedia())
		{
			throw SDL_Error;
		}

	}
}

bool Game::LoadMedia()
{
	bool success = true;

	//Load music
    gMusic = Mix_LoadMUS( "Assets/Sounds/pacman_beginning.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

	//Load Sound Effects
	gDeath = Mix_LoadWAV( "Assets/Sounds/pacman_death.wav" );
	if (gDeath == NULL)
	{
		printf( "Failed to load Death Sound Effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
	}

	return success;
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
			SDL_Delay(60);
		}

		SDL_Delay(60);
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
		map = new Map("Assets/Images/Background.png", "Assets/Images/Heart.png", renderer, Width, Height, this);
				
		if (!map)
			throw SDL_Error;

		map->LoadMap(lvl1);
		
		Mix_PlayMusic(gMusic, -1);
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

	//Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
	Mix_FreeChunk( gDeath );
	gDeath = NULL;
	
	Mix_Quit();
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
	Mix_PlayChannel(-1, gDeath, 0);
	Mix_PauseMusic();
	menu->GameOver(Score);
}

void Game::Ultimate(bool eat)
{
	CanEat = eat;
}