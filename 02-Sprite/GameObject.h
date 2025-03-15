#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "debug.h"


using namespace std;

// Define a simple rectangle structure for collision bounds
struct Rect {
    float left, top, right, bottom;
};

// Forward declaration
class CGameObject;

// Define the typedef 
typedef CGameObject* LPGAMEOBJECT;

class CGameObject
{
protected:
    float x;
    float y;
    float width;    // Add width property
    float height;   // Add height property
public:
    CGameObject(float x = 0.0f, float y = 0.0f, int width = 0, int height = 0);

    void SetPosition(float x, float y) { this->x = x, this->y = y; }
    float GetX() { return x; }
    float GetY() { return y; }

    // Get the collision bounds of this object
    virtual Rect GetBounds() {
        return {
            x - width / 2,   // left
            y - height / 2,  // top
            x + width / 2,   // right
            y + height / 2   // bottom
        };
    }

    // Check if this object collides with another object
    virtual bool CheckCollision(LPGAMEOBJECT other);

    // Handle collision with another object
    virtual void OnCollision(LPGAMEOBJECT other) {};


    virtual void Update(DWORD dt) = 0;
    virtual void Render() = 0;
};

