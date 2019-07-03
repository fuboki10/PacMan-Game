#include "Menu.h"


Menu::Menu(const char* startFileName, const char* gameOverFileName, SDL_Renderer* renderer, int w, int h, Game* game) : 
	renderer(renderer), game(game), OptionsDiff(80)
{
	startMenu = TextureManager::LoadTexture(startFileName, renderer);
	gameOverMenu = TextureManager::LoadTexture(gameOverFileName, renderer);
	Square = TextureManager::LoadTexture("Asserts/Square.png", renderer);

	mode = START;
	option = Start;

	srcStart.x = srcStart.y = 0;
	srcStart.w = 800;
	srcStart.h = 600;

	srcEnd.x = srcEnd.y = 0;
	srcEnd.w = 1920;
	srcEnd.h = 1080;

	srcSquare.x = srcSquare.y = 0;
	srcSquare.w = 200;
	srcSquare.h = 64;

	dst.x = dst.y = 0;
	dst.w = w;
	dst.h = h;

	// 246 to 334 to 414
	// let it 80
	dstSquare.x = 302;
	dstSquare.y = 246;
	dstSquare.w = 200;
	dstSquare.h = 64;

	ScoreFontPath = "Asserts/04B_30__.TTF";
}


Menu::~Menu(void)
{
	Clean();
}

void Menu::GameOver(int Score)
{
	std::cout << "GameOver ... Your Score :  " << Score << '\n';

	CurrentScore = Score;

	mode = END;

	//SDL_Delay(3000); // i will change it later
}

void Menu::DrawScore()
{
	SDL_Rect ScoreDst = {180, 100, 200, 200};
	std::string Score = "Your Score : ";
	Score += std::to_string(CurrentScore);
	TextureManager::DrawText(ScoreFontPath, Score.c_str(), ScoreDst, renderer, 36);
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
		TextureManager::Draw(gameOverMenu, srcEnd, dst, renderer), DrawScore();
	if (Mode() == START)
	{
		TextureManager::Draw(startMenu, srcStart, dst, renderer);
		dstSquare.y = 246 + OptionsDiff * option;
		TextureManager::Draw(Square, srcSquare, dstSquare, renderer);
	}
}

void Menu::MoveSquare(bool mv)
{
	if (mv)
	{
		option = StartOptions((option + 1 + START_OPTIONS_NUM) % START_OPTIONS_NUM); 
	}
	else
	{
		option = StartOptions((option - 1 + START_OPTIONS_NUM) % START_OPTIONS_NUM); 
	}
}

void Menu::Enter()
{
	switch (option)
	{
	case Start:
		Play();
		break;
	case Options:
		break;
	case EXIT:
		Exit();
		break;
	default:
		break;
	}
}

void Menu::Clean()
{
	SDL_DestroyTexture(startMenu);
	SDL_DestroyTexture(gameOverMenu);
}
