#include <d3dx9.h>
#include <iostream>
#include "debug.h"
#include "Game.h"
#include "Mario.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletManager.h"

#define MARIO_VX 0.1f
#define MARIO_YX 0.1f
#define MARIO_WIDTH 16.f
#define MARIO_HEIGHT 16.f

void CMario::Update(DWORD dt)
{
    bool keyStates[256] = { false }; // Dummy keyStates array
    bool keyPressed[256] = { false };
    Update(dt, keyStates, keyPressed);
}

void CMario::Update(DWORD dt, bool keyStates[], bool keyPressed[])
{
    // Check for respawn;
    if (keyPressed['F']) Respawn();
    keyPressed['F'] = false;

    if (!isAlive) return;

    // Handle movement input
    if (keyStates['A']) {
        vx = -MARIO_VX;  // Move left
        state = SHIP_STATE_LEFT;
        texture = texTankLeft;
    }
    else if (keyStates['D']) {
        vx = MARIO_VX;  // Move right
        state = SHIP_STATE_RIGHT;
        texture = texTankRight;
    }
	else if (keyStates['W']) {
		vy = -MARIO_VX;  // Move up
		state = SHIP_STATE_UP;
        texture = texTankUp;
	}
	else if (keyStates['S']) {
		vy = MARIO_VX;  // Move down
		state = SHIP_STATE_DOWN;
		texture = texTankDown;
	}
	else {
		vx = 0; // Stop if no key is pressed
		vy = 0; // Stop if no key is pressed
	}

    x += vx * dt; // Update x
	y += vy * dt; // Update y

    // Get screen width
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

    // Fix lagging issue at boundaries
    float leftLimit = MARIO_WIDTH / 2.0f;
    float rightLimit = BackBufferWidth - MARIO_WIDTH / 2.0f;
	float upperLimit = MARIO_HEIGHT / 2.0f;
	float lowerLimit = BackBufferHeight - MARIO_HEIGHT / 2.0f;

    if (x <= leftLimit) {
        x = leftLimit + 1.0f; // Ensure it's inside bounds
        vx = fabs(vx); // Move right
    }
    if (x >= rightLimit) {
        x = rightLimit - 1.0f; // Ensure it's inside bounds
        vx = -fabs(vx); // Move left
    }
    if (y <= upperLimit) {
        y = upperLimit + 1.0f; // Ensure it's inside bounds
        vy = fabs(vy); // Move down
    }
    if (y >= lowerLimit) {
        y = lowerLimit - 1.0f; // Ensure it's inside bounds
        vy = -fabs(vy); // Move up
    }

    // Check if spacebar is pressed and shoot a bullet
    if (keyPressed[' ']) Shoot();
    keyPressed[' '] = false;
}

void CMario::Render()
{
    if (!isAlive) return;

    CGameObject::Render(); // Render Mario
}

bool CMario::CheckCollision(LPGAMEOBJECT other)
{
    if (!isAlive) return false;

    return CGameObject::CheckCollision(other);
}

Rect CMario::GetBounds()
{
    if (!isAlive) return { 0, 0, 0, 0 };

    return CGameObject::GetBounds();
}

void CMario::Respawn()
{
    DebugOut(L"[INFO] Hero never die!!.\n");
    isAlive = true;
}

void CMario::OnCollision(LPGAMEOBJECT other)
{
    // Check what type of object we collided with
    // For example, if it's an enemy:
    DebugOut(L"[INFO] Something hit Mario.\n");
	CTank::OnCollision(other);
}
