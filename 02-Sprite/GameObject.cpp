#include "GameObject.h"

CGameObject::CGameObject(float x, float y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool CGameObject::CheckCollision(LPGAMEOBJECT other)
{
    Rect thisBounds = this->GetBounds();
    Rect otherBounds = other->GetBounds();

    // Check if the two rectangles intersect
    return !(thisBounds.right < otherBounds.left ||
        thisBounds.left > otherBounds.right ||
        thisBounds.bottom < otherBounds.top ||
        thisBounds.top > otherBounds.bottom);
}
