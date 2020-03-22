#include <iostream>

#include "BitImageManager.h"
#include "BitImage.h"

BitImageManager* BitImageManager::inst = nullptr;

BitImageManager::BitImageManager()
{
}

void BitImageManager::Init(HDC hdc)
{
	char chMine[256];
	char chFlag[256];
	char chBlock[256];
	char chMap[256];
	char chReset[256];
	

	//BLOCK
	for (int i = 0; i < 9; i++)
	{
		BitImage* Block_pNew = new BitImage();
		sprintf_s(chBlock, "block_%d.bmp", i);
		Block_pNew->Init(hdc, hWnd, chBlock);
		VecBlock.push_back(Block_pNew);
	}

	BitImage* Block_pNew = new BitImage();
	sprintf_s(chBlock, "block.bmp");
	Block_pNew->Init(hdc, hWnd, chBlock);
	VecBlock.push_back(Block_pNew);
	
	//MINE
	BitImage* Mine_pNew = new BitImage();
	sprintf_s(chMine, "mine.bmp");
	Mine_pNew->Init(hdc, hWnd, chMine);
	VecObject.push_back(Mine_pNew);

	//BACKGROUND
	BitImage* BackGround_pNew = new BitImage();
	sprintf_s(chMap, "back.bmp");
	BackGround_pNew->Init(hdc, hWnd, chMap);
	vecMap.push_back(BackGround_pNew);

	//FLAG
	BitImage* Flag_pNew = new BitImage();
	sprintf_s(chFlag, "flag.bmp");
	Flag_pNew->Init(hdc, hWnd, chFlag);
	VecObject.push_back(Flag_pNew);

	//RESET
	BitImage* Reset_pNew = new BitImage();
	sprintf_s(chReset, "reset.bmp");
	Reset_pNew->Init(hdc, hWnd, chReset);
	vecReset.push_back(Reset_pNew);
}

BitImage * BitImageManager::GetBitImage(int BlockID, int ObjectKind)
{
	if (ObjectKind == BLOCK)
	{
		return VecBlock[BlockID];
	}

	else if (ObjectKind == OBJECT)
	{
		return VecObject[BlockID];
	}

	else if (ObjectKind == RESET)
	{
		return vecReset[BlockID];
	}

	else if (ObjectKind == MAP)
	{
		return vecMap[BlockID];
	}

	return false;
}

void BitImageManager::Release()
{
	for (auto iter = VecBlock.begin(); iter != VecBlock.end(); iter++)
	{
		delete(*iter);
	}

	for (auto iter = VecObject.begin(); iter != VecObject.end(); iter++)
	{
		delete(*iter);
	}

	for (auto iter = vecMap.begin(); iter != vecMap.end(); iter++)
	{
		delete(*iter);
	}

	for (auto iter = vecReset.begin(); iter != vecReset.end(); iter++)
	{
		delete (*iter);
	}


}

void BitImageManager::Destroy()
{
	if (inst)
	{
		delete inst;
		inst = nullptr;
	}
}


BitImageManager::~BitImageManager()
{
}
