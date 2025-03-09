#pragma once  
#include "GameObject.h"  

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
    //virtual void Update(DWORD dt) override;  
    //virtual void Render() override;  

    //// Check if this object collides with another object  
    //virtual bool CheckCollision(LPGAMEOBJECT other) {}  

    //// Handle collision with another object  
    //virtual void OnCollision(LPGAMEOBJECT other) {}  
};