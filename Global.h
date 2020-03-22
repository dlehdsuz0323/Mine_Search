#pragma once
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

enum GAME_OBJECT
{
	OPEN_BLOCK,
	CLOSED_BLOCK = 9,
	MINE = 10,
	FLAG,
	OBJECT,
	MAP,
	BLOCK,
	RESET,
	NONE,
};

enum LEVEL
{
	EASY,
	NOMAL,
	HARD
};

enum MOUSECLICK
{
	RIGHT_MOUSE_CLICK,
	LEFT_MOUSE_CLICK
};

enum BLOCKSTATE
{
	CLOSE,
	OPEN
};

enum PLAY_GAME
{
	GAME_PLAY,
	GAME_OVER,
	GAME_RESET,
	GAME_CLEAR
};