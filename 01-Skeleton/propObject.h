#pragma once
#include "GameObject.h"

class CpropObject : public CGameObject
{
protected:
	bool isDestroyed = false;
public:
	CpropObject(float x, float y, float width, float height, LPTEXTURE texture)
		: CGameObject(x, y, width, height, texture)
	{
	}
	virtual void Update(DWORD dt) override;
	virtual void Render() override;
	virtual void OnCollision(LPGAMEOBJECT other) override;
};