#include "Game.h"
#include "Mario.h"

// First, modify Mario.cpp to implement variable jump height:

void CMario::Update(DWORD dt)
{
    // Apply direction to velocity
    if (direction != 0 && isMoving)
        vx = direction * MARIO_WALKING_SPEED;
    else
        vx = 0;

    // Handle jumping
    if (isJumping) {
        // Initial jump impulse
        if (jumpTimer == 0)
            vy = -MARIO_JUMP_SPEED;

        // Variable jump height based on how long button is held
        jumpTimer += dt;

        // Three-phase jump physics for smoother transitions
        if (isJumpHeld && jumpTimer < jumpTime * 0.8) {
			// Phase 1: increase upward velocity when button is held
            vy -= GRAVITY * dt * 0.4f;
        }
        else if (!isJumpHeld && vy < 0) {
            // Phase 2: Button released during rise - intermediate gravity
            vy += GRAVITY * dt * 0.7f;
        }
        else {
            // Phase 3: Peak and fall - full gravity
            vy += GRAVITY * dt;
        }
    }


    // End jump if jump time exceeds limit
    if (jumpTimer >= jumpTime)
    {
        isJumping = false;
        isJumpHeld = false;
        jumpTimer = 0;
    }

    // Apply gravity if not jumping
    if (!isJumping) {
        vy += GRAVITY * dt;
    }

    // Max fall speed (terminal velocity)
    if (vy > 0.3f)
        vy = 0.3f;

    // Update position
    x += vx * dt;
    y += vy * dt;

    // Ensure Mario stays within the screen boundaries
    int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
    int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();
    if (x <= 0) {
        x = 0;
    }
    else if (x >= BackBufferWidth - MARIO_WIDTH) {
        x = (float)(BackBufferWidth - MARIO_WIDTH);
    }
    if (y <= 0) {
        y = 0;
    }
    else if (y >= BackBufferHeight - MARIO_HEIGHT) {
        y = (float)(BackBufferHeight - MARIO_HEIGHT);
        isOnGround = true;  // Mario is on ground when at bottom of screen
        vy = 0;  // Stop falling
    }
    else {
        // Mario is not at the bottom of the screen, so not on ground
        // unless there's a collision with an object below
        isOnGround = false;
    }
}

void CMario::Jump()
{
    // Only allow jumping if Mario is on the ground and not already jumping
    if (isOnGround && !isJumping) {
        // Reset jump time to minimum for each new jump
        jumpTime = MARIO_JUMP_TIME;
        isJumping = true;
        isJumpHeld = true;
        jumpTimer = 0;
        isOnGround = false;  // Mario is no longer on ground when jumping
    }
}

void CMario::StopJump()
{
    // When jump button is released
    isJumpHeld = false;

    // If still in the rising phase of the jump, start falling faster
    if (isJumping && vy < 0) {
        vy *= 0.6f;  // Reduce upward velocity by half for a smoother transition
    }
}


void CMario::SetJumping(bool state)
{
    if (state) {
        Jump();
    }
    else {
        StopJump();
    }
}

void CMario::Render()
{
    LPANIMATION ani = nullptr; // Initialize ani to nullptr

    // Choose animation based on direction
    if (!isOnGround)
    {
        if (direction > 0) ani = CAnimations::GetInstance()->Get(504);
        else ani = CAnimations::GetInstance()->Get(505);
    }
	else if (isMoving)
    {
        if (vx > 0) ani = CAnimations::GetInstance()->Get(500);
        else if (vx < 0) ani = CAnimations::GetInstance()->Get(501);
    }
    else {
        // For idle state, use the last movement direction to determine which direction Mario faces
        if (direction > 0) ani = CAnimations::GetInstance()->Get(502);
        else ani = CAnimations::GetInstance()->Get(503);
    }

    // Ensure ani is not nullptr before calling Render
    if (ani != nullptr) {
        ani->Render(x, y);
    }
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