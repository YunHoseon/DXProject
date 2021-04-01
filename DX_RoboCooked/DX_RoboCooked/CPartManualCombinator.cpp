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

	// �޽� ũ�⿡ ���� y�� ����
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
	
	if (m_isDischarging && m_pParts == nullptr)
		DischargeParts();

	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadPossible)
		m_pInteractCenter->CheckAroundCombinator(this);

	if (m_pParts != nullptr && m_pParts->GetPartsID() == "D00")
	{
		m_eCombinatorActionState = eCombinatorActionState::Unusable;
		m_DestroyTrashCountTime += g_pTimeManager->GetElapsedTime();
		if (m_pParts->GetDestroyTrashTime() <= m_DestroyTrashCountTime)
		{
			m_pInteractCenter->DeleteParts(m_pParts);
			m_pParts = nullptr;
			m_eCombinatorActionState = eCombinatorActionState::Usable;
			m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
			m_DestroyTrashCountTime = 0;
		}
	}
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
	 * ���ս� �Ŵ����� ���սĵ��ͼ� ���� 
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
	if (m_pParts == nullptr || pCharacter->GetPlayerState() != ePlayerState::None)
		return;
	if (m_pParts->GetPartsID() == "D00")
		return;

	//pCharacter->SetPlayerState(ePlayerState::Grab);
	pCharacter->SetParts(m_pParts);
	m_pParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
	m_pParts->GetCollision()->SetActive(true);
	m_pParts = nullptr;
	
	m_eCombinatorActionState = eCombinatorActionState::Usable;
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
	if (!g_SoundManager->IsPlayingSFX("machine_run"))
		g_SoundManager->PlaySFX("machine_run");
	if(m_pUICombinatorGauge)
		m_pUICombinatorGauge->UpdateCombinator(m_fElapsedTime, m_fCombineTime);

	if(m_fElapsedTime >= m_fCombineTime)
	{
		//m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
		m_isTimeCheck = false;
		m_fElapsedTime = 0;
		
		CParts* parts = Make();
		parts->GetCollision()->SetActive(false);
		if(m_pUICombinatorGauge)
			m_pUICombinatorGauge->SetChildActive(false);
		m_vecDischargeParts.push_back(parts);
		m_pInteractCenter->AddParts(parts);

		m_isDischarging = true;
	}
}

void CPartManualCombinator::DischargeParts()
{
	if (m_vecDischargeParts.empty())
	{
		m_nPartsCount = 0;
		m_eCombinatorLoadState = eCombinatorLoadState::LoadPossible;
		m_isDischarging = false;
		return;
	}
	m_pParts = m_vecDischargeParts.back();
	//m_pParts->SetPosition(m_vOnCombinatorPosition);
	//m_pParts->SetGrabPosition(&m_vOnCombinatorPosition);
	m_pParts->SetGrabPosition(&m_vecOnCombinatorPosition[1]);
	m_pParts->Unsmallize();
	//m_vecDischargeParts.erase(m_vecDischargeParts.begin());
	m_vecDischargeParts.pop_back();
}

void CPartManualCombinator::InsertParts(CParts* p)
{
	m_multimapParts.insert(std::make_pair(p->GetPartsID(), p));
}

void CPartManualCombinator::ReadytoCarryParts()
{
	CheckCombineisFull();
	if (m_isTimeCheck) //���� �����ִٸ� ��ǰ�� ����� ���տ� ��
		return;

	// �� ������ ���� ��� ����ִ� ��ǰ�� �������� �迭�� �߰���.
	m_isDischarging = true; 
	for (auto it : m_multimapParts)
	{
		m_vecDischargeParts.push_back(it.second);
	}
	m_multimapParts.clear();
	//if (!m_vecDischargeParts.empty())
	m_eCombinatorLoadState = eCombinatorLoadState::LoadImpossible;
}

void CPartManualCombinator::CheckCombineisFull()
{
	// loadImpossible => �� ���ְų� ������ ��ǰ�� ���� ��.
	// ���� LoadImpossible�̰� ������ ��ǰ�� ���ٸ� �� ���ִ�.
	if (m_eCombinatorLoadState == eCombinatorLoadState::LoadImpossible && m_pParts == nullptr) 
	{
		for (auto it : m_multimapParts)
		{
			it.second->UsingCombinator();
		}
		
		m_isTimeCheck = true;
	}
}
