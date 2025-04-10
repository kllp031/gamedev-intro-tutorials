#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == BRICK_TYPE_NORMAL)
		animations->Get(ID_ANI_BRICK_NORMAL)->Render(x, y);
	else if (type == BRICK_TYPE_FLOOR_BOTTOM_MIDDLE)
		animations->Get(ID_ANI_BRICK_FLOOR_BOTTOM_MIDDLE)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}