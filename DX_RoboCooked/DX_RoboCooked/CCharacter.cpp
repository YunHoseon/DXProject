#include "stdafx.h"
#include "CCharacter.h"

#include "CGameScene.h"
#include "ICollisionArea.h"


CCharacter::CCharacter()
	: m_pInteractCollision(nullptr)
	, m_ePlayerState(EPlayerState::E_None)
	, m_vGrabPartsPosition(0, 1, 0)
	, m_pParts(NULL)
	, m_elapsedTime(0)
	, m_isGrabCooltime(false)
{
	m_fBaseSpeed = 0.001f;
	m_fSpeed = m_fBaseSpeed;
}

CCharacter::~CCharacter()
{
	SafeDelete(m_pInteractCollision);
}
