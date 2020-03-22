#include "Block.h"

Block* Block::inst = nullptr;

Block::Block()
{
}

void Block::Init(int iLevel, int MineXPos, int MineYPos, int iMineNum)
{
	MineNumCount = iMineNum;

	for (int i = 0; i < 10; i++)
	{
		GameBlock.push_back(BitImageManager::GetInstance()->GetBitImage(i, BLOCK));
	}

	for (int i = 0; i < 2; i++)
	{
		GameBlock.push_back(BitImageManager::GetInstance()->GetBitImage(i, OBJECT));
	}

	arrBlockState = new int*[MineYPos];	 
	for (int i = 0; i < MineYPos; i++)
	{
		arrBlockState[i] = new int[MineXPos];
	}

	arrObjectBlockState = new int*[MineYPos];
	for (int i = 0; i < MineYPos; i++)
	{
		arrObjectBlockState[i] = new int[MineXPos];
	}

	arrBlockState2 = new int[MineXPos * MineYPos];
	arrObjectBlockState2 = new int[MineXPos * MineYPos];

	////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < MineXPos * MineYPos; i++)
	{
		arrBlockState2[i] = OPEN_BLOCK;
		arrObjectBlockState2[i] = CLOSED_BLOCK;
	}

	for (int i = 0; i < MineYPos; i++)
	{
		for (int j = 0; j < MineXPos; j++)
		{
			arrObjectBlockState[i][j] = CLOSED_BLOCK;
			arrBlockState[i][j] = OPEN_BLOCK;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////

	 InitPutMine(iLevel, MineXPos, MineYPos, iMineNum);
	
	//InitPutMine(iLevel, MineXPos, MineYPos, iMineNum,1);

	SearchAroundMines(MineXPos, MineYPos);

	//SearchAroundMines(MineXPos, MineYPos, 1);
}

void Block::InitPutMine(int iLevel, int MineXpos, int MineYPos, int iMineNum)
{
	POINT mine;
	srand(unsigned int(time(NULL)));

	for (int k = 0; k < iMineNum; k++)
	{
		for (int i = 0; i < MineYPos; i++)
		{
			for (int j = 0; j < MineXpos; j++)
			{
				mine.x = rand() % MineXpos;
				break;
			}

			mine.y = rand() % MineYPos;
			if (arrBlockState[mine.y][mine.x] != MINE)
			{
				arrBlockState[mine.y][mine.x] = MINE;
				break;
			}

		}
	}
}
//
//void Block::InitPutMine(int iLevel, int MineXPos, int MineYpos, int iMineNUm, int Test)                   
//{
//	int iMinePos = 0;
//
//	srand(unsigned int(time(NULL)));
//
//	for (int i = 0; i < iMineNUm; i++)
//	{
//		for (int j = 0; j < MineXPos * MineYpos; j++)
//		{
//			iMinePos = rand() % (MineXPos * MineYpos);
//
//			if (arrBlockState2[j] != MINE)
//			{
//				arrBlockState2[iMinePos] = MINE;
//				break;
//			}
//		}
//	}
//}

void Block::Draw(HDC hdc, int iLevel, int MineXpos, int MineYPos)
{
	for (int i = 0; i < MineYPos; i++)
	{
		for (int j = 0; j < MineXpos; j++)
		{
			GameBlock[arrBlockState[i][j]]->Draw(hdc, j, i, NULL);
		}
	}
}

//void Block::Draw(HDC hdc, int iLevel, int MineXPos, int MineYPos, int test)
//{
//	for (int i = 0; i < MineXPos * MineYPos; i++)
//	{
//		GameBlock[arrBlockState2[i]]->Draw(hdc, i%MineXPos, i / MineXPos, NULL);
//	}		
//}

void Block::DrawCloseBlock(HDC hdc, int iLevel, int MineXPos, int MineYPos)
{
	for (int i = 0; i < MineYPos; i++)
	{
		for (int j = 0; j < MineXPos; j++)
		{
			if (arrObjectBlockState[i][j] == NONE)
			{
				continue;
			}
			GameBlock[arrObjectBlockState[i][j]]->Draw(hdc, j, i, NULL);
		}
	}
}
//
//void Block::DrawCloseBlock(HDC hdc, int iLevel, int MineXPos, int MineYPos, int test)
//{
//	for (int i = 0; i < MineXPos * MineYPos; i++)
//	{
//		if (arrObjectBlockState2[i] == NONE)
//		{
//			continue;
//		}
//		GameBlock[arrObjectBlockState2[i]]->Draw(hdc, i%MineXPos, i / MineXPos, NULL);
//	}
//}

bool Block::PutFlag(int MouseXPos, int MouseYPos)
{
	if (arrObjectBlockState[MouseYPos][MouseXPos] == CLOSED_BLOCK)
	{
		MineNumCount--;
		arrObjectBlockState[MouseYPos][MouseXPos] = FLAG;

		return true;
	}

	return false;
}
//
//bool Block::PutFlag(int MouseXPos, int MouseYPos, int test)
//{
//	if (arrObjectBlockState2[MouseXPos] == CLOSED_BLOCK)
//	{
//		MineNumCount--;
//		arrObjectBlockState2[MouseXPos] = FLAG;
//
//		return true;
//	}
//
//	return false;
//}

bool Block::DrawingFlag(int MouseXPos, int MouseYPos)
{
	if (arrObjectBlockState[MouseYPos][MouseXPos] == FLAG)
	{
		MineNumCount++;
		arrObjectBlockState[MouseYPos][MouseXPos] = CLOSED_BLOCK;

		return true;
	}

	return false;
}
//
//bool Block::DrawingFlag(int MouseXPos, int MouseYPos, int test)
//{
//	if (arrObjectBlockState2[MouseXPos] == FLAG)
//	{
//		MineNumCount++;
//		arrObjectBlockState2[MouseXPos] = CLOSED_BLOCK;
//
//		return true;
//	}
//
//	return false;
//}

void Block::NumberOfMine(HDC hdc, HWND hWnd)
{
	wsprintf(str, TEXT("%d"), MineNumCount);
	TextOut(hdc, 680, 480, str, lstrlen(str));
}


void Block::SearchAroundMines(int MineXpos, int MineYPos)
{
	for (int i = 0; i < MineYPos; i++)
	{
		for (int j = 0; j < MineXpos; j++)
		{
			if (arrBlockState[i][j] == MINE)
			{
				if (i >= 0 && j >= 0 &&
					j < MineXpos && i  < MineYPos)
				{
					if (i > 0 && j > 0)
					{
						if (arrBlockState[i-1][j-1]!= MINE)
						{
							arrBlockState[i - 1][j - 1] += 1;
						}
					}

					if (i > 0)
					{
						if (arrBlockState[i-1][j]!= MINE)
						{
							arrBlockState[i - 1][j] += 1;
						}
					}

					//if (i > 0 && j < MineXpos)
					{
						if (j < MineXpos - 1 && i > 0)
						{
							if (arrBlockState[i-1][j+1]!= MINE)
							{
								arrBlockState[i - 1][j + 1] += 1;
							}
						}
					}

					if (j > 0)
					{
						if (arrBlockState[i][j-1]!= MINE)
						{
							arrBlockState[i][j - 1] += 1;
						}
					}

					if (j < MineXpos - 1)
					{
						if (arrBlockState[i][j+1]!= MINE)
						{
							arrBlockState[i][j + 1] += 1;
						}
					}

					if (i < MineYPos - 1 && j > 0)
					{
						if (arrBlockState[i+1][j-1]!= MINE)
						{
							arrBlockState[i + 1][j - 1] += 1;
						}
					}
					if (i < MineYPos - 1)
					{
						if (arrBlockState[i+1][j]!= MINE)
						{
							arrBlockState[i + 1][j] += 1;
						}
					}
					if (i < MineYPos - 1 && j < MineXpos - 1)
					{
						if (arrBlockState[i+1][j+1]!= MINE)
						{
							arrBlockState[i + 1][j + 1] += 1;
						}
					}

				}
			}
		}
	}
}
//
//void Block::SearchAroundMines(int MineXPos, int MineYPos, int test)
//{
//	/*
//		i % high  == 0 continue
//		i % high  == 1 continue
//	*/
//	for (int i = 0; i < MineXPos * MineYPos; i++)
//	{
//		if (arrBlockState2[i] == MINE)
//		{
//			if(i == (MineXPos / 15))
//			if (i - (MineXPos - 1) >= 0)
//			{
//				if (arrBlockState2[i - MineXPos - 1] != MINE)
//				{
//					arrBlockState2[i - MineXPos - 1] += 1;
//				}
//			}
//
//			if (i - MineXPos >= 0)
//			{
//				if (arrBlockState2[i - MineXPos] != MINE)
//				{
//					arrBlockState2[i - MineXPos] += 1;
//				}
//			}
//
//			if (i - (MineXPos + 1) >= 0)
//			{
//				if (arrBlockState2[i - MineXPos + 1] != MINE)
//				{
//					arrBlockState2[i - MineXPos + 1] += 1;
//				}
//			}
//
//			if (i - 1 >= 0)
//			{
//				if (arrBlockState2[i - 1] != MINE)
//				{
//					arrBlockState2[i - 1] += 1;
//				}
//			}
//
//			if (i + 1 < MineXPos * MineYPos)
//			{
//				if (arrBlockState2[i + 1] != MINE)
//				{
//					arrBlockState2[i + 1] += 1;
//				}
//			}
//
//			if (i + (MineXPos - 1) < MineXPos * MineYPos)
//			{
//				if (arrBlockState2[i + MineXPos - 1] != MINE)
//				{
//					arrBlockState2[i + MineXPos - 1] += 1;
//				}
//			}
//
//			if (i + MineXPos < MineXPos * MineYPos)
//			{
//				if (arrBlockState2[i + MineXPos] != MINE)
//				{
//					arrBlockState2[i + MineXPos] += 1;
//				}
//			}
//
//			if (i + (MineXPos + 1) < MineXPos * MineYPos)
//			{
//				if (arrBlockState2[i + MineXPos + 1] != MINE)
//				{						   
//					arrBlockState2[i + MineXPos + 1] += 1;
//				}
//			}
//		}
//	}
//}

int Block::OpenBlockState(int MineXPos, int MineYPos)
{
	if (arrObjectBlockState[MineYPos][MineXPos] == FLAG)
	{
		return false;
	}

	if (arrObjectBlockState[MineYPos][MineXPos] == NONE)
	{
		return NONE;
	}

	else if (arrObjectBlockState[MineYPos][MineXPos] == CLOSED_BLOCK)
	{
		arrObjectBlockState[MineYPos][MineXPos] = NONE;

		return CLOSED_BLOCK;
	}

	return false;
}

int Block::ReturnBlockState(int PosX, int PosY)
{
	if (arrBlockState[PosY][PosX] == MINE)
	{
		return MINE;
	}

	if (arrBlockState[PosY][PosX] < 10)
	{
		return arrBlockState[PosY][PosX];
	}

	return false;
}

int Block::ReturnObjectState(int PosX, int PosY)
{
	if (arrObjectBlockState[PosY][PosX] == FLAG)
	{
		return FLAG;
	}

	else if (arrObjectBlockState[PosY][PosX] == NONE)
	{
		return NONE;
	}

	return false;
}


void Block::print(int MapWidth, int MapHigh)
{
	cout << "----------------------------------------------------------------------------" << endl;

	for (int i = 0; i < MapHigh; i++)
	{
		for (int j = 0; j < MapWidth; j++)
		{
			cout << arrBlockState[i][j];
			cout << "	";
		}
		cout << endl;
	}
	cout << endl;
	cout << "----------------------------------------------------------------------------" << endl;
}

void Block::Destroy()
{
	if (inst)
	{
		delete inst;
		inst = nullptr;
	}
}

void Block::Release(int MineXpos, int MineYPos)
{
	delete arrBlockState2;
	delete arrObjectBlockState2;

	for (int i = 0; i < MineYPos; i++)
	{
		delete[]arrBlockState[i];
	}
	delete[]arrBlockState;

	for (int i = 0; i < MineYPos; i++)
	{
		delete[]arrObjectBlockState[i];
	}
	delete[]arrObjectBlockState;

}

Block::~Block()
{
}
