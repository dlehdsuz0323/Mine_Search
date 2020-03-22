#include "Map.h"

Map* Map::inst = nullptr;

void Map::Init(int iLevel, int MineXPos, int MineYPos)
{	
	iMapXPos = MineXPos;
	iMapYPos = MineYPos;

	GameBackGround.push_back(BitImageManager::GetInstance()->GetBitImage(0, MAP));
	GameBackGround.push_back(BitImageManager::GetInstance()->GetBitImage(1, BLOCK));

}

void Map::Draw(HDC hdc, int iLevel, int MineXpos, int MineYPos)
{
	GameBackGround[0]->Draw(hdc, 0, 0, MAP);

	for (int i = 0; i < MineXpos; i++)
	{
		for (int j = 0; j < MineYPos; j++)
		{	
			GameBackGround[1]->Draw(hdc, i, j, NULL);
		}
	}
}
void Map::Destroy()
{
	if (inst)
	{
		delete inst;
		inst = nullptr;
	}
}


Map::Map()
{
}


Map::~Map()
{
}
