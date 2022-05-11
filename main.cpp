#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include"game.h"
#include "GlobalDefine.h"
//HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
//{
//	WNDCLASSEX wc;
//	wc.cbSize = sizeof(WNDCLASSEX);
//
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.hInstance = hInstance;
//
//	wc.lpfnWndProc = (WNDPROC)WinProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = WINDOW_CLASS_NAME;
//	wc.hIconSm = NULL;
//
//	RegisterClassEx(&wc);
//
//	HWND hWnd =
//		CreateWindow(
//			WINDOW_CLASS_NAME,
//			MAIN_WINDOW_TITLE,
//			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
//			CW_USEDEFAULT,
//			CW_USEDEFAULT,
//			ScreenWidth,
//			ScreenHeight,
//			NULL,
//			NULL,
//			hInstance,
//			NULL);
//
//	if (!hWnd)
//	{
//		DWORD ErrCode = GetLastError();
//		//DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
//		return 0;
//	}
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	//SetDebugWindow(hWnd);
//
//	return hWnd;
//}
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	//HWND hWnd = CreateGameWindow(hInstance, nCmdShow, 1080, 720);
	Game *game = Game::getInstance();
	game->Init(hInstance, nCmdShow, 1080, 720);
	game->LoadResources();
	SetWindowPos(game->getHWnd(), 0, 0, 0, 1080, 720, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	game->run();
	return 0;
}