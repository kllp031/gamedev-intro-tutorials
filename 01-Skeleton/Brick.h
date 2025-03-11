#pragma once
#include "propObject.h"

class CBrick : public CpropObject
{
public:
    CBrick(float x, float y, float width, float height, LPTEXTURE texture)
        : CpropObject(x, y, width, height, texture) {
    }
    void Update(DWORD dt) override;

    // Override collision handler
    void OnCollision(LPGAMEOBJECT other) override;
};
