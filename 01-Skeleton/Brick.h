#pragma once
#include "GameObject.h"

class CBrick : public CGameObject
{
public:
	CBrick(float x, float y, float width, float height, LPTEXTURE texture)
		: CGameObject(x, y, width, height, texture){}
	void Update(DWORD dt) override {};

	// Override collision handler
	void OnCollision(LPGAMEOBJECT other) override;
};