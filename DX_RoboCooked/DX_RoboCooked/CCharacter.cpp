#include "stdafx.h"
#include "CCharacter.h"


CCharacter::CCharacter()
	: m_GameCenter(NULL)
	, m_pInteractCollision(nullptr)
	, m_ePlayerState(ePlayerState::E_None)
	, m_fSpeed(0.2f)
	, m_fRotY(0)
{
	m_vPosition = D3DXVECTOR3(0,0,0);
}

CCharacter::~CCharacter()
{
}
