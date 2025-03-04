// In GameObject.cpp
#include <d3dx9.h>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"

CGameObject::CGameObject(float x, float y, int width, int height, LPTEXTURE tex)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->texture = tex;
}

void CGameObject::Render()
{
    if (texture == NULL) return; // Prevent null pointer access
    CGame::GetInstance()->Draw(x, y, texture);
}

// Implement the collision detection method
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

CGameObject::~CGameObject()
{
    if (texture != NULL) delete texture;
}