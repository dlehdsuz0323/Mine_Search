#pragma once

#include <Windows.h>
#include <time.h>

#include "BitImageManager.h"
#include "Global.h"

class Block
{
private:

	static Block* inst;

	int iMapXPos;
	int iMapYPos;
	int MineNumCount;

	int **arrBlockState;
	int **arrObjectBlockState;

	int *arrBlockState2;
	int *arrObjectBlockState2;

	vector<BitImage*> GameBlock;
	TCHAR str[128];

public:

	void Init(int iLevel, int MineXPos, int MineYPos, int iMineNum);
	void InitPutMine(int iLevel, int MineXPos, int MineYPos, int iMineNum);
	//void InitPutMine(int iLevel, int MineXPos, int MineYPos, int iMineNum, int test);

	void Draw(HDC hdc, int iLevel, int MineXPos, int MineYPos);
	//void Draw(HDC hdc, int iLevel, int MineXPos, int MineYPos, int test);
	void DrawCloseBlock(HDC hdc, int iLevel, int MineXPos, int MineYPos);
	//void DrawCloseBlock(HDC hdc, int iLevel, int MineXPos, int MineYPos, int test);

	bool PutFlag(int MouseXPos, int MouseYPos);
	//bool PutFlag(int MouseXPos, int MouseYPos, int test);
	bool DrawingFlag(int MouseXPos, int MouseYPos);
	//bool DrawingFlag(int MouseXPos, int MouseYPos, int test);
	void NumberOfMine(HDC hdc, HWND hWnd);


	void SearchAroundMines(int MineXpos, int MineYPos);
	//void SearchAroundMines(int MineXpos, int MineYPos, int test);
	int OpenBlockState(int MineXPos, int MineYPos);
	int ReturnBlockState(int PosX, int PosY);
	int ReturnObjectState(int PosX, int PosY);

	void print(int MapWidth, int MapHigh);

	void Destroy();
	void Release(int MineXpos, int MineYPos);

	static Block* Getinstance()
	{
		if (inst == nullptr)
			inst = new Block();

		return inst;
	}

	Block();
	~Block();
};

