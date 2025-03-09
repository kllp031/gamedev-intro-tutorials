#pragma once
#include "Mario.h"

class CtankEnemy : public CMario
{
private:
    float shootTimer;        // Timer for random shooting
    float shootInterval;     // Time between shots
    float directionTimer;    // Timer for random direction changes
    float directionInterval; // Time between direction changes
    float movementSpeed;     // Speed of the enemy

public:
    CEnemy(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
        : CMario(x, y, width, height, vx, vy, texture)
    {
        // Initialize timers with random values
        shootTimer = 0;
        shootInterval = 1000.0f + static_cast<float>(rand() % 2000); // Random interval between 1-3 seconds
        directionTimer = 0;
        directionInterval = 1000.0f + static_cast<float>(rand() % 3000); // Random interval between 1-4 seconds
        movementSpeed = 0.05f + (static_cast<float>(rand()) / RAND_MAX) * 0.05f; // Random speed between 0.05-0.1
    }

    // Override the Update method to implement random movement and shooting
    void Update(DWORD dt) override;

    // Implement random movement
    void RandomMove(DWORD dt);

    // Randomly change direction
    void ChangeDirection();

    // Override shoot method to make it shoot in random directions
    void Shoot() override;
};