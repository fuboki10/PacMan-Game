#pragma once

/*
 I N C L U D E S
*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Map.h"
#include "Menu.h"
/* */
using std::cout;
using std::endl;

class Map;
class Menu;

class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Map* map;
	Menu* menu;
	SDL_Event event;

	Mix_Music* gMusic;
	Mix_Chunk* gDeath;

	int Width, Height;
	const int FPS;
	int frameDelay;
	Uint32 frameStart;
	int frameTime;

	bool GameIsRunning;  
	bool CloseTheGame;    // Close the Entire Game Menu
	static bool CanEat;

public:
	
	Game(int w = 800, int h = 600);
	~Game(void);
	void StartGame(bool s);
	bool GameLoop();
	void GameOver(int Score);
	void CloseGame(bool cg);
	void init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
	bool LoadMedia();
	
	void handleEvents();
	void update();
	void render();
	void clean();
	bool quit() const;
	static bool canEat();
	void Ultimate(bool eat);
	bool running() { return GameIsRunning; }
};

