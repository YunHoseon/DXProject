#include "stdafx.h"
#include "CPartManualCombinator.h"
#include "ICollisionArea.h"
#include "CBoxCollision.h"
#include "CCharacter.h"
#include "CParts.h"
#include "CSphereCollision.h"
#include "IInteractCenter.h"
#include "CUICombinatorGauge.h"


CPartManualCombinator::CPartManualCombinator(IInteractCenter* pInteractCenter, eCombinatorPartsLevel eType, float fAngle, D3DXVECTOR3 vPosition):
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


CPartManualCombinator::~CPartManualCombinator()
{
	SafeDelete(m_pPartsInteractCollision);
	SafeDelete(m_pCollision);
	SafeRelease(m_CombinatorTexture);
}

void CPartManualCombinator::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	SetRotationY(fAngle);
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	m_pUICombinatorGauge = new CUICombinatorGauge(&m_vPosition);

	// 메시 크기에 따라 y값 보정
	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);
	m_pPartsInteractCollision = new CSphereCollision(D3DXVECTOR3(0, m_pCollision->GetCenter().y,0), 2.0f, &m_matWorld);

	if (m_pCollision)
		m_pCollision->Update();
	if (m_pPartsInteractCollision)
		m_pPartsInteractCollision->Update();
	
	m_isTimeCheck = false;
}


void CPartManualCombinator::Update()
{
	if (m_isTimeCheck && m_eCombinatorActionState == eCombinatorActionState::Usable)
		CombineParts();
	
	if (m_isCombine && m_pParts == nullptr)
		DischargeParts();

	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadPossible)
		m_pInteractCenter->CheckAroundCombinator(this);
}

void CPartManualCombinator::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	if (m_pUICombinatorGauge)
		m_pUICombinatorGauge->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();

	_DEBUG_COMMENT if (m_pPartsInteractCollision)
		_DEBUG_COMMENT m_pPartsInteractCollision->Render();
}

CParts* CPartManualCombinator::Make()
{
	/*
	 * 조합식 매니저로 조합식들고와서 조합 
	 */
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

void CPartManualCombinator::Interact(CCharacter* pCharacter)
{
	if (m_pParts == nullptr ||  pCharacter->GetPlayerState() != ePlayerState::None)
		return;

	//pCharacter->SetPlayerState(ePlayerState::Grab);
	pCharacter->SetParts(m_pParts);
	m_pParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
	m_pParts->GetCollision()->SetActive(true);
	m_pParts = nullptr;

}

void CPartManualCombinator::PartsInteract(CParts* pParts)
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
	//pParts->SetMoveParts(true);
	pParts->SetMoveParts(true, m_vecOnCombinatorPosition[m_nPartsCount - 1]);
	g_EventManager->CallEvent(eEvent::CombinUse, NULL);
	
}

void CPartManualCombinator::CombineParts()
{
	m_fElapsedTime += g_pTimeManager->GetElapsedTime();
	g_SoundManager->PlaySFX("machine_run");
	if(m_pUICombinatorGauge)
		m_pUICombinatorGauge->UpdateCombinator(m_fElapsedTime, m_fCombineTime);

	if(m_fElapsedTime >= m_fCombineTime)
	{
		m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
		m_isTimeCheck = false;
		m_fElapsedTime = 0;
		
		CParts* parts = Make();
		if(m_pUICombinatorGauge)
			m_pUICombinatorGauge->SetChildActive(false);
		m_vecDischargeParts.push_back(parts);
		m_pInteractCenter->AddParts(parts);

		m_isCombine = true;
	}
}

void CPartManualCombinator::DischargeParts()
{
	if (m_vecDischargeParts.empty())
	{
		m_nPartsCount = 0;
		m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
		m_isCombine = false;
		return;
	}
	m_pParts = *m_vecDischargeParts.begin();
	//m_pParts->SetPosition(m_vOnCombinatorPosition);
	//m_pParts->SetGrabPosition(&m_vOnCombinatorPosition);
	m_pParts->SetGrabPosition(&m_vecOnCombinatorPosition[1]);
	m_vecDischargeParts.erase(m_vecDischargeParts.begin());
}

void CPartManualCombinator::InsertParts(CParts* p)
{
	m_multimapParts.insert(std::make_pair(p->GetPartsID(), p));
}

void CPartManualCombinator::ReadytoCarryParts()
{
	CheckCombineisFull();
	if (m_isTimeCheck)
		return;

	m_isCombine = true; 
	for (auto it : m_multimapParts)
	{
		m_vecDischargeParts.push_back(it.second);
	}
	m_multimapParts.clear();
}

void CPartManualCombinator::CheckCombineisFull()
{
	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadImpossible)
	{
		for (auto it : m_multimapParts)
		{
			it.second->UsingCombinator();
		}
		
		m_isTimeCheck = true;
	}
}
