#include <windows.h>
#include <crtdbg.h>

#include "GameManager.h"
#include "resource.h"

#include "BitImageManager.h"



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hinst;
LPCTSTR lpszClass = TEXT("Mine_Search");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
//	_CrtSetBreakAlloc(243);


	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hinst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);


	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

HDC hdc;
PAINTSTRUCT ps;


int iLevel =	HARD;

static int RMousePointX;
static int RMousePointY;

static int LMousePointX;
static int LMousePointY;

bool RMouseButtonUP = false;
bool LMouseButtonUP = false;

int iGameState;
int start, finish;
int timeSec;
TCHAR str[128];
RECT cRect = { 120, 470, 200, 500 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (iGameState == GAME_PLAY)
	{
		timeSec = (finish - start) / 1000;
		finish = GetTickCount();
	}

	switch (iMessage) 
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		iGameState = GAME_PLAY;
		GameManager::GetInstance()->Init(hdc, iLevel, iGameState);
		start = GetTickCount();
		return 0;
	case WM_TIMER:
		wsprintf(str, TEXT("%d"), timeSec);
		InvalidateRect(hWnd,&cRect, FALSE);
		return 0;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GameManager::GetInstance()->Draw(hdc, hWnd);
		TextOut(hdc, 180, 480, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;

	case WM_LBUTTONUP: 
		LMousePointX = LOWORD(lParam);
		LMousePointY = HIWORD(lParam);
		GameManager::GetInstance()->Input(LMousePointX, LMousePointY, hWnd, NULL, LEFT_MOUSE_CLICK,RMouseButtonUP,LMouseButtonUP, iGameState, timeSec, start);
		GameManager::GetInstance()->ClickedAtOnce(RMouseButtonUP,LMouseButtonUP, LMousePointX, LMousePointY, iGameState);
		return 0;

	case WM_RBUTTONUP:
		RMousePointX = LOWORD(lParam);
		RMousePointY = HIWORD(lParam);
		GameManager::GetInstance()->Input(RMousePointX, RMousePointY, hWnd, RIGHT_MOUSE_CLICK,NULL, RMouseButtonUP, LMouseButtonUP, iGameState, timeSec, start);
		GameManager::GetInstance()->ClickedAtOnce(RMouseButtonUP, LMouseButtonUP, RMousePointX, RMousePointY, iGameState);
		return 0;

	case WM_LBUTTONDOWN:
		LMousePointX = LOWORD(lParam);
		LMousePointY = HIWORD(lParam);
		LMouseButtonUP = true;
		return 0;

	case WM_RBUTTONDOWN:
		RMousePointX = LOWORD(lParam);
		RMousePointY = HIWORD(lParam);
		RMouseButtonUP = true;
		return 0;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
	
		case ID_MENU_LEVEL:
			if (DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About) == TRUE)
			{
				GameManager::GetInstance()->Release();

				iGameState = GAME_PLAY;
				timeSec = 0;
				start = GetTickCount();
				GameManager::GetInstance()->Init(hdc, iLevel, iGameState);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;

		case ID_MENU_EXIT:
			PostQuitMessage(0);
			break;

		}
		return 0;

	
	case WM_DESTROY:
		BitImageManager::GetInstance()->Release();
		GameManager::GetInstance()->Release();
		GameManager::GetInstance()->Destroy();
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
		{
			if (LOWORD(wParam) == IDOK)
			{
				iLevel = EASY;


				EndDialog(hDlg, LOWORD(wParam));	
				return (INT_PTR)TRUE;
			}
			
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)FALSE;
		}

		else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
		{
			if (LOWORD(wParam) == IDOK)
			{
				iLevel = NOMAL;


				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)FALSE;
		}


		else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
		{
			if (LOWORD(wParam) == IDOK)
			{
				iLevel = HARD;


				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)FALSE;
		}

	}
	return (INT_PTR)FALSE;
}