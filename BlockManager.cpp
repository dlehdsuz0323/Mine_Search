#include <conio.h>

#include "BlockManager.h"

BlockManager* BlockManager::inst = nullptr;

void BlockManager::Init(int iLevel, int MineXpos, int MineYPos, int iMineNum)
{	
	MineNum = iMineNum;
	ResetButton::GetInstance()->Init();
	Block::Getinstance()->Init(iLevel, MineXpos, MineYPos,iMineNum);
	blockmanager.push_back(BitImageManager::GetInstance()->GetBitImage(1, BLOCK));	
}	 

int BlockManager::ClickedMine(int MineXpos, int MineYPos, int iMineNum, int &iGameState, int MouseXPos, int MouseYPos)
{

	for (int k = 0; k < iMineNum; k++)
	{
		for (int i = 0; i < MineXpos; i++)
		{
			for (int j = 0; j < MineYPos; j++)
			{
				if(Block::Getinstance()->ReturnBlockState(i,j) == MINE)
				{
					if (MouseXPos == i && MouseYPos == j)
					{
						iGameState = GAME_OVER;
						return iGameState;
					}
				}
			}
		}
	}

	return false;
} 

void BlockManager::Draw(HDC hdc, int iLevel, int MineXpos, int MineYPos, HWND hWnd)
{
	ResetButton::GetInstance()->Draw(hdc);
	Block::Getinstance()->Draw(hdc, iLevel, MineXpos, MineYPos);
	//Block::Getinstance()->Draw(hdc, iLevel, MineXpos, MineYPos,0);
	Block::Getinstance()->DrawCloseBlock(hdc, iLevel, MineXpos, MineYPos);
	//Block::Getinstance()->DrawCloseBlock(hdc, iLevel, MineXpos, MineYPos,0);
	Block::Getinstance()->NumberOfMine(hdc, hWnd);
}

int BlockManager::ClearGame(int MineXPos, int MineYPos, int MineNum,int &iGameState)
{
	int iOpenBlock = 0;
	int iClearCondition = 0;
	iClearCondition = (MineXPos * MineYPos) - MineNum;

	for (int i = 0; i < MineYPos; i++)
	{
		for (int j = 0; j < MineXPos; j++)
		{
			if (Block::Getinstance()->ReturnObjectState(j, i) == NONE)
			{
				iOpenBlock += 1;
			}
		}
	}	

	if (iOpenBlock == iClearCondition)
	{
		cout << "CLEAR CONDITION" << endl;

		GameOver(MineXPos, MineYPos, iGameState);
		iGameState = GAME_CLEAR;
	}

	return iGameState;
}

int BlockManager::Input(int MouseXPos, int MouseYPos, int MouseClick, int iGameState, int MineXPos, int MineYPos, int iMineNum)
{
	if (MouseClick == LEFT_MOUSE_CLICK)
	{
		ClickedMine(MineXPos, MineYPos, iMineNum, iGameState,MouseXPos,MouseYPos);
		Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos);
		RepeatOpen(MouseXPos, MouseYPos, MineXPos, MineYPos);

		ClearGame(MineXPos, MineYPos, iMineNum, iGameState);
	}

	else if (MouseClick == RIGHT_MOUSE_CLICK)
	{
		if (Block::Getinstance()->PutFlag(MouseXPos, MouseYPos) == true)
		{
			Block::Getinstance()->PutFlag(MouseXPos, MouseYPos);
			return true;
		}

		if (Block::Getinstance()->DrawingFlag(MouseXPos, MouseYPos) == true)
		{	
			Block::Getinstance()->DrawingFlag(MouseXPos, MouseYPos);
			return true;
		}

	}

	if (iGameState == GAME_OVER)
	{
		GameOver(MineXPos, MineYPos, iGameState);
	}
	return iGameState;
}

