#pragma once
#include <SDL.h>
#include <iostream>
using std::cout;
using std::endl;
class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool GameIsRunning;
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

