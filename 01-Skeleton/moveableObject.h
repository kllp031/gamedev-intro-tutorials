#pragma once  
#include "GameObject.h"  
#include "Game.h"

class CMoveableObject : public CGameObject
{
protected:
    float vx;
    float vy;
public:
    CMoveableObject(float x, float y, float width, float height, float vx, float vy, LPTEXTURE texture)
        : CGameObject(x, y, width, height, texture), vx(vx), vy(vy)
    {
    }

    // Handle collision with another object  
    virtual void OnCollision(LPGAMEOBJECT other);
};