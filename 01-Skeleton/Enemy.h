#pragma once
#include "GameObject.h"
#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include "Bullet.h"
#include <vector>

class CEnemy : public CGameObject
{
private:
    float vx;
    float vy;
    bool isAlive;
    DWORD respawnTimer; // Time counter for respawn
    DWORD attackTimer;
    
public:
    std::vector<CBullet*> bullets; // Store bullets

    // Make sure your constructor initializes these values
    CEnemy(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
        : CGameObject(x, y, width, height, texture), vx(vx), vy(vy)
    {
        isAlive = true;
        respawnTimer = 0;
        attackTimer = 0;
        
        // Seed the random number generator (do this once in your game initialization)
        // In actual practice, you'd do this in your main game initialization, not here
        static bool seeded = false;
        if (!seeded) {
            srand(static_cast<unsigned int>(time(0)));
            seeded = true;
        }
    }

    bool IsAlive() const { return isAlive; }
    void Die();

    bool CheckCollision(LPGAMEOBJECT other) override;
    virtual Rect GetBounds() override;

    void Respawn();

    void Shoot();

	void Update(DWORD dt) override; // Implement the pure virtual function
    void Render();

	// Override collision handler
	void OnCollision(LPGAMEOBJECT other) override;
};