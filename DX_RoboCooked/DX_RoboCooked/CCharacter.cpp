#include "stdafx.h"
#include "CCharacter.h"


CCharacter::CCharacter()
	: m_GameCenter(NULL)
	, m_pInteractCollision(nullptr)
	, m_fSpeed(0.02f)
	, m_fRotY(0.0f)
{
}


CCharacter::~CCharacter()
{
}
