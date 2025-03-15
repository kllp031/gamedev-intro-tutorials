#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "debug.h"

class CDoor : public CGameObject {
private:
    bool isActivated = false;         // Whether the door animation is playing
	bool isOpened = false;            // Whether the door is opened
    ULONGLONG lastCollisionTime = 0;  // Time of last collision with Mario

public:
    CDoor(float x, float y, float width, float height) : CGameObject(x, y, width, height) {}
    void Render();
    void Update(DWORD dt);

    void OnCollision(LPGAMEOBJECT other);
};
