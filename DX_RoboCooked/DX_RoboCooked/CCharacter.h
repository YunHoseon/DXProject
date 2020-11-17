#pragma once
#include "CGameScene.h"
class CGameScene;

class CCharacter
{

protected:
	CGameScene*			m_GameCenter;
	ICollisionArea*		m_pInteractCollision;
public:
	CCharacter();
	~CCharacter();

	
	ICollisionArea* GetInteractCollsion() { return m_pInteractCollision; }
};

