#pragma once

#include <Windows.h>
#include "Map.h"
#include "ResetButton.h"
#include "Block.h"

class BlockManager
{
private:

	static BlockManager* inst;

	vector <BitImage*> blockmanager;
	int MineNum	;


public:

	void Init(int iLevel, int MineXpos, int MineYPos, int iMineNum);
	void Draw(HDC hdc, int iLevel, int MineXpos, int MineYPos, HWND hWnd);	
	int Input(int MouseXPos, int MouseYPos, int MouseClick, int iGameState, int MineXPos, int MineYPos, int iMineNum);
	int RepeatOpen(int MouseXPos, int MouseYPos, int MineXPos, int MineYPos);
	int ClearGame(int MineXPos, int MineYPos, int MineNum, int &iGameState);
	int ClickedMine(int MineXpos, int MineYPos, int iMineNum, int &iGameState, int MouseXPos, int MouseYPos);
	int ClickedMouseLR_AroundNumber(int MouseXPos, int MouseYPos, int MapXPos, int MapYPos); 
	int ClickedAroundOpen(int MouseXPos, int MouseYPos, int MapXPos, int MapYPos, int &iGameState); 
	void GameOver(int MineXPos, int MineYPos, int &iGamestate);
	void Release(int MineXpos, int MineYPos);
	void Destroy();

	static BlockManager* GetInstance()
	{
		if (inst == nullptr)
			inst = new BlockManager();

		return inst;
	}

	BlockManager();
	~BlockManager();
};

