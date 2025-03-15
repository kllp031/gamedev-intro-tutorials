#pragma once

#include "MovingObject.h"
#include "Koopa.h"
#include "debug.h"

#include "Animation.h"
#include "Animations.h"

#define MARIO_WIDTH 14
#define MARIO_WALKING_SPEED 0.1f

class CMario : public CMovingObject
{
protected:
    int direction;  
	bool isMoving;

public:
	CMario(float x, float y, float width, float height, float vx, float vy)
		: CMovingObject(x, y, width, height, vx, vy) {
		direction = 1;  // Initialize direction to face right
		isMoving = false; // Initialize to not moving
	}


	void Update(DWORD dt);
	void Render();

	bool CheckCollision(LPGAMEOBJECT other);

	//Collision handling
	void OnCollision(LPGAMEOBJECT other);

    void SetMoving(bool state);
    void SetDirection(int dir);
};
