#include "BitImage.h"



BitImage::BitImage()
{
}


BitImage::~BitImage()
{
}

void BitImage::Init(HDC hdc, HWND hwnd, char *cBlock)
{
	MemDC = CreateCompatibleDC(hdc);
	MyBitMap = (HBITMAP)LoadImage(NULL, cBlock,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	if (MyBitMap == NULL)
	{
		MessageBox(hwnd, "이미지 로드 실패", "이미지 로드 실패", MB_OK);
	}
	OldBitMap = (HBITMAP)SelectObject(MemDC, MyBitMap);	

}

void BitImage::Draw(HDC hdc, int iMineXPos, int iMineYPos, int iAreaCheck)
{
	if (iAreaCheck == MAP)
	{
		TransparentBlt(hdc, iMineXPos, iMineYPos, 870, 512, MemDC, 0, 0, 870, 512, RGB(255, 0, 255));
	}
	else
	TransparentBlt(hdc, (iMineXPos*26+42), (iMineYPos*26+45), 26, 26, MemDC, 0, 0, 26, 26, RGB(255, 0, 255));
}

void BitImage::Release(void)
{
	DeleteObject(MemDC);
	DeleteObject(MyBitMap);
	DeleteObject(OldBitMap);
}
