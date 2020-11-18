#include "stdafx.h"
#include "CCharacter.h"

#include "CGameScene.h"
#include "ICollisionArea.h"


CCharacter::CCharacter()
	: m_pInteractCollision(nullptr)
	, m_ePlayerState(EPlayerState::E_None)
	, m_fBaseSpeed(0.02f)
	, m_fSpeed(0)
	, m_fRotY(0)
	, m_vDirection(0,0,1)
	, m_vPosition(0, 0, 0)
	, m_vGrabPartsPosition(0, 1, 0)
	, m_pParts(NULL)
{
}

CCharacter::~CCharacter()
{
	SafeDelete(m_pInteractCollision);
}
