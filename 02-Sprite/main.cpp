/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Mario.h"
#include "Brick.h"
#include "Koopa.h"
#include "Door.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_ENEMY_FLIPPED 11
#define ID_TEX_MISC 20

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario_transparent.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies_transparent.png"
#define TEXTURE_PATH_ENEMIES_FLIPPED TEXTURES_DIR "\\enemies_flipped.png"

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f
#define MARIO_START_VY 0.0f
#define MARIO_WIDTH 14
#define MARIO_HEIGHT 27

CBrick *brick;

CDoor* door;
#define DOOR_START_X 200.0f
#define DOOR_START_Y 130.0f
#define DOOR_WIDTH 16
#define DOOR_HEIGHT 26

CKoopa *koopa;
#define KOOPA_START_X 50.0f
#define KOOPA_START_Y 130.0f
#define KOOPA_START_VX 0.1f
#define KOOPA_START_VY 0.0f
#define KOOPA_WIDTH 18
#define KOOPA_HEIGHT 27

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			mario->SetDirection(-1);
			mario->SetMoving(true);
			break;
		case VK_RIGHT:
			mario->SetDirection(1);
			mario->SetMoving(true);
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_LEFT:
		case VK_RIGHT:
			mario->SetMoving(false);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMIES);
	textures->Add(ID_TEX_ENEMY_FLIPPED, TEXTURE_PATH_ENEMIES_FLIPPED);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);

	// Verify textures are loaded
	if (textures->Get(ID_TEX_MARIO) == nullptr) {
		DebugOut(L"[ERROR] Failed to load texture: %s\n", TEXTURE_PATH_MARIO);
	}
	if (textures->Get(ID_TEX_ENEMY) == nullptr) {
		DebugOut(L"[ERROR] Failed to load texture: %s\n", TEXTURE_PATH_ENEMIES);
	}
	if (textures->Get(ID_TEX_MISC) == nullptr) {
		DebugOut(L"[ERROR] Failed to load texture: %s\n", TEXTURE_PATH_MISC);
	}

	CSprites* sprites = CSprites::GetInstance();
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// readline => id, left, top, right, bottom

	// MARIO SPRITE
	// idle right sprites
	sprites->Add(10001, 246, 154, 260, 181, texMario);

	// idle left sprites
	sprites->Add(10011, 186, 154, 200, 181, texMario);

	// move right sprites
	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	// move left sprites
	sprites->Add(10011, 186, 154, 200, 181, texMario);
	sprites->Add(10012, 155, 154, 171, 181, texMario);
	sprites->Add(10013, 125, 154, 141, 181, texMario);

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(502, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(503, ani);

	// move right animation
	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	// move left animation
	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	// BRICK SPRITE
	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 300, 135, 317, 151, texMisc);
	sprites->Add(20002, 318, 135, 335, 151, texMisc);
	sprites->Add(20003, 336, 135, 353, 151, texMisc);
	sprites->Add(20004, 354, 135, 371, 151, texMisc);

	ani = new CAnimation(100);
	ani->Add(20001, 1000);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(510, ani);

	//door top sprite
	sprites->Add(40001, 282, 99, 298, 115, texMisc);
	sprites->Add(40003, 282, 135, 298, 151, texMisc);
	sprites->Add(40005, 282, 171, 298, 187, texMisc);
	sprites->Add(40007, 282, 207, 298, 223, texMisc);

	//door bottom sprite
	sprites->Add(40002, 282, 117, 298, 133, texMisc);
	sprites->Add(40004, 282, 153, 298, 169, texMisc);
	sprites->Add(40006, 282, 189, 298, 205, texMisc);
	sprites->Add(40008, 282, 225, 298, 241, texMisc);

	//door top animation
	ani = new CAnimation(100);
	ani->Add(40001);
	ani->Add(40003);
	ani->Add(40005);
	ani->Add(40007);
	ani -> SetLooping(false);
	animations->Add(530, ani);

	//door bottom animation
	ani = new CAnimation(100);
	ani->Add(40002);
	ani->Add(40004);
	ani->Add(40006);
	ani->Add(40008);
	ani->SetLooping(false);
	animations->Add(531, ani);


	// Koopa walking sprites
	LPTEXTURE texEnemies = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 5, 129, 23, 157, texEnemies);
	sprites->Add(30002, 27, 129, 45, 157, texEnemies);

	LPTEXTURE texEnemies_flipped = textures->Get(ID_TEX_ENEMY_FLIPPED);
	sprites->Add(30011, 435, 129, 453, 157, texEnemies_flipped);
	sprites->Add(30012, 457, 129, 475, 157, texEnemies_flipped);

	// Koopa walking animation
	ani = new CAnimation(200);
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(520, ani);

	// Koopa walking flipped animation
	ani = new CAnimation(200);
	ani->Add(30011);
	ani->Add(30012);
	animations->Add(521, ani);

	mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_WIDTH, MARIO_HEIGHT, MARIO_START_VX, MARIO_START_VY);
	brick = new CBrick(100.0f, 100.0f);
	koopa = new CKoopa(KOOPA_START_X, KOOPA_START_Y, KOOPA_WIDTH, KOOPA_HEIGHT ,KOOPA_START_VX, KOOPA_START_VY);
	door = new CDoor(DOOR_START_X, DOOR_START_Y, DOOR_WIDTH, DOOR_HEIGHT);
}
	
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
	koopa->Update(dt);
	door->Update(dt);
	if(door->CheckCollision(mario))
	{
		door->OnCollision(mario);
	}
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		brick->Render();
		mario->Render();
		// In Render() function, add after mario->Render():
		koopa->Render();
		door->Render();


		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
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
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame *game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}