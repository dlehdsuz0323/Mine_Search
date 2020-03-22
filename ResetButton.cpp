#include "ResetButton.h"

ResetButton* ResetButton::inst = nullptr;

void ResetButton::Init()
{
	GameReset.push_back(BitImageManager::GetInstance()->GetBitImage(0, RESET));
}

void ResetButton::Draw(HDC hdc)
{
	GameReset[0]->Draw(hdc, -1, -1, NULL);
}

bool ResetButton::ClickedResetButton(int MouseXPos, int MouseYPos)
{
	if (MouseXPos > 17 && MouseYPos > 17 && MouseXPos < 40 && MouseYPos < 40)
	{
		return true;
	}
	return false;
}

void ResetButton::Release()
{
}

void ResetButton::Destroy()
{
	if (inst)
	{
		delete inst;
		inst = nullptr;
	}
}

ResetButton::ResetButton()
{
}


ResetButton::~ResetButton()
{
}
