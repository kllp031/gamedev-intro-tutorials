#pragma once
#include "Game.h"
#include "moveableObject.h"
#include "Bullet.h"
#include "BulletManager.h"
#include <vector>
#include <cstdlib> // For srand, rand
#include <ctime>

#define TEXTURE_PATH_BULLET L"Ball.png"
#define BULLET_WIDTH 5.0f
#define BULLET_HEIGHT 5.0f

#define SHIP_STATE_UP 1
#define SHIP_STATE_DOWN 2
#define SHIP_STATE_LEFT 3
#define SHIP_STATE_RIGHT 4

class CTank : public CMoveableObject
{
protected:
	int health;
	int currentHealth;

	bool isAlive;
	int state;
	LPTEXTURE texTankUp;
	LPTEXTURE texTankDown;
	LPTEXTURE texTankLeft;
	LPTEXTURE texTankRight;
public:
	CTank(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
		: CMoveableObject(x, y, width, height, vx, vy, texture)
	{
		health = 1;
		currentHealth = health;
		isAlive = true;
		state = SHIP_STATE_UP;

		texTankDown = NULL;
		texTankLeft = NULL;
		texTankRight = NULL;
		texTankUp = NULL;

		// Seed the random number generator (do this once in your game initialization)
		// In actual practice, you'd do this in your main game initialization, not here
		static bool seeded = false;
		if (!seeded) {
			srand(static_cast<unsigned int>(time(0)));
			seeded = true;
		}
	}
	bool IsAlive() const { return isAlive; }
	void TakeDamage(int damage) { currentHealth -= damage; }

	virtual void Shoot(); // Function to shoot a bullet
	virtual void Die();
	virtual void Respawn() { isAlive = true; }

	virtual void OnCollision(LPGAMEOBJECT other) override;
};