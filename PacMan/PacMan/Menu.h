#pragma once
#include "TextureManager.h"
#include "Game.h"
#include <string>

enum StartOptions
{
	Start,
	Options,
	EXIT,
	START_OPTIONS_NUM
};

class Game;
class Menu
{
	SDL_Texture* startMenu;
	SDL_Texture* gameOverMenu;
	SDL_Texture* Square;
	SDL_Renderer* renderer;
	SDL_Rect srcEnd, srcStart, srcSquare, dstSquare, dst;
	Game* game;
		
	const char* ScoreFontPath;	
	int CurrentScore;
	const int OptionsDiff;
	StartOptions option; 
	MENU mode;

public:
	Menu(const char* startFileName, const char* gameOverFileName, SDL_Renderer* renderer, int w, int h, Game* game);
	~Menu(void);

	void MoveSquare(bool mv);
	void GameOver(int Score);
	void Play();
	void Exit();
	void Enter();
	void Clean();
	void render();
	MENU Mode() const;
	void Update();
	void DrawScore();
};

