// 02-Sprite/Door.cpp
#include "Door.h"
#include "Animations.h"

void CDoor::Render()
{
    if (isActivated) {
        LPANIMATION ani;
        // Play the door animation only if it's activated (Mario is touching it)
        ani = CAnimations::GetInstance()->Get(530);  // Door top animation ID
        ani->Render(x, y - 8);
		ani = CAnimations::GetInstance()->Get(531);  // Door bottom animation ID
		ani->Render(x, y + 8);
    }
    else {
        // When not activated, just show the first frame
        LPANIMATION ani = CAnimations::GetInstance()->Get(530);  // Door top animation ID
        ani->RenderFrame(0, x, y - 8);  
		ani = CAnimations::GetInstance()->Get(531);  // Door bottom animation ID
		ani->RenderFrame(0, x, y + 8);  
    }
}

void CDoor::OnCollision(LPGAMEOBJECT other)
{
    // Activate the animation when Mario collides with the door
    CMario* mario = dynamic_cast<CMario*>(other);
    if (mario) {
        isActivated = true;
        lastCollisionTime = GetTickCount64();  // Record the time of collision
    }
}

void CDoor::Update(DWORD dt)
{
    // Check if Mario has walked away for more than 1 second
    if (isActivated && GetTickCount64() - lastCollisionTime > 1000) {
        isActivated = false;
        LPANIMATION ani;
        // Play the door animation only if it's activated (Mario is touching it)
        ani = CAnimations::GetInstance()->Get(530);  // Door top animation ID
		ani->Reset();
        ani = CAnimations::GetInstance()->Get(531);  // Door bottom animation ID
		ani->Reset();
    }
}
