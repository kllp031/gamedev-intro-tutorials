#include "tankEnemy.h"

#include "Enemy.h"
#include "BulletManager.h"
#include "Game.h"
#include "debug.h"

extern BulletManager bulletManager;

void CtankEnemy::Update(DWORD dt)
{
    // Don't do anything if not alive
    if (!IsAlive()) return;

    // Update timers
    shootTimer += dt;
    directionTimer += dt;

    // Check if it's time to change direction
    if (directionTimer >= directionInterval) {
        ChangeDirection();
        directionTimer = 0;
        directionInterval = 1000.0f + static_cast<float>(rand() % 3000); // New random interval
    }

    // Check if it's time to shoot
    if (shootTimer >= shootInterval) {
        Shoot();
        shootTimer = 0;
        shootInterval = 1000.0f + static_cast<float>(rand() % 2000); // New random interval
    }

    // Random movement
    RandomMove(dt);

    // Get screen boundaries
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

    // Keep enemy within screen bounds
    float leftLimit = GetWidth() / 2.0f;
    float rightLimit = BackBufferWidth - GetWidth() / 2.0f;
    float upperLimit = GetHeight() / 2.0f;
    float lowerLimit = BackBufferHeight - GetHeight() / 2.0f;

    // Check boundaries and bounce off edges
    if (x <= leftLimit) {
        x = leftLimit + 1.0f;
        vx = fabs(vx); // Move right
    }
    if (x >= rightLimit) {
        x = rightLimit - 1.0f;
        vx = -fabs(vx); // Move left
    }
    if (y <= upperLimit) {
        y = upperLimit + 1.0f;
        vy = fabs(vy); // Move down
    }
    if (y >= lowerLimit) {
        y = lowerLimit - 1.0f;
        vy = -fabs(vy); // Move up
    }

    // Update position
    x += vx * dt;
    y += vy * dt;
}

void CtankEnemy::RandomMove(DWORD dt)
{
    // Already handled in Update
}

void CtankEnemy::ChangeDirection()
{
    // Choose a random direction (0-3)
    int direction = rand() % 4;

    // Reset velocities
    vx = 0;
    vy = 0;

    // Set velocity based on direction
    switch (direction) {
    case 0: // Up
        vy = -movementSpeed;
        state = SHIP_STATE_UP;
        break;
    case 1: // Down
        vy = movementSpeed;
        state = SHIP_STATE_DOWN;
        break;
    case 2: // Left
        vx = -movementSpeed;
        state = SHIP_STATE_LEFT;
        break;
    case 3: // Right
        vx = movementSpeed;
        state = SHIP_STATE_RIGHT;
        break;
    }

    // Update texture based on state
    if (state == SHIP_STATE_UP)
        texture = texShipUp;
    else if (state == SHIP_STATE_DOWN)
        texture = texShipDown;
    else if (state == SHIP_STATE_LEFT)
        texture = texShipLeft;
    else if (state == SHIP_STATE_RIGHT)
        texture = texShipRight;

    DebugOut(L"[INFO] Enemy changed direction to %d\n", direction);
}

void CtankEnemy::Shoot()
{
    // Create a bullet
    LPTEXTURE bulletTexture = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET);

    // Shoot in the direction the enemy is facing
    CBullet* bullet = nullptr;

    if (state == SHIP_STATE_UP)
        bullet = new CBullet(x, y - 10.f, BULLET_WIDTH, BULLET_HEIGHT, 0.0f, -0.2f, bulletTexture);
    else if (state == SHIP_STATE_DOWN)
        bullet = new CBullet(x, y + 10.f, BULLET_WIDTH, BULLET_HEIGHT, 0.0f, 0.2f, bulletTexture);
    else if (state == SHIP_STATE_LEFT)
        bullet = new CBullet(x - 10.f, y, BULLET_WIDTH, BULLET_HEIGHT, -0.2f, 0.0f, bulletTexture);
    else if (state == SHIP_STATE_RIGHT)
        bullet = new CBullet(x + 10.f, y, BULLET_WIDTH, BULLET_HEIGHT, 0.2f, 0.0f, bulletTexture);

    // Add the bullet to the bullet manager
    bulletManager.AddBullet(bullet);

    DebugOut(L"[INFO] Enemy fired a bullet\n");
}