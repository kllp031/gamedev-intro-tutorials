#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include <vector>

class CMario : public CGameObject
{
private:
	float vx;
	float vy;
	bool isAlive;

public:
	std::vector<CBullet*> bullets; // Store bullets

	CMario(float x, float y, float width, float height,float vx, float vy, LPTEXTURE texture)
		: CGameObject(x, y, width, height, texture), vx(vx), vy(vy) 
	{
		isAlive = true;

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
	void Respawn();

	bool CheckCollision(LPGAMEOBJECT other) override;
	virtual Rect GetBounds() override;

	void Update(DWORD dt) override; // Implement the pure virtual function
	void Update(DWORD dt, bool keyStates[], bool keyPressed[]);
	void Shoot(); // Function to shoot a bullet
	void Render() override; // Override render to draw bullets too

	// Override collision handler
	void OnCollision(LPGAMEOBJECT other) override;
};