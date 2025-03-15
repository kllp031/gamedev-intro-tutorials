#pragma once
#include "propObject.h"

// Add a simple health or destroyable flag to CBrick
class CBrick : public CpropObject {

public:
    CBrick(float x, float y, float width, float height, LPTEXTURE texture)
        : CpropObject(x, y, width, height, texture) {
    }

    void Update(DWORD dt) override;
    void OnCollision(LPGAMEOBJECT other) override;

    // Method to mark brick for destruction
    void Destroy();

    // Check if brick is destroyed
    bool IsDestroyed() const { return isDestroyed; }
};

