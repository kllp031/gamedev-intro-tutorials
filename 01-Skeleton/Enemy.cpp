#include <d3dx9.h>
#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include "debug.h"
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"

#define TEXTURE_PATH_BULLET L"Ball.png"
#define BULLET_WIDTH 10.0f
#define BULLET_HEIGHT 10.0f
#define MARIO_WIDTH 14
#define RESPAWN_TIME 3000 // 3 seconds in milliseconds

void CEnemy::Update(DWORD dt)
{
    if (!isAlive) {
        // Update respawn timer
        respawnTimer += dt;

        // Check if it's time to respawn
        if (respawnTimer >= RESPAWN_TIME) {
            Respawn();
        }
        return; // Don't update position while dead
    }

    attackTimer += dt;
    if (attackTimer >= 2000)
        Shoot();

    x += vx * dt;
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    if (x < MARIO_WIDTH / 2) vx = -vx;
    if (x > BackBufferWidth - MARIO_WIDTH / 2) vx = -vx;

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

void CEnemy::Render()
{
    if (!isAlive) return;  // Don't render dead enemies

    CGameObject::Render();

    for (CBullet* bullet : bullets) {
        bullet->Render();
    }
}

void CEnemy::Respawn()
{
    // Generate random X position within screen bounds
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    int margin = 50; // Keep away from edges

    // Calculate random X between margin and (screen width - margin)
    x = margin + (rand() % (BackBufferWidth - margin * 2));

    // Keep original Y position
    // Reset enemy state
    isAlive = true;
    respawnTimer = 0;

    DebugOut(L"[INFO] Enemy respawned at X: %f, Y: %f\n", x, y);
}

void CEnemy::Shoot()
{
    // Use the bullet texture you loaded
    LPTEXTURE bulletTexture = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET);

    // Create a bullet with proper texture and velocity
    CBullet* bullet = new CBullet(x, y + 20.f, BULLET_WIDTH, BULLET_HEIGHT, 0.0f, -0.05f, bulletTexture);
    bullets.push_back(bullet);

    attackTimer = 0;
}

void CEnemy::Die()
{
    isAlive = false;
    respawnTimer = 0; // Reset the respawn timer

    // Delete all bullets and clear the vector
    for (CBullet* bullet : bullets) {
        delete bullet;  // Free memory
    }
    bullets.clear(); // Remove all pointers from the vector

    DebugOut(L"[INFO] Enemy died. All bullets removed. Will respawn in 3 seconds.\n");
}


bool CEnemy::CheckCollision(LPGAMEOBJECT other)
{
    if (!isAlive) return false;

    return CGameObject::CheckCollision(other);
}

Rect CEnemy::GetBounds()
{
    if (!isAlive) return {0, 0, 0, 0};

    return CGameObject::GetBounds();
}

// In CEnemy::OnCollision
void CEnemy::OnCollision(LPGAMEOBJECT other)
{
    CBullet* bullet = dynamic_cast<CBullet*>(other);
    if (bullet)
    {
        this->Die();  // Mark enemy as dead

        // Add debug output
        //DebugOut(L"[INFO] Enemy hit by bullet! Enemy marked as dead.\n");
    }
}