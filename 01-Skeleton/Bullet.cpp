#include <d3dx9.h>
#include "Game.h"
#include "Bullet.h"
#include "Enemy.h"

void CBullet::Update(DWORD dt)
{
	if (!exist) return;

	x += vx * dt; // Move the bullet horizontally
    y += vy * dt; // Move the bullet upwards

    // Check if the ball goes off-screen
    if (y < 0 || y > CGame::GetInstance()->GetBackBufferHeight()) {
        exist = false; // Ball is off-screen, so it no longer exists
    }
	if (x < 0 || x > CGame::GetInstance()->GetBackBufferWidth()) {
		exist = false; // Ball is off-screen, so it no longer exists
	}
}

void CBullet::Render()
{
    if(!exist) return;
    CGameObject::Render();
}

void CBullet::OnCollision(LPGAMEOBJECT other)
{
    this->exist = false;
}