int BlockManager::RepeatOpen(int MouseXPos, int MouseYPos, int MineXPos, int MineYPos)
{
	if (Block::Getinstance()->ReturnBlockState(MouseXPos,MouseYPos) == OPEN_BLOCK)
	{
		if (MouseXPos > 0 && MouseYPos > 0)
		{
			if(Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos - 1) == CLOSED_BLOCK)
			{
				if(Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos - 1) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos - 1) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos - 1);	
						RepeatOpen(MouseXPos - 1, MouseYPos - 1, MineXPos, MineYPos);
					}

					else if(Block::Getinstance()->ReturnBlockState(MouseXPos -1 , MouseYPos - 1) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos - 1);
					}
				}
			}
		}

		if (MouseYPos > 0)
		{
			if (Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos - 1) == CLOSED_BLOCK)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos, MouseYPos - 1) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos - 1) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos - 1);
						RepeatOpen(MouseXPos, MouseYPos - 1, MineXPos, MineYPos);
					}

					else if (Block::Getinstance()->ReturnBlockState(MouseXPos, MouseYPos - 1) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos - 1);
					}
				}
			}
		}

		if (MouseXPos < MineXPos - 1 && MouseYPos > 0)
		{
			if (Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos - 1) == CLOSED_BLOCK)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos - 1) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos - 1) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos - 1);
						RepeatOpen(MouseXPos + 1, MouseYPos - 1, MineXPos, MineYPos);
					}

					else if (Block::Getinstance()->ReturnBlockState(MouseXPos + 1, MouseYPos - 1) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos - 1);
					}
				}
			}
		}

		if (MouseXPos < MineXPos - 1)
		{
			if (Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos) == CLOSED_BLOCK)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos);
						RepeatOpen(MouseXPos + 1, MouseYPos, MineXPos, MineYPos);
					}

					else if (Block::Getinstance()->ReturnBlockState(MouseXPos + 1, MouseYPos) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos);
					}
				}
			}
		}

		if (MouseXPos < MineXPos - 1 && MouseYPos < MineYPos - 1)
		{
			if (Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos + 1) == CLOSED_BLOCK)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos + 1) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos + 1) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos + 1);
						RepeatOpen(MouseXPos + 1, MouseYPos + 1, MineXPos, MineYPos);
					}

					else if (Block::Getinstance()->ReturnBlockState(MouseXPos + 1, MouseYPos + 1) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos + 1);
					}
				}
			}
		}

		if (MouseYPos < MineYPos - 1)
		{
			if (Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos + 1) == CLOSED_BLOCK)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos, MouseYPos + 1) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos + 1) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos + 1);
						RepeatOpen(MouseXPos, MouseYPos + 1, MineXPos, MineYPos);
					}

					else if (Block::Getinstance()->ReturnBlockState(MouseXPos, MouseYPos + 1) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos + 1);
					}
				}
			}
		}

		if (MouseXPos > 0 && MouseYPos < MineYPos - 1)
		{
			if (Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos + 1) == CLOSED_BLOCK)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos + 1) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos + 1) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos + 1);
						RepeatOpen(MouseXPos - 1, MouseYPos + 1, MineXPos, MineYPos);
					}

					else if (Block::Getinstance()->ReturnBlockState(MouseXPos - 1, MouseYPos + 1) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos + 1);
					}
				}
			}
		}

		if (MouseXPos > 0)
		{
			if (Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos) == CLOSED_BLOCK)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos) != FLAG)
				{
					if (Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos) == NONE)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos);
						RepeatOpen(MouseXPos - 1, MouseYPos, MineXPos, MineYPos);
					}

					else if (Block::Getinstance()->ReturnBlockState(MouseXPos - 1, MouseYPos) > 0)
					{
						Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos);
					}
				}
			}
		}
	}
	return 0;
}

int BlockManager::ClickedMouseLR_AroundNumber(int MouseXPos, int MouseYPos, int MapXPos, int MapYPos)
{
	int iFlagAroundNum = 0;

	if(Block::Getinstance()->ReturnObjectState(MouseXPos,MouseYPos) == NONE)
	{
		if (MouseXPos >= 0 && MouseYPos >= 0 &&
			MouseXPos < MapXPos && MouseYPos < MapYPos)
		{
			if (MouseXPos > 0 && MouseYPos > 0)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos - 1) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}

			if (MouseXPos > 0)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos + 0) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}

			if (MouseXPos > 0 && MouseYPos < MapYPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos + 1) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}

			if (MouseYPos > 0)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 0, MouseYPos - 1) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}

			if (MouseYPos < MapYPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 0, MouseYPos + 1) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}

			if (MouseXPos < MapXPos - 1 && MouseYPos > 0)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos - 1) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}

			if (MouseXPos < MapXPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos + 0) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}

			if (MouseXPos < MapXPos - 1 && MouseYPos < MapYPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos + 1) == FLAG)
				{
					iFlagAroundNum += 1;
				}
			}
		}
	}
	return iFlagAroundNum;
} 

