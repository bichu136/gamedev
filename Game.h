#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "Texture.h"
#include "Sprite.h"
#include "LoadedResources.h"
#include "PlayableCharacter.h"
#include "GameObject.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "KeyEventHandler.h"
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256


class Game
{
private:
    static Game* __instance;
    int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
    int backBufferHeight = 0;
    ID3D10Device* pD3DDevice = NULL; //get monitor device?
    IDXGISwapChain* pSwapChain = NULL; // tool for swa p2 frame?
    ID3D10RenderTargetView* pRenderTargetView = NULL; // reder tools?
    ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state

    ID3DX10Sprite* spriteObject = NULL;

    D3DXMATRIX matTranslation;
    HWND hWnd;
    
    //inputs
    LPDIRECTINPUT8       di;		// The DirectInput object         
    LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 
    BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
    DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

    KeyEventHandler* keyHandler;
    HINSTANCE* hInstance;

    HWND _CreateGameWindow(HINSTANCE &hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
    static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    //WINDOW_CLASS_NAME
    //MAIN_WINDOW_TITLE
    //WINDOW_ICON_PATH
public:
    //init DirectX, sprite Handler;
    void Init(HINSTANCE &hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight);
    static Game* getInstance();
    void run();
    void Draw(float x, float y, Texture* tex, RECT* rect = NULL);
    void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b)
    {
        RECT rect;
        rect.left = l;
        rect.top = t;
        rect.right = r;
        rect.bottom = b;
        this->Draw(x, y, tex, &rect);
    }
    void InitKeyboard();
    void drawWoondenFloor(GameObject* object);
    Texture* LoadTexture(LPCWSTR texturePath);
    ID3D10Device* getDevice() { return pD3DDevice; }
    IDXGISwapChain* getSwapChain() { return pSwapChain; }
    ID3D10RenderTargetView* getRenderTargetView() { return pRenderTargetView; }
    ID3D10BlendState* getBlendState() { return pBlendStateAlpha; }		
    ID3DX10Sprite* getSpriteObject() { return spriteObject; }
    int getBackBufWidth() { return backBufferWidth; }
    int getBackBufHeight() { return backBufferHeight; }
    HWND getHWnd() { return hWnd; };
    void drawSprite(float x, float y, Sprite* sprite);
    void drawObject(GameObject* object);
    void LoadResources();
    void Update(DWORD dt);
    void drawPlatform(GameObject* object);
};

