#ifndef UTILS_H 
#define UTILS_H

const int dx[] = { 1,-1,0,0};
const int dy[] = { 0,0,-1,1};

enum Moves
{
	Right, // 0 
	Left,  // 1
	UP,    // 2
	Down,  // 3
	Stop,  // 4
	MOVES_NUM
};

enum Objects
{
	NOTHING, // 0
	COIN,    // 1
	PLAYER,  // 2
	MONSTER, // 3
	WALL,    // 4
	OBJECTS_NUM
};

enum MENU
{
	START,
	END,
	MENU_OPTIONS
};

#endif