#include <d3dx9.h>
#include <iostream>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#define TEXTURE_PATH_BULLET L"Ball.png"

/*
	Initialize game object 
*/
CGameObject::CGameObject(float x, float y, LPTEXTURE tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void CGameObject::Render()
{
    if (texture == NULL) return; // Prevent null pointer access
    CGame::GetInstance()->Draw(x, y, texture);
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14

void CMario::Update(DWORD dt, bool keyStates[], bool keyPressed[])
{
    // Handle movement input
    if (keyStates['A']) vx = -MARIO_VX;  // Move left
    else if (keyStates['D']) vx = MARIO_VX;  // Move right
    else vx = 0;  // Stop if no key is pressed

    x += vx * dt; // Update position

    // Get screen boundaries
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    if (x < MARIO_WIDTH / 2) x = MARIO_WIDTH / 2;
    if (x > BackBufferWidth - MARIO_WIDTH / 2) x = (float)(BackBufferWidth - MARIO_WIDTH / 2);

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

void CMario::Render()
{
    CGameObject::Render(); // Render Mario

    // Render bullets
    for (CBullet* bullet : bullets) {
        bullet->Render();
    }
}

void CMario::Shoot()
{
    // Use the bullet texture you loaded
    LPTEXTURE bulletTexture = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET);

    // Create a bullet with proper texture and velocity
    CBullet* bullet = new CBullet(x, y - 10, 0.0f, 0.05f, bulletTexture);
    bullets.push_back(bullet);

    std::cout << "PEW" << std::endl;
}

void CBullet::Update(DWORD dt)
{
    y -= vy * dt; // Move the bullet upwards

    // Check if the ball goes off-screen
    if (y < 0 || y > CGame::GetInstance()->GetBackBufferHeight()) {
        exist = false; // Ball is off-screen, so it no longer exists
    }
}

void CBullet::Render()
{
    CGameObject::Render();
}
