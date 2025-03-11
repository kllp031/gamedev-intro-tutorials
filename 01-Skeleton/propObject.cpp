#include "propObject.h"

void CpropObject::Update(DWORD dt)
{
	//doesnt update
}

void CpropObject::Render()
{
	CGameObject::Render();
}

void CpropObject::OnCollision(LPGAMEOBJECT other)
{
	return;
}
