#pragma once
#include "Tank.h"
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include "Bullet.h"
#include <vector>

// With a single fixed interval
#define DIRECTION_CHANGE_TIME 2000  // 3 seconds
#define ENEMY_SPEED 0.05f               // Base speed

#define SHIP_STATE_UP 1
#define SHIP_STATE_DOWN 2
#define SHIP_STATE_LEFT 3
#define SHIP_STATE_RIGHT 4

//White tank texture
#define TEXTURE_SHIP_W_UP L"Sprite\\Enemy\\wUp.png"
#define TEXTURE_SHIP_W_DOWN L"Sprite\\Enemy\\wDown.png"
#define TEXTURE_SHIP_W_LEFT L"Sprite\\Enemy\\wLeft.png"
#define TEXTURE_SHIP_W_RIGHT L"Sprite\\Enemy\\wRight.png"

//Red tank texture
#define TEXTURE_SHIP_R_UP L"Sprite\\Enemy\\rUp.png"
#define TEXTURE_SHIP_R_DOWN L"Sprite\\Enemy\\rDown.png"
#define TEXTURE_SHIP_R_LEFT L"Sprite\\Enemy\\rLeft.png"
#define TEXTURE_SHIP_R_RIGHT L"Sprite\\Enemy\\rRight.png"

//Green tank texture
#define TEXTURE_SHIP_G_UP L"Sprite\\Enemy\\gUp.png"
#define TEXTURE_SHIP_G_DOWN L"Sprite\\Enemy\\gDown.png"
#define TEXTURE_SHIP_G_LEFT L"Sprite\\Enemy\\gLeft.png"
#define TEXTURE_SHIP_G_RIGHT L"Sprite\\Enemy\\gRight.png"

class CEnemy : public CTank
{
private:
    DWORD respawnTimer;
    DWORD attackTimer;
    DWORD directionChangeTimer;
    DWORD directionChangeInterval;

public:
    // Update the constructor to accept 7 arguments
    CEnemy(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
        : CTank(x, y, width, height, vx, vy, texture)
    {
        isAlive = true;
        respawnTimer = 0;
        attackTimer = 0;
        state = SHIP_STATE_DOWN;

        // Add a small initial delay before first direction change
        directionChangeTimer = 0;
        directionChangeInterval = DIRECTION_CHANGE_TIME;

        CGame* game = CGame::GetInstance();

        health = (rand() % 3) + 1;
		currentHealth = health;

        switch (health)
        {
        case 1:
            texTankUp = game->LoadTexture(TEXTURE_SHIP_W_UP);
            texTankDown = game->LoadTexture(TEXTURE_SHIP_W_DOWN);
            texTankLeft = game->LoadTexture(TEXTURE_SHIP_W_LEFT);
            texTankRight = game->LoadTexture(TEXTURE_SHIP_W_RIGHT);
            break;
        case 2:
            texTankUp = game->LoadTexture(TEXTURE_SHIP_R_UP);
            texTankDown = game->LoadTexture(TEXTURE_SHIP_R_DOWN);
            texTankLeft = game->LoadTexture(TEXTURE_SHIP_R_LEFT);
            texTankRight = game->LoadTexture(TEXTURE_SHIP_R_RIGHT);
            break;
        case 3:
        default:
            texTankUp = game->LoadTexture(TEXTURE_SHIP_G_UP);
            texTankDown = game->LoadTexture(TEXTURE_SHIP_G_DOWN);
            texTankLeft = game->LoadTexture(TEXTURE_SHIP_G_LEFT);
            texTankRight = game->LoadTexture(TEXTURE_SHIP_G_RIGHT);
            break;
        }
    }

    bool CheckCollision(LPGAMEOBJECT other) override;
    virtual Rect GetBounds() override;

    void Respawn() override;
    void Die() override;
    void Shoot() override;

    void Update(DWORD dt) override;
    void Render();
    void ChangeDirection();

    void OnCollision(LPGAMEOBJECT other) override;
};
 