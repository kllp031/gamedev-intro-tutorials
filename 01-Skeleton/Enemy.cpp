#include "Enemy.h"
#include "Game.h"

#define TEXTURE_PATH_BULLET L"Ball.png"
#define BULLET_WIDTH 5.0f
#define BULLET_HEIGHT 5.0f

#define TANK_WIDTH 16
#define TANK_HEIGHT 16
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

    // Handle attack timer
    attackTimer += dt;
    if (attackTimer >= 2000)
        Shoot();

    // Update direction change timer
    directionChangeTimer += dt;
    if (directionChangeTimer >= directionChangeInterval) {
        ChangeDirection();
    }

    // Update position
    y += vy * dt;
    x += vx * dt;

    // Boundary checking with offset correction
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

    float leftLimit = TANK_WIDTH / 2.0f;
    float rightLimit = BackBufferWidth - TANK_WIDTH / 2.0f;
    float upperLimit = TANK_HEIGHT / 2.0f;
    float lowerLimit = BackBufferHeight - TANK_HEIGHT / 2.0f;

    if (x <= leftLimit) {
        x = leftLimit + 1.0f; // Ensure it's inside bounds
        ChangeDirection();
    }
    if (x >= rightLimit) {
        x = rightLimit - 1.0f; // Ensure it's inside bounds
        ChangeDirection();
    }
    if (y <= upperLimit) {
        y = upperLimit + 1.0f; // Ensure it's inside bounds
        ChangeDirection();
    }
    if (y >= lowerLimit) {
        y = lowerLimit - 1.0f; // Ensure it's inside bounds
        ChangeDirection();
    }
}

void CEnemy::Render()
{
    if (!isAlive) return;

    LPTEXTURE textureToRender = nullptr;

    switch (state)
    {
    case SHIP_STATE_UP:
        textureToRender = texTankUp;
        break;
    case SHIP_STATE_DOWN:
        textureToRender = texTankDown;
        break;
    case SHIP_STATE_LEFT:
        textureToRender = texTankLeft;
        break;
    case SHIP_STATE_RIGHT:
        textureToRender = texTankRight;
        break;
    }

    if (textureToRender)
    {
        // Render the enemy with the selected texture
        CGame::GetInstance()->Draw(x, y, textureToRender);
    }
}

void CEnemy::ChangeDirection() {
    // Random direction: 0-3 for UP, RIGHT, DOWN, LEFT
    int direction = rand() % 4;

    switch (direction) {
    case 0: // UP
        vx = 0;
        vy = -ENEMY_SPEED;
        state = SHIP_STATE_UP;
        break;
    case 1: // RIGHT
        vx = ENEMY_SPEED;
        vy = 0;
        state = SHIP_STATE_RIGHT;
        break;
    case 2: // DOWN
        vx = 0;
        vy = ENEMY_SPEED;
        state = SHIP_STATE_DOWN;
        break;
    case 3: // LEFT
        vx = -ENEMY_SPEED;
        vy = 0;
        state = SHIP_STATE_LEFT;
        break;
    }

    // Set a new random interval before the next direction change
    directionChangeInterval = DIRECTION_CHANGE_TIME;
    directionChangeTimer = 0;
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
	currentHealth = health;
    respawnTimer = 0;

    DebugOut(L"[INFO] Enemy respawned at X: %f, Y: %f\n", x, y);
}

void CEnemy::Die() {
    isAlive = false;
    respawnTimer = 0; // Reset the respawn timer

    DebugOut(L"[INFO] Enemy died. Will respawn in 3 seconds.\n");
}

void CEnemy::Shoot()
{
    CTank::Shoot();
    attackTimer = 0; // Reset attack timer
}

bool CEnemy::CheckCollision(LPGAMEOBJECT other)
{
    if (!isAlive) return false;

    return CGameObject::CheckCollision(other);
}

Rect CEnemy::GetBounds()
{
    if (!isAlive) return { 0, 0, 0, 0 };

    return CGameObject::GetBounds();
}

void CEnemy::OnCollision(LPGAMEOBJECT other)
{
    // Call the parent class's OnCollision
    CTank::OnCollision(other);

    // Update textures based on health
    if (currentHealth == 2)
    {
        texTankDown = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_R_DOWN);
        texTankLeft = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_R_LEFT);
        texTankRight = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_R_RIGHT);
        texTankUp = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_R_UP);
    }
    else if (currentHealth == 1)
    {
        texTankDown = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_W_DOWN);
        texTankLeft = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_W_LEFT);
        texTankRight = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_W_RIGHT);
        texTankUp = CGame::GetInstance()->LoadTexture(TEXTURE_SHIP_W_UP);
    }

    // Add a small push to help unstick the enemy
    switch (state) {
    case SHIP_STATE_UP:
        y -= 1.0f;
        break;
    case SHIP_STATE_DOWN:
        y += 1.0f;
        break;
    case SHIP_STATE_LEFT:
        x -= 1.0f;
        break;
    case SHIP_STATE_RIGHT:
        x += 1.0f;
        break;
    }
}