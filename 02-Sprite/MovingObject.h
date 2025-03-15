#pragma once
#include "GameObject.h"

class CMovingObject : public CGameObject
{
protected:
	float vx;
	float vy;
public:
	CMovingObject(float x, float y, float width, float height, float vx, float vy) :
		CGameObject(x, y, width, height), vx(vx), vy(vy) {
	}
};