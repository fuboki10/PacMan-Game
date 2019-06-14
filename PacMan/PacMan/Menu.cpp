#include "Menu.h"


Menu::Menu(const char* startFileName, const char* gameOverFileName, SDL_Renderer* renderer, int w, int h, Game* game) : renderer(renderer), game(game)
{
	startMenu = TextureManager::LoadTexture(startFileName, renderer);
	gameOverMenu = TextureManager::LoadTexture(gameOverFileName, renderer);

	mode = START;

	src.x = src.y = 0;
	src.w = 1920;
	src.h = 1080;

	dst.x = dst.y = 0;
	dst.w = w;
	dst.h = h;
}


Menu::~Menu(void)
{
	Clean();
}

void Menu::GameOver(int Score)
{
	std::cout << "GameOver ... Your Score :  " << Score << '\n';

	mode = END;

	//SDL_Delay(3000); // i will change it later
}

void Menu::Update()
{

}

MENU Menu::Mode() const
{
	return this->mode;
}

void Menu::Exit()
{
	game->CloseGame(true);
}

void Menu::Play()
{
	game->StartGame(true);
}

void Menu::render()
{
	if (Mode() == END)
		TextureManager::Draw(gameOverMenu, src, dst, renderer);
}

void Menu::Clean()
{
	SDL_DestroyTexture(startMenu);
	SDL_DestroyTexture(gameOverMenu);
}