int BlockManager::ClickedAroundOpen(int MouseXPos, int MouseYPos, int MapXPos, int MapYPos, int &iGameState)
{
	if (ClickedMouseLR_AroundNumber(MouseXPos, MouseYPos, MapXPos, MapYPos) == Block::Getinstance()->ReturnBlockState(MouseXPos, MouseYPos))
	{
		if (MouseXPos >= 0 && MouseYPos >= 0 &&
			MouseXPos < MapXPos && MouseYPos < MapYPos)
		{
			if (MouseXPos > 0 && MouseYPos > 0)
			{
				if(Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos - 1) != FLAG)
				{
					if(Block::Getinstance()->ReturnBlockState(MouseXPos - 1, MouseYPos -1) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos - 1);
					RepeatOpen(MouseXPos - 1, MouseYPos - 1, MapXPos, MapYPos);
				}
			}

			if (MouseXPos > 0)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos) != FLAG)
				{
					if (Block::Getinstance()->ReturnBlockState(MouseXPos - 1, MouseYPos) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos);
					RepeatOpen(MouseXPos - 1, MouseYPos + 0, MapXPos, MapYPos);
				}
			}


			if (MouseXPos > 0 && MouseYPos < MapYPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos - 1, MouseYPos + 1) != FLAG)
				{
					if (Block::Getinstance()->ReturnBlockState(MouseXPos - 1, MouseYPos + 1) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos - 1, MouseYPos + 1);
					RepeatOpen(MouseXPos - 1, MouseYPos + 1, MapXPos, MapYPos);
				}
			}


			if (MouseYPos > 0)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos, MouseYPos - 1) != FLAG)
				{
					if (Block::Getinstance()->ReturnBlockState(MouseXPos, MouseYPos - 1) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos - 1);
					RepeatOpen(MouseXPos + 0, MouseYPos - 1, MapXPos, MapYPos);
				}
			}

			if (MouseYPos < MapYPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos, MouseYPos + 1) != FLAG)
				{
					if (Block::Getinstance()->ReturnBlockState(MouseXPos, MouseYPos + 1) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos, MouseYPos + 1);
					RepeatOpen(MouseXPos + 0, MouseYPos + 1, MapXPos, MapYPos);
				}
			}
			

			if (MouseXPos < MapXPos - 1 && MouseYPos > 0)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos - 1) != FLAG)
				{
					if (Block::Getinstance()->ReturnBlockState(MouseXPos + 1, MouseYPos - 1) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos - 1);
					RepeatOpen(MouseXPos + 1, MouseYPos - 1, MapXPos, MapYPos);
				}
			}

			if (MouseXPos < MapXPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos) != FLAG)
				{
					if (Block::Getinstance()->ReturnBlockState(MouseXPos + 1, MouseYPos) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos);
					RepeatOpen(MouseXPos + 1, MouseYPos + 0, MapXPos, MapYPos);
				}
			}

			if (MouseXPos < MapXPos - 1 && MouseYPos < MapYPos - 1)
			{
				if (Block::Getinstance()->ReturnObjectState(MouseXPos + 1, MouseYPos + 1) != FLAG)
				{
					if (Block::Getinstance()->ReturnBlockState(MouseXPos + 1, MouseYPos + 1) == MINE)
					{
						iGameState = GAME_OVER;
						GameOver(MapXPos, MapYPos, iGameState);
						return false;
					}
					Block::Getinstance()->OpenBlockState(MouseXPos + 1, MouseYPos + 1);
					RepeatOpen(MouseXPos + 1, MouseYPos + 1, MapXPos, MapYPos);
				}

			}
		}
	}

	ClearGame(MapXPos, MapYPos, MineNum,iGameState);
	return iGameState;
}

void BlockManager::GameOver(int MineXPos, int MineYPos, int & iGamestate)
{
	if (iGamestate == GAME_OVER)
	{
		for (int i = 0; i < MineXPos; i++)
		{
			for (int j = 0; j < MineYPos; j++)
			{
				if (Block::Getinstance()->ReturnBlockState(i, j) == MINE)
				{
					Block::Getinstance()->OpenBlockState(i, j);
				}
			}
		}
	}
}

void BlockManager::Release(int MineXpos, int MineYPos)
{
	Block::Getinstance()->Release(MineXpos, MineYPos);
}

void BlockManager::Destroy()
{
	Map::GetInstance()->Destroy();
	Block::Getinstance()->Destroy();
	ResetButton::GetInstance()->Destroy();
	BitImageManager::GetInstance()->Destroy();


	if (inst)
	{
		delete inst;
		inst = nullptr;
	}
}

BlockManager::BlockManager()
{

}


BlockManager::~BlockManager()
{
}
