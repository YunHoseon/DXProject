#include "stdafx.h"
#include "CPartAutoCombinator.h"
#include "CBoxCollision.h"
#include "CSphereCollision.h"
#include "CParts.h"
#include "IInteractCenter.h"
#include "CCharacter.h"

CPartAutoCombinator::CPartAutoCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition):
	CPartCombinator(pInteractCenter, eType, fAngle, vPosition)
{
	switch (m_eLevel)
	{
	case eCombinatorPartsLevel::ONE:
		m_nMaxPartsCount = 2;
		if (!m_pSMesh)
			m_pSMesh = g_pStaticMeshManager->GetStaticMesh("CombinatorLevel1");
		break;
	case eCombinatorPartsLevel::TWO:
		m_nMaxPartsCount = 3;
		if (!m_pSMesh)
			m_pSMesh = g_pStaticMeshManager->GetStaticMesh("CombinatorLevel2");
		break;
	}
	Setup(fAngle, vPosition);
}


CPartAutoCombinator::~CPartAutoCombinator()
{
}

void CPartAutoCombinator::Update()
{
	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadImpossible &&
		m_eCombinatorActionState == eCombinatorActionState::Usable)
		CombineParts();
	
	if(m_isCombine && m_pParts == nullptr)
		DischargeParts();

	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadPossible && m_pParts == nullptr)
		m_pInteractCenter->CheckAroundCombinator(this);
}

void CPartAutoCombinator::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();

	_DEBUG_COMMENT if (m_pPartsInteractCollision)
		_DEBUG_COMMENT m_pPartsInteractCollision->Render();

}

void CPartAutoCombinator::Interact(CCharacter* pCharacter)
{
	if (m_pParts == nullptr || pCharacter->GetPlayerState() != ePlayerState::None)
		return;
	pCharacter->SetParts(m_pParts);
	m_pParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
	m_pParts->GetCollision()->SetActive(true);
	m_pParts = nullptr;
	m_eCombinatorActionState = eCombinatorActionState::Usable;
}

void CPartAutoCombinator::PartsInteract(CParts* pParts)
{
	m_nPartsCount++;
	
	if (m_nPartsCount > m_nMaxPartsCount)
	{
		return;
	}

	if(m_nPartsCount == m_nMaxPartsCount)
		m_eCombinatorLoadState = eCombinatorLoadState::LoadImpossible;


	pParts->GetCollision()->SetActive(false);
	pParts->SetCombinatorPosition(m_vPosition);
	pParts->SetMoveParts(true);

	g_EventManager->CallEvent(eEvent::CombinUse, NULL);
}


void CPartAutoCombinator::CombineParts()
{
	m_fElapsedTime += g_pTimeManager->GetElapsedTime();

	if (m_fElapsedTime >= m_fCombineTime)
	{
		m_fElapsedTime = 0;
		ReadytoCarryParts();
	}
}

void CPartAutoCombinator::DischargeParts()
{
	//if (m_vecDischargeParts.empty())
	//{
	//	m_nPartsCount = 0;
	//	m_eCombinatorActionState = eCombinatorActionState::Unusable;
	//	m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
	//	m_isCombine = false;
	//	return;
	//}

	m_nPartsCount = 0;
	m_eCombinatorActionState = eCombinatorActionState::Unusable;
	m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
	m_isCombine = false;

	m_pParts = *m_vecDischargeParts.begin();
	//m_pParts->SetPosition(m_vOnCombinatorPosition);
	m_pParts->SetGrabPosition(&m_vOnCombinatorPosition);
	m_vecDischargeParts.clear();
}

void CPartAutoCombinator::InsertParts(CParts* p)
{
	m_multimapParts.insert(std::make_pair(p->GetPartsID(), p));
}

void CPartAutoCombinator::ReadytoCarryParts()
{
	m_isCombine = true;
	CParts* parts = Make();

	m_vecDischargeParts.push_back(parts);
	m_pInteractCenter->AddParts(parts);
}

CParts* CPartAutoCombinator::Make()
{
	string strResult;
	for (auto it : m_multimapParts)
	{
		strResult += it.first;
		m_pInteractCenter->DeleteParts(it.second);
	}
	m_multimapParts.clear();

	CParts* Parts = g_pPartsManager->CreateParts(g_pPartsManager->GetIDFromFormula(strResult));
	
	return Parts;
}

void CPartAutoCombinator::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	SetRotationY(fAngle);
	if (!m_pCollision)
		m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	// ???? ?????? ???? y?? ????
	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);
	if (!m_pPartsInteractCollision)
		m_pPartsInteractCollision = new CSphereCollision(D3DXVECTOR3(0, m_pCollision->GetCenter().y, 0), 2.0f, &m_matWorld);
	if (m_pCollision)
		m_pCollision->Update();

	if (m_pPartsInteractCollision)
		m_pPartsInteractCollision->Update();
}
