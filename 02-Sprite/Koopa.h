#pragma once
#include "MovingObject.h"
#include "Animation.h"
#include "Animations.h"

class CKoopa : public CMovingObject
{
protected:
	int direction;
	bool isMoving;
public:
	CKoopa(float x, float y, float width, float height, float vx, float vy)
		: CMovingObject(x, y, width, height, vx, vy) {
		direction = 1;  // Start moving right
		isMoving = true; // Start moving
	}

	void Update(DWORD dt);
	void Render();

	void SetMoving(bool state);
	void SetDirection(int dir);
};