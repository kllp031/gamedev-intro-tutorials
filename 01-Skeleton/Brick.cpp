#include "Brick.h"
#include "Bullet.h"
void CBrick::Update(DWORD dt)
{
	CpropObject::Update(dt);
}

void CBrick::OnCollision(LPGAMEOBJECT other) {
    // Check if collision is with a bullet
    CBullet* bullet = dynamic_cast<CBullet*>(other);
    if (bullet) {
        // Decide if the bullet should destroy the brick
        // For example, you might have special bullet types
        Destroy();
    }
}

void CBrick::Destroy()
{
    isDestroyed = true;
    MarkForDeletion(); // Connect to the base class flag
}

