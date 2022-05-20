#pragma once
#include "Game.h"
#include <windows.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
//#include "debug.h"

#include"debug.h"
#include "GameObject.h"
#include "LoadedResources.h"
#include "PlayableCharacter.h"
#include <initguid.h>
#include <dinput.h>
//global define
#include "GlobalDefine.h"
Game* Game::__instance = NULL;
void Game::run() {
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / 60;
	LoadedResources* lr = LoadedResources::getInstance();
	InitKeyboard();
	while (true) {
		//game loops
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();
		
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			//keyboard handler
			pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

			spriteObject->Begin(D3DX10_SPRITE_SORT_TEXTURE);

			// Use Alpha blending for transparent sprites
			FLOAT NewBlendFactor[4] = { 0,0,0,0 };
			pD3DDevice->OMSetBlendState(pBlendStateAlpha, NewBlendFactor, 0xffffffff);
			//get keyboard state

			HRESULT hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
			if (FAILED(hr))
			{
				// If the keyboard lost focus or was not acquired then try to get control back.
				if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
				{
					HRESULT h = didv->Acquire();
					if (h == DI_OK)
					{
						DebugOut(L"[INFO] Keyboard re-acquired!\n");
					}
					else return;
				}
				else
				{
					//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
					return;
				}
			}

			// we have keyStates, check if what keys are pressed.
			keyHandler->KeyState((BYTE*)keyStates, lr->Mario);
DWORD dwElements = KEYBOARD_BUFFER_SIZE;
hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
if (FAILED(hr))
{
	DebugOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
	return;
}

// Scan through all buffered events, check if the key is pressed or released
// this is keydata. using for detect key up or down
for (DWORD i = 0; i < dwElements; i++)
{
	int KeyCode = keyEvents[i].dwOfs;
	int KeyState = keyEvents[i].dwData;
	//
	if ((KeyState & 0x80) > 0)
		keyHandler->OnKeyDown(KeyCode, lr->Mario);
	else
		keyHandler->OnKeyUp(KeyCode, lr->Mario);
}



this->Update(dt);


for (int i = 0; i < lr->stage_blocks.size(); i++) {
	if (i== lr->stage_blocks.size()-1)
		drawObject(lr->stage_blocks[i]);
	else
		drawObject(lr->stage_blocks[i]);

}
for (int i = 0; i < lr->enemies.size(); i++) {
	drawObject(lr->enemies[i]);

}
for (int i = 0; i < lr->Attack.size(); i++) {
	drawObject(lr->Attack[i]);

}
drawObject(lr->Mario);
spriteObject->End();
pSwapChain->Present(0, 0);
		}
		else
		Sleep((DWORD)(tickPerFrame - dt));

	}
	return;
}
void Game::InitKeyboard()
{
	KeyEventHandler* handler = new KeyEventHandler();
	//create DirectInput and DeviceInstance for game
	HRESULT hr = DirectInput8Create(*this->hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}
	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}
	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}
	this->keyHandler = handler;

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}
void Game::drawWoondenFloor(GameObject* _in)
{
	WoodenFloor* object = dynamic_cast<WoodenFloor*>(_in);
	if (dynamic_cast<Pipe*>(object)) {
		object = dynamic_cast<Pipe*>(object);
	}
	int width, height, spriteID;
	float x, y;
	object->getSize(width, height);
	SpriteManage* sm = SpriteManage::getInstance();
	for (int h_iter = 0; h_iter < height; h_iter++) {
		for (int w_iter = 0; w_iter < width; w_iter++) {
			spriteID = object->getCorrectSprite(w_iter, h_iter);
			object->getCorrectSpritePosition(w_iter, h_iter, x, y);
			Sprite* pSprite = sm->Get(spriteID);
			drawSprite(x, y, pSprite);
		}
	}
}
void Game::drawSprite(float x, float y, Sprite* sprite)
{
	float x_cord = x;
	float y_cord = (y);
	
	D3DXMatrixTranslation(&matTranslation, x_cord - this->cam_x - sprite->offset_x , y_cord - this->cam_y- sprite->offset_y , 1.0f);
	D3DX10_SPRITE d3dxSprite = sprite->sprite;
	d3dxSprite.matWorld = ((sprite->getMatrixScaling()) * matTranslation);
	//MIGHT CAUSE BUG
	spriteObject->DrawSpritesImmediate(&d3dxSprite, 1, 0, 0);
}
void Game::drawObject(GameObject* object)
{
	float x = object->GetX();
	float y = object->GetY();
	AnimationManage* am = AnimationManage::getInstance();
	if (dynamic_cast<WoodenFloor*>(object)) {
		drawWoondenFloor(object);
	}else 
	{
		int aniID = object->getCorrectAnimation();
		Animation* ani = am->Get(aniID);
		int spriteID = ani->getCorrectSpriteID();
		SpriteManage* sm = SpriteManage::getInstance();
		Sprite* pSprite = sm->Get(spriteID);
		drawSprite(x, y, pSprite);
	}
	
			

}
void Game::LoadResources()
{
	LoadedResources* lr = LoadedResources::getInstance();
	lr->LoadResources();
}
void Game::Update(DWORD dt)
{
	LoadedResources* lr = LoadedResources::getInstance();
	//update state of object.
	lr->Update(dt);
	float cx, cy;
	lr->Mario->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0;
	setCamPos(cx, cy);
}
void Render() {
	//draw all the correctly choose sprite from loaded resource instance;

}
HWND Game::_CreateGameWindow(HINSTANCE &hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)Game::WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH/*NEED DEFINE*/, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,// NEED DEFINE
			MAIN_WINDOW_TITLE,//NEED DEFINE
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		//DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}
LRESULT Game::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
Game* Game::getInstance() {
	if (__instance == NULL) __instance = new Game();
	return __instance;
}
void Game::Init(HINSTANCE &hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight) {
	RECT r;
	this->hInstance = &hInstance;
	hWnd = this->_CreateGameWindow(hInstance,nCmdShow,ScreenWidth, ScreenHeight);
	//get back buffer height and width
	GetClientRect(hWnd,&r);
	backBufferWidth = r.right + 1;
	backBufferHeight = r.bottom + 1;


	//get swap chain and device
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		//configuration for SwapChain
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = backBufferWidth;
		swapChainDesc.BufferDesc.Height = backBufferHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;

		//get device and swap chain according to config
		HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_REFERENCE, NULL, 0, D3D10_SDK_VERSION, &swapChainDesc, &pSwapChain, &pD3DDevice);

	//check hr aka handling error for get device and swap chain
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}
	//checking access to backbuffer
	ID3D10Texture2D* pBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}
	//create RenderView at backBufferPointer;
	hr = pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	pBackBuffer->Release();

	//check creating RenderView successful or not.
	if (hr != S_OK)
	{
		DebugOut((wchar_t*)L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}
	//set monitor?
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);
	// create and set the viewport
	D3D10_VIEWPORT viewPort;
	viewPort.Width = backBufferWidth;
	viewPort.Height = backBufferHeight;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	pD3DDevice->RSSetViewports(1, &viewPort);


	// create the sprite object associate with monitor? to handle sprite drawing 
	hr = D3DX10CreateSprite(pD3DDevice, 0, &spriteObject);

	if (hr != S_OK)
	{
		//DebugOut((wchar_t*)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
		return;
	}
	D3DXMATRIX matProjection;

	// Create the projection matrix using the values in the viewport
	D3DXMatrixOrthoOffCenterLH(&matProjection,
		(float)viewPort.TopLeftX,
		(float)viewPort.Width,
		(float)viewPort.TopLeftY,
		(float)viewPort.Height,
		0.1f,
		10);
	hr = spriteObject->SetProjectionTransform(&matProjection);

	// Initialize the blend state for alpha drawing
	D3D10_BLEND_DESC StateDesc;
	ZeroMemory(&StateDesc, sizeof(D3D10_BLEND_DESC));
	StateDesc.AlphaToCoverageEnable = FALSE;
	StateDesc.BlendEnable[0] = TRUE;
	StateDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	StateDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	StateDesc.BlendOp = D3D10_BLEND_OP_ADD;
	StateDesc.SrcBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	StateDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	pD3DDevice->CreateBlendState(&StateDesc, &this->pBlendStateAlpha);


}


