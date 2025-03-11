#pragma once
#include <Windows.h>
#include <d3dx10.h>
#include "Texture.h"
#include "debug.h"

// Forward declaration
class CGameObject;

// Define the typedef 
typedef CGameObject* LPGAMEOBJECT;

// Define a simple rectangle structure for collision bounds
struct Rect {
    float left, top, right, bottom;
};

class CGameObject
{
protected:
    float x;
    float y;
    float width;    // Add width property
    float height;   // Add height property
    LPTEXTURE texture;

public:

    CGameObject(float x = 0.0f, float y = 0.0f, int width = 0, int height = 0, LPTEXTURE texture = NULL);

    void SetPosition(float x, float y) { this->x = x, this->y = y; }
    float GetX() { return x; }
    float GetY() { return y; }

    // Add methods to get/set object dimensions
    void SetSize(float width, float height) { this->width = width; this->height = height; }
    int GetWidth() { return width; }
    int GetHeight() { return height; }

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
    virtual void Render();
    ~CGameObject();
};