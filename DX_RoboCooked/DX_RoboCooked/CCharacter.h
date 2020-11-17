#pragma once
#include "CGameScene.h"
class CGameScene;

enum class ePlayerState
{
	E_None, //기본상태
	E_Grab  //잡기상태
};

class CCharacter
{
protected:
	CGameScene*			m_GameCenter;
	ICollisionArea*		m_pInteractCollision;
	ePlayerState		m_ePlayerState;
public:
	CCharacter();
	~CCharacter();

	ICollisionArea* GetInteractCollsion() { return m_pInteractCollision; }
};

