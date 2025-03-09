#include "Tank.h"

void CTank::Die()
{
    isAlive = false;
}

void CTank::OnCollision(LPGAMEOBJECT other)
{
	CBullet* bullet = dynamic_cast<CBullet*>(other);
	if (bullet)
	{
		TakeDamage(1);
		if (currentHealth <= 0)
		{
			Die();
		}
	}
}

BulletManager bulletManager;

void CTank::Shoot()
{
    // Use the bullet texture you loaded
    LPTEXTURE bulletTexture = CGame::GetInstance()->LoadTexture(TEXTURE_PATH_BULLET);

    // Create a bullet with proper texture and velocity
    CBullet* bullet = nullptr;
    if (state == SHIP_STATE_UP)
        bullet = new CBullet(x, y - 10.f, BULLET_WIDTH, BULLET_HEIGHT, 0.0f, -0.2f, bulletTexture);
    else if (state == SHIP_STATE_DOWN)
        bullet = new CBullet(x, y + 10.f, BULLET_WIDTH, BULLET_HEIGHT, 0.0f, 0.2f, bulletTexture);
    else if (state == SHIP_STATE_LEFT)
        bullet = new CBullet(x - 10.f, y, BULLET_WIDTH, BULLET_HEIGHT, -0.2f, 0.0f, bulletTexture);
    else if (state == SHIP_STATE_RIGHT)
        bullet = new CBullet(x + 10.f, y, BULLET_WIDTH, BULLET_HEIGHT, 0.2f, 0.0f, bulletTexture);

    bulletManager.AddBullet(bullet);
}