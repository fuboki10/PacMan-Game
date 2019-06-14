#pragma once

/*
 I N C L U D E S
*/
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"
/* */

using std::cout;
using std::endl;

class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Map* map;

	bool GameIsRunning;
	const int FPS;
	int frameDelay;
	Uint32 frameStart;
	int frameTime;

	static bool CanEat;

public:
	
	static SDL_Event event;
	
	Game(void);
	~Game(void);
	bool GameLoop();
	void init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	static bool canEat();
	bool running() { return GameIsRunning; }
};

