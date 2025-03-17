#pragma once

#include "MovingObject.h"
#include "Koopa.h"
#include "debug.h"

#include "Animation.h"
#include "Animations.h"

#define MARIO_WIDTH 14
#define MARIO_HEIGHT 27
#define MARIO_WALKING_SPEED 0.1f         // Reduced from 0.15f for more authentic feel
#define MARIO_JUMP_SPEED 0.28f            // Increased from 0.3f for better jump height
#define MARIO_JUMP_TIME 150                       
#define GRAVITY 0.0008f                  // Increased from 0.0015f for faster falling


class CMario : public CMovingObject
{
protected:
    int direction;
    bool isMoving;
    bool isJumping;
    bool isOnGround;  // Add this flag
    DWORD jumpTime;
    DWORD jumpTimer;

public:
    CMario(float x, float y, float width, float height, float vx, float vy)
        : CMovingObject(x, y, width, height, vx, vy) {
        direction = 1;  // Initialize direction to face right
        jumpTimer = 0; // Initialize jump timer to 0
        isMoving = false; // Initialize to not moving
        isJumping = false; // Initialize to not jumping
        isOnGround = false; // Initialize to not on ground
        jumpTime = MARIO_JUMP_TIME;
    }


	void Update(DWORD dt);
	void Render();

	//Mario's actions
	void Jump();

	bool CheckCollision(LPGAMEOBJECT other);

	//Collision handling
	void OnCollision(LPGAMEOBJECT other);

    void SetMoving(bool state);

    //Handle Jumping
	void SetJumping(bool state);
    void StopJump();
    bool isJumpHeld;  // Track if jump button is still being held

    void SetDirection(int dir);
};
