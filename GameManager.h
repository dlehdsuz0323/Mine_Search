#pragma once
#include <Windows.h>
#include "Global.h"

#include "BlockManager.h"
#include "Map.h"

class GameManager
{
private:


	static GameManager* inst;
	POINT MousePos;

	int	iPlayerTurn;
	int	Level;

	int	iMineNum;
	int	iMineXPos;
	int	iMineYPos;

	RECT cRect = { 0, 0, 870, 512 };

public:

	void Init(HDC hdc, int iLevel, int &GameState);
	void Draw(HDC hdc, HWND hWnd);
	
	void Release(void);
	void Input(int MouseXPos, int MouseYPos, HWND hWnd, int RMouseClick, int LMouseClick , bool RMouseButton, bool LMouseButton, int &GameState, int &iTimeSec, int &iTimeStart);
	void ClickedAtOnce(bool &RMouseButton, bool &LMouseButton, int MouseXPos, int MouseYPos, int &GameState);
	void Destroy();

	static GameManager* GetInstance()
	{
		if (inst == nullptr)
			inst = new GameManager();

		return inst;
	}
	GameManager();
	~GameManager();
};

