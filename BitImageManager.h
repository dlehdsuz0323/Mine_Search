#pragma once
#include <Windows.h>
#include <vector>

#include "BitImage.h"
#include "Global.h"

using namespace std;


class BitImageManager
{
private:

	static BitImageManager* inst;

	vector <BitImage*> VecBlock;
	vector <BitImage*> VecObject;
	vector <BitImage*> vecMap;
	vector <BitImage*> vecReset;

	HWND				hWnd;

public:

	void Init(HDC hdc);
	BitImage* GetBitImage(int BlockID, int ObjectKind);


	void Release();
	void Destroy();

	static BitImageManager* GetInstance()
	{
		if (inst == nullptr)
			inst = new BitImageManager();

		return inst;
	}

	BitImageManager();
	~BitImageManager();
};