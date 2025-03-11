#include "moveableObject.h"

void CMoveableObject::OnCollision(LPGAMEOBJECT other)
{
    // Temporarily set velocity to 0 for the collision resolution
    float tempVx = vx;
    float tempVy = vy;
    vx = 0;
    vy = 0;

    // Get the bounds of both objects
    Rect thisBounds = this->GetBounds();
    Rect otherBounds = other->GetBounds();

    // Calculate overlap on each axis
    float overlapX = 0;
    float overlapY = 0;

    // Calculate horizontal overlap
    if (x < other->GetX()) {
        // This object is to the left of the other object
        overlapX = thisBounds.right - otherBounds.left;
    }
    else {
        // This object is to the right of the other object
        overlapX = otherBounds.right - thisBounds.left;
    }

    // Calculate vertical overlap
    if (y < other->GetY()) {
        // This object is above the other object
        overlapY = thisBounds.bottom - otherBounds.top;
    }
    else {
        // This object is below the other object
        overlapY = otherBounds.bottom - thisBounds.top;
    }

    // Move in the direction of minimum overlap (to avoid getting stuck)
    if (overlapX < overlapY) {
        // Move horizontally (left or right)
        if (x < other->GetX()) {
            x -= overlapX + 1.0f;  // Move left with a little extra space
        }
        else {
            x += overlapX + 1.0f;  // Move right with a little extra space
        }
    }
    else {
        // Move vertically (up or down)
        if (y < other->GetY()) {
            y -= overlapY + 1.0f;  // Move up with a little extra space
        }
        else {
            y += overlapY + 1.0f;  // Move down with a little extra space
        }
    }

    // For CMario objects, keep velocity at 0
    // For CEnemy objects, we'll restore velocity in the CEnemy::OnCollision method
    // Do not restore velocity here to allow derived classes to control this behavior
}