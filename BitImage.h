#pragma once
#include <Windows.h>

#include "Global.h"

class BitImage
{
private:

	HDC MemDC;
	SIZE BitImageSize;
	HBITMAP MyBitMap;
	HBITMAP OldBitMap;

public:

	void Init(HDC hdc, HWND hwnd, char *cBlock);
	void Draw(HDC hdc, int iMineXPos, int iMineYPos, int iAreaCheck);
	void Release(void);

	BitImage();
	~BitImage();
};

