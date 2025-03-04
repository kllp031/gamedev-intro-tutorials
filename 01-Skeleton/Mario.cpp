#include <d3dx9.h>
#include <iostream>
#include "debug.h"
#include "Game.h"
#include "Mario.h"
#include "Enemy.h"
#include "Bullet.h"

#define TEXTURE_PATH_BULLET L"Ball.png"
#define MARIO_VX 0.1f
#define MARIO_WIDTH 14.f
#define BULLET_WIDTH 10.0f
#define BULLET_HEIGHT 10.0f

void CMario::Update(DWORD dt, bool keyStates[], bool keyPressed[])
{
    // Check for respawn;
    if (keyPressed['F']) Respawn();
    keyPressed['F'] = false;

    if (!isAlive) return;

    // Handle movement input
    if (keyStates['A']) vx = -MARIO_VX;  // Move left
    else if (keyStates['D']) vx = MARIO_VX;  // Move right
    else vx = 0;  // Stop if no key is pressed
    x += vx * dt; // Update position

    // Get screen width
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();

    // Fix lagging issue at boundaries
    float leftLimit = MARIO_WIDTH / 2.0f;
    float rightLimit = BackBufferWidth - MARIO_WIDTH / 2.0f;

    if (x <= leftLimit) {
        x = leftLimit + 1.0f; // Ensure it's inside bounds
        vx = fabs(vx); // Move right
    }
    if (x >= rightLimit) {
        x = rightLimit - 1.0f; // Ensure it's inside bounds
        vx = -fabs(vx); // Move left
    }

    // Check if spacebar is pressed and shoot a bullet
    if (keyPressed[' ']) Shoot();
    keyPressed[' '] = false;

    // Update bullets
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i]->Update(dt);
        if (!bullets[i]->exist) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
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

void CMario::Die()
{
    isAlive = false;
    DebugOut(L"[INFO] Mario died.\n");

    // Delete all bullets and clear the vector
    for (CBullet* bullet : bullets) {
        delete bullet;  // Free memory
    }
    bullets.clear(); // Remove all pointers from the vector
}

void CMario::Respawn()
{
    DebugOut(L"[INFO] Hero never die!!.\n");
    isAlive = true;
}

void CMario::Update(DWORD dt)
{
    bool keyStates[256] = { false }; // Dummy keyStates array
    bool keyPressed[256] = { false };
    Update(dt, keyStates, keyPressed);
}

void CMario::Render()
{
    if (!isAlive) return;

    CGameObject::Render(); // Render Mario

    // Render bullets
    for (CBullet* bullet : bullets) {
        bullet->Render();
    }
}

void CMario::OnCollision(LPGAMEOBJECT other)
{
    // Check what type of object we collided with
    // For example, if it's an enemy:
    DebugOut(L"[INFO] Something hit Mario.\n");
    CBullet* bullet = dynamic_cast<CBullet*>(other);
    if (bullet)
    {
        Die();
    }
}

void CMario::Shoot()
{
    // Use the bullet texture you loaded
    LPTEXTURE bulletTexture = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET);
    // Create a bullet with proper texture and velocity
    CBullet* bullet = new CBullet(x, y - 10.f, BULLET_WIDTH, BULLET_HEIGHT, 0.0f, 0.05f, bulletTexture);
    bullets.push_back(bullet);
}
