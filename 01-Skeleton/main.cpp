/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 01 - SKELETON CODE 

	This sample illustrates how to:

	1/ Re-organize introductory code to an initial skeleton for better scalability
	2/ CGame is a singleton, playing a role of an "engine".
	3/ CGameObject is an abstract class for all game objects
	4/ CTexture is a wrapper class for ID3D10TEXTURE 
	
	NOTE: to create transparent background, download GIMP, then use Color to Alpha feature 
================================================================ */

#include <windows.h>

#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Bullet.h"
#include "Enemy.h"
#include "BulletManager.h"

#define WINDOW_CLASS_NAME L"Game Window"
#define MAIN_WINDOW_TITLE L"01 - Skeleton"
#define WINDOW_ICON_PATH L"brick.ico"

#define TEXTURE_PATH_BRICK L"brick.png"
#define TEXTURE_PATH_MARIO L"mario.png"

//Ship texture
#define TEXTURE_SHIP_UP L"Sprite\\tUp.png"

//Enemy texture
#define TEXTURE_ENEMY_DOWN L"Sprite\\Enemy\\wDown.png"

#define TEXTURE_PATH_BULLET L"Ball.png"
#define TEXTURE_PATH_MISC L"misc.png"

#define BACKGROUND_COLOR D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240


using namespace std;

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 100.0f
#define MARIO_START_VX 0.1f
#define MARIO_START_VY 0.1f
#define MARIO_WIDTH 14.0f
#define MARIO_HEIGHT 20.f

CMario* ship;
#define SHIP_START_X 50.0f
#define SHIP_START_Y 180.0f
#define SHIP_START_VX 0.0f
#define SHIP_START_VY 0.1f
#define SHIP_WIDTH 14.0f
#define SHIP_HEIGHT 5.f

CBrick *brick;
#define BRICK_X 8.0f
#define BRICK_Y 120.0f
#define BRICK_WIDTH 16.0f
#define BRICK_HEIGHT 16.f

CEnemy *enemy;
#define ENEMY_START_X 10.0f
#define ENEMY_START_Y 20.0f
#define ENEMY_START_VX 0.00f
#define ENEMY_START_VY 0.05f
#define ENEMY_WIDTH 14.0f
#define ENEMY_HEIGHT 20.f

LPTEXTURE texMario = NULL;
LPTEXTURE texBrick = NULL;
LPTEXTURE texShip = NULL;
LPTEXTURE texEnemy = NULL;
LPTEXTURE texMisc = NULL;
LPTEXTURE texBullet = NULL;

// Store key states
bool keyStates[256] = { false };
bool keyPressed[256] = { false }; // To track keys that were just pressed
bool keyHeld[256] = { false };    // To track keys being held down

vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> objectsProjectile;
vector<LPGAMEOBJECT> objectsToDelete;
extern BulletManager bulletManager;


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (!keyHeld[wParam]) {
			keyPressed[wParam] = true;  // Key was just pressed
		}
		keyHeld[wParam] = true;         // Key is now being held
		keyStates[wParam] = true;       // Keep your existing code
		break;
	case WM_KEYUP:
		keyHeld[wParam] = false;        // Key is no longer held
		keyStates[wParam] = false;      // Keep your existing code
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources. In this example, create a brick object and mario object
*/
void LoadResources()
{
	CGame * game = CGame::GetInstance();
	texBrick = game->LoadTexture(TEXTURE_PATH_BRICK);
	texShip = game->LoadTexture(TEXTURE_SHIP_UP);
	texMisc = game->LoadTexture(TEXTURE_PATH_MISC);
	texBullet = game->LoadTexture(TEXTURE_PATH_BULLET);
	texEnemy = game->LoadTexture(TEXTURE_ENEMY_DOWN);

	// Load a sprite sheet as a texture to try drawing a portion of a texture. See function Render 
	//texMisc = game->LoadTexture(MISC_TEXTURE_PATH);

	ship = new CMario(SHIP_START_X, SHIP_START_Y, SHIP_WIDTH, SHIP_HEIGHT, SHIP_START_VX, SHIP_START_VY, texShip);

	objects.push_back(ship);

	for (size_t i = 0; i < 2; i++)
	{
		objects.push_back(new CEnemy(ENEMY_START_X + i * 32.0f, ENEMY_START_Y, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_START_VX, ENEMY_START_VY, texEnemy));
	}

	for(int i = 0; i < 2; i++)		 
		objects.push_back(new CBrick(BRICK_X+i*BRICK_WIDTH, BRICK_Y, BRICK_WIDTH, BRICK_HEIGHT, texBrick));
	

	
	//int x = BRICK_X;
	//for(i)
	//	... new CGameObject(x,.... 
	//	x+=BRICK_WIDTH;
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
// In Update() function (in your main game file)
void Update(DWORD dt) {
	// Update all game objects
	for (auto obj : objects) {
		obj->Update(dt);
	}

	// Check for input
	ship->Update(dt, keyStates, keyPressed);

	// Update bullets
	bulletManager.Update(dt);

	// Temporary vector to track bullets to remove
	std::vector<CBullet*> bulletsToRemove;

	// Check for bullet collision
	for (size_t i = 0; i < bulletManager.bullets.size(); i++) {
		CBullet* bullet = bulletManager.bullets[i];

		for (auto obj : objects) {
			if (bullet->CheckCollision(obj)) {
				// Mark bullet for removal
				bullet->exist = false;
				bulletsToRemove.push_back(bullet);

				// Handle collision for the object
				obj->OnCollision(bullet);

				//Check if the object is an enemy that died
				//CEnemy* enemy = dynamic_cast<CEnemy*>(obj);
				//if (enemy && !enemy->IsAlive()) {
				//	objectsToDelete.push_back(enemy);
				//}

				// Break out of the inner loop once collision is detected
				break;
			}
		}
	}

	// Check for bullet-to-bullet collision
	for (size_t i = 0; i < bulletManager.bullets.size(); i++) {
		CBullet* bullet1 = bulletManager.bullets[i];
		for (size_t j = i + 1; j < bulletManager.bullets.size(); j++) {
			CBullet* bullet2 = bulletManager.bullets[j];
			if (bullet1->CheckCollision(bullet2)) {
				// Mark both bullets for removal
				bullet1->exist = false;
				bullet2->exist = false;
				bulletsToRemove.push_back(bullet1);
				bulletsToRemove.push_back(bullet2);
			}
		}
	}

	// Remove bullets that had collisions
	for (CBullet* bullet : bulletsToRemove) {
		auto it = std::find(bulletManager.bullets.begin(), bulletManager.bullets.end(), bullet);
		if (it != bulletManager.bullets.end()) {
			bulletManager.bullets.erase(it);
			delete bullet;
		}
	}

	// Check collisions between other game objects
	for (int i = 0; i < objects.size(); i++) {
		for (int j = i + 1; j < objects.size(); j++) {
			if (objects[i]->CheckCollision(objects[j])) {
				// Handle collision
				objects[i]->OnCollision(objects[j]);
				objects[j]->OnCollision(objects[i]);
			}
		}
	}

	// AFTER all collision checking is done, remove dead objects
	for (auto obj : objectsToDelete) {
		auto it = std::find(objects.begin(), objects.end(), obj);
		if (it != objects.end()) {
			objects.erase(it);
		}
		delete obj;
	}
	objectsToDelete.clear();
}

void Render() {
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL) {
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		// Render bullets
		bulletManager.Render();

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
) 
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame * game = CGame::GetInstance();
	game->Init(hWnd);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);


	LoadResources();

	Run();

	return 0;
}