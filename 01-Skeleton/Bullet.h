#pragma once
#include "moveableObject.h"

class CBullet : public CMoveableObject
{
public:
	bool exist = true;

	CBullet(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
		: CMoveableObject(x, y, width, height, vx, vy, texture) {}
	
	void Update(DWORD dt) override;
	void Render() override;

	// Override collision handler
	void OnCollision(LPGAMEOBJECT other) override;
};