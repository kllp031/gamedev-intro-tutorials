// 02-Sprite/Koopa.cpp
#include "Koopa.h"

void CKoopa::Update(DWORD dt)
{
    if (isMoving)
        x += vx * direction * dt;

    float Width = CGame::GetInstance()->GetBackBufferWidth();

    // Don't let Koopa go completely off screen before changing direction
    if (x <= 0) {
        x = 0;  // Keep it at the edge
        direction = 1;  // Change direction to right
    }
    else if (x >= Width - width) {  // Use the width property
        x = Width - width;  // Keep it at the edge
        direction = -1;  // Change direction to left
    }
}


void CKoopa::Render()
{
	LPANIMATION ani;

	// Use animation 530 for walking
	if (direction == 1)
		ani = CAnimations::GetInstance()->Get(521);
	else
	{
		ani = CAnimations::GetInstance()->Get(520);
	}
	

	ani->Render(x, y);
}

void CKoopa::SetMoving(bool state)
{
	isMoving = state;
}

void CKoopa::SetDirection(int dir)
{
	direction = dir;
}
