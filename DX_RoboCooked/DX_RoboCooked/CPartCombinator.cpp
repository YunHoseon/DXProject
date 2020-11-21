#include "stdafx.h"
#include "CPartCombinator.h"
#include "CActor.h"
#include "IInteractCenter.h"



CPartCombinator::CPartCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType , float fAngle, D3DXVECTOR3 vPosition)
	: m_eLevel(eType), m_eCombinatorState(ECombinatorState::E_LoadPossible), m_CombinatorTexture(nullptr),
	  m_pPartsInteractCollision(NULL)
	  , m_vOnCombinatorPosition(0, 0, 0)
	  , m_pParts(NULL), m_isCombine(false) , m_fElapsedTime(0) , m_fCombineTime(0)
{
}


CPartCombinator::~CPartCombinator()
{
	
}
