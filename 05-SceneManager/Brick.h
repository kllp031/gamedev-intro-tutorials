#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_NORMAL 10001
#define ID_ANI_BRICK_FLOOR_BOTTOM_MIDDLE 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_TYPE_NORMAL 0
#define BRICK_TYPE_FLOOR_BOTTOM_LEFT 1
#define BRICK_TYPE_FLOOR_BOTTOM_MIDDLE 2
#define BRICK_TYPE_FLOOR_BOTTOM_RIGHT 3
#define BRICK_TYPE_FLOOR_TOP_LEFT 4
#define BRICK_TYPE_FLOOR_TOP_MIDDLE 5
#define BRICK_TYPE_FLOOR_TOP_RIGHT 6

class CBrick : public CGameObject {
protected:
	int type;
public:
	CBrick(float x, float y, int type) : CGameObject(x, y), type(type){}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};