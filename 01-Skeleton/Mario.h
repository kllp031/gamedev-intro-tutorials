#pragma once
#include "Tank.h"
#include "Bullet.h"
#include <vector>
#include <cstdlib> // For srand, rand
#include <ctime>   // For time

#define SHIP_STATE_UP 1
#define SHIP_STATE_DOWN 2
#define SHIP_STATE_LEFT 3
#define SHIP_STATE_RIGHT 4

//Ship texture
#define TEXTURE_SHIP_UP L"Sprite\\tUp.png"
#define TEXTURE_SHIP_DOWN L"Sprite\\tDown.png"
#define TEXTURE_SHIP_LEFT L"Sprite\\tLeft.png"
#define TEXTURE_SHIP_RIGHT L"Sprite\\tRight.png"

class CMario : public CTank
{
private:
public:
    CMario(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
        : CTank(x, y, width, height, vx, vy, texture)
    {
        isAlive = true;
        state = SHIP_STATE_UP;


        CGame* game = CGame::GetInstance();
        texTankUp = game->LoadTexture(TEXTURE_SHIP_UP);
        texTankDown = game->LoadTexture(TEXTURE_SHIP_DOWN);
        texTankLeft = game->LoadTexture(TEXTURE_SHIP_LEFT);
        texTankRight = game->LoadTexture(TEXTURE_SHIP_RIGHT);
    }

    void Update(DWORD dt) override; // Implement the pure virtual function
    void Update(DWORD dt, bool keyStates[], bool keyPressed[]);
    void Render() override; // Override render to draw bullets too

    void Respawn() override;

    bool CheckCollision(LPGAMEOBJECT other) override;
    virtual Rect GetBounds() override;
    // Override collision handler
    void OnCollision(LPGAMEOBJECT other) override;
};
