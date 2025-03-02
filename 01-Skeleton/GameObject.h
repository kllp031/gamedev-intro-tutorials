#pragma once

#include <vector>
#include <Windows.h>
#include <d3dx10.h>

#include "Texture.h"

class CGameObject
{
protected: 
	float x; 
	float y;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object. 
	// For now, just a pointer to a single texture
	LPTEXTURE texture;			
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	float GetX() { return x; }
	float GetY() { return y; }

	CGameObject(float x = 0.0f, float y=0.0f, LPTEXTURE texture = NULL);

	virtual void Update(DWORD dt) = 0;
	virtual void Render();

	~CGameObject();
};
typedef CGameObject * LPGAMEOBJECT;

class CBrick : public CGameObject
{
public:
	CBrick(float x, float y, LPTEXTURE texture): CGameObject(x,y,texture) {}
	void Update(DWORD dt) {}; 
};

class CBullet : public CGameObject
{
public:
	float vx;
	float vy;
	bool exist = true;

	CBullet(float x, float y, float vx, float vy, LPTEXTURE texture)
		: CGameObject(x, y, texture), vx(vx), vy(vy) {}

	void Update(DWORD dt);
	void Render();
};

class CMario : public CGameObject
{
	float vx;
	float vy;
	std::vector<CBullet*> bullets; // Store bullets

public:
	CMario(float x, float y, float vx, float vy, LPTEXTURE texture)
		: CGameObject(x, y, texture), vx(vx), vy(vy) {}

	void Update(DWORD dt) override // Provide implementation for the pure virtual function
	{
		bool keyStates[256] = { false }; // Dummy keyStates array (replace with actual key input)
		bool keyPressed[] = { false };
		Update(dt, keyStates, keyPressed);
	}
	void Update(DWORD dt, bool keyStates[], bool keyPressed[]);
	void Shoot(); // Function to shoot a bullet
	void Render(); // Override render to draw bullets too
};

