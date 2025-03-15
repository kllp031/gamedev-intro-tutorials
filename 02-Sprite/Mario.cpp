#include "Game.h"
#include "Mario.h"

void CMario::Update(DWORD dt)
{
    // Apply direction to velocity
    if (direction != 0 && isMoving)
        vx = direction * MARIO_WALKING_SPEED;
    else
        vx = 0;

    // Update position
    if(isMoving)
        x += vx * dt;

    // Ensure Mario stays within the screen boundaries
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    if (x <= 0) {
        x = 0;
    }
    else if (x >= BackBufferWidth - MARIO_WIDTH) {
        x = (float)(BackBufferWidth - MARIO_WIDTH);
    }
}

void CMario::Render()
{
    LPANIMATION ani;

    // Choose animation based on direction
    if (vx > 0) ani = CAnimations::GetInstance()->Get(500);
    else if (vx < 0) ani = CAnimations::GetInstance()->Get(501);
    else {
        // For idle state, use the last movement direction to determine which direction Mario faces
        if (direction > 0 && !isMoving) ani = CAnimations::GetInstance()->Get(502);
        else ani = CAnimations::GetInstance()->Get(503);
    }

    ani->Render(x, y);
}

void CMario::SetMoving(bool state)
{

	this->isMoving = state;
}

void CMario::SetDirection(int dir)
{
    this->direction = dir;
}

bool CMario::CheckCollision(LPGAMEOBJECT other)
{
    return CGameObject::CheckCollision(other);
}


void CMario::OnCollision(LPGAMEOBJECT other)
{
    DebugOut(L"[INFO] Something hit Mario.\n");
    CKoopa* koopa = dynamic_cast<CKoopa*>(other);

    if (koopa)
    {
        vx = 0;
        vy = 0.2f;
    }
}