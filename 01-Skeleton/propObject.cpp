#include "propObject.h"

void CpropObject::Update(DWORD dt)
{
	x = x;
	y = y;
}

void CpropObject::Render()
{
	CGameObject::Render();
}

void CpropObject::OnCollision(LPGAMEOBJECT other)
{
	return;
}
