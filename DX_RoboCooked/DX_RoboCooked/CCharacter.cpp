#include "stdafx.h"
#include "CCharacter.h"

#include "CGameScene.h"
#include "ICollisionArea.h"


CCharacter::CCharacter()
	: m_pInteractCollision(nullptr)
	, m_ePlayerState(EPlayerState::E_None)
	, m_fBaseSpeed(0.02f)
	, m_fSpeed(0)
	, m_vGrabPartsPosition(0, 1, 0)
	, m_pParts(NULL)
	, m_isGrabCooltime(false)
{
}

CCharacter::~CCharacter()
{
	SafeDelete(m_pInteractCollision);
}
