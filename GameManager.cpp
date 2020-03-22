#include "GameManager.h"
#include "BitImageManager.h"

GameManager* GameManager::inst = nullptr;


// 더블포인터 1차원 배열로 변환하기

void GameManager::Init(HDC hdc, int iLevel, int &GameState)
{
	switch (iLevel)
	{
	case EASY:
		iMineXPos = 9;
		iMineYPos = 9;
		iMineNum = 10;

		break;

	case NOMAL:
		iMineXPos = 16;
		iMineYPos = 16;
		iMineNum = 40;
		break;

	case HARD:
		iMineXPos = 30;
		iMineYPos = 16;
		iMineNum = 50;
	}

	GameState = GAME_PLAY;
	Level = iLevel;
	system("cls");

	BitImageManager::GetInstance()->Init(hdc);
	Map::GetInstance()->Init(iLevel, iMineXPos, iMineYPos);
	BlockManager::GetInstance()->Init( Level, iMineXPos, iMineYPos, iMineNum);

	Block::Getinstance()->print(iMineXPos,iMineYPos);
}

void GameManager::Draw(HDC hdc, HWND hWnd)
{	
	Map::GetInstance()->Draw(hdc, Level, iMineXPos, iMineYPos);
	BlockManager::GetInstance()->Draw(hdc, Level, iMineXPos, iMineYPos, hWnd);
}

void GameManager::Input(int MouseXPos, int MouseYPos, HWND hWnd, int RMouseClick, int LMouseClick, bool RMouseButton, bool LMouseButton, int &GameState, int &iTimeSec, int &iTimeStart)
{
	MousePos.x = MouseXPos;
	MousePos.y = MouseYPos;

	if (GameState == GAME_PLAY)	
	{
		if (MouseXPos > 42 && MouseYPos > 45 && MouseXPos < 820 && MouseYPos < 460)
		{
			MousePos.x = (MouseXPos - 42) / 26;
			MousePos.y = (MouseYPos - 45) / 26;

			if (GameState == GAME_PLAY)
			{
				if (LMouseClick == LEFT_MOUSE_CLICK && LMouseButton == true && RMouseButton == false)
				{
					GameState = BlockManager::GetInstance()->Input(MousePos.x, MousePos.y, LMouseClick, GameState, iMineXPos, iMineYPos, iMineNum);
				}

				else if (RMouseClick == RIGHT_MOUSE_CLICK && RMouseButton == true && LMouseButton == false)
				{
					BlockManager::GetInstance()->Input(MousePos.x, MousePos.y, RMouseClick, GameState, iMineXPos, iMineYPos, iMineNum);
				}
			}
		}
	}

	if(MouseXPos > 17 && MouseYPos > 17 && MouseXPos < 40 && MouseYPos < 40)
	{
		if (LMouseClick == LEFT_MOUSE_CLICK && LMouseButton == true && RMouseButton == false)
		{
			if (ResetButton::GetInstance()->ClickedResetButton(MouseXPos, MouseYPos) == true)
			{
				Release();
				Map::GetInstance()->Init(Level, iMineXPos, iMineYPos);
				BlockManager::GetInstance()->Init(Level, iMineXPos, iMineYPos, iMineNum);

				GameState = GAME_PLAY;
				iTimeStart = GetTickCount();
				iTimeSec = 0;
			}
		}
	}

	InvalidateRect(hWnd, &cRect, FALSE);
	


	if (GameState == GAME_OVER)
	{
		MessageBox(hWnd, "GAME OVER", "GAME OVER", MB_OK);
	}

	if (GameState == GAME_CLEAR)
	{
		MessageBox(hWnd, "GAME CLEAR ", "GAME CLEAR", MB_OK);
	}
}

void GameManager::ClickedAtOnce(bool &RMouseButton, bool &LMouseButton, int MouseXPos, int MouseYPos, int &GameState)
{
	if (RMouseButton == true && LMouseButton == true)
	{
		if (MouseXPos > 42 && MouseYPos > 45 && MouseXPos < 820 && MouseYPos < 460)
		{
			MouseXPos = (MouseXPos - 42) / 26;
			MouseYPos = (MouseYPos - 45) / 26;

			BlockManager::GetInstance()->ClickedAroundOpen(MouseXPos, MouseYPos, iMineXPos,iMineYPos, GameState);
		}
	}

	if (GameState == GAME_OVER)
	{
		cout << "GAME_OVER!";
	}

	if (GameState == GAME_CLEAR)
	{
		cout << "CLEAR_GAME!!";
	}

	RMouseButton = false;
	LMouseButton = false;
}


void GameManager::Destroy()
{
	BlockManager::GetInstance()->Destroy();

		delete inst;
		inst = nullptr;
}



void GameManager::Release(void)
{
	BlockManager::GetInstance()->Release(iMineXPos, iMineYPos);
}

GameManager::GameManager()
{	
}


GameManager::~GameManager()
{

}
