#include "stdafx.h"
#include "CCharacter.h"


CCharacter::CCharacter()
	: m_GameCenter(NULL)
	, m_pInteractCollision(nullptr)
	, m_ePlayerState(ePlayerState::E_None)
{
}

CCharacter::~CCharacter()
{
}