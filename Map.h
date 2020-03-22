#pragma once
#include <Windows.h>
#include <vector>

#include "BitImageManager.h"
#include "Global.h"

using namespace std;

class Map
{
private:

	static Map* inst;

	int iMapXPos;
	int iMapYPos;
	int iMineNum;

	vector<int> VecMapCloseBlock;
	vector<BitImage*> GameBackGround;

public:

	void Init(int iLevel, int MineXpos, int MineYPos);
	void Draw(HDC hdc, int iLevel, int MineXpos, int MineYPos);
	void Destroy();



	static Map* GetInstance()
	{
		if (inst == nullptr)
			inst = new Map();

		return inst;
		}

	Map();
	~Map();
};

