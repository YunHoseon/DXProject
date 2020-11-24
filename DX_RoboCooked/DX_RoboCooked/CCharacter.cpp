#include "stdafx.h"
#include "CCharacter.h"

#include "CGameScene.h"
#include "ICollisionArea.h"


CCharacter::CCharacter()
	: m_pInteractCollision(nullptr)
	, m_ePlayerState(ePlayerState::None)
	, m_vGrabPartsPosition(0, 1, 0)
	, m_pParts(NULL)
	, m_isGrabCooltime(false)
{
	m_fBaseSpeed = 0.02f;
	m_fSpeed = m_fBaseSpeed;
}

CCharacter::~CCharacter()
{
	SafeDelete(m_pInteractCollision);
}
