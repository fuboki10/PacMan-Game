#pragma once

/*
 I N C L U D E S
*/
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
/* */

using std::cout;
using std::endl;

class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	

	bool GameIsRunning;
	const int FPS;
	int frameDelay;
	Uint32 frameStart;
	int frameTime;

public:
	Game(void);
	~Game(void);
	bool GameLoop();
	void init(const char* title, int xpos, int ypos, int w, int h, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return GameIsRunning; }
};

