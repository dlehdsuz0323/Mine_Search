#pragma once

#include "Global.h"
#include "BitImageManager.h"


class ResetButton
{
private:

	static ResetButton* inst;
	vector <BitImage*> GameReset;

public:

	void Init();
	void Draw(HDC hdc);
	bool ClickedResetButton(int MouseXPos, int MouseYPos);
	void Release();
	void Destroy();

	static ResetButton* GetInstance()
	{
		if (inst == nullptr)
			inst = new ResetButton();

		return inst;
	}


	ResetButton();
	~ResetButton();
};

