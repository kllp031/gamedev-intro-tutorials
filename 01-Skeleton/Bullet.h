#pragma once
#include "GameObject.h"

class CBullet : public CGameObject
{
public:
	float vx;
	float vy;
	bool exist = true;

	CBullet(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
		: CGameObject(x, y, width, height, texture), vx(vx), vy(vy) {}
	
	void Update(DWORD dt) override;
	void Render() override;

	// Override collision handler
	void OnCollision(LPGAMEOBJECT other) override;
};