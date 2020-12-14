#include "stdafx.h"
#include "CPharaohCoffin.h"
#include "ICollisionArea.h"
#include "CCharacter.h"
#include "CGameScene.h"
#include "CCCStopMove.h"

CPharaohCoffin::CPharaohCoffin(IInteractCenter* pInteractCenter, D3DXVECTOR3 vPos)
	: m_pSMesh(nullptr)
	, m_isInteractCalled(false)
	, m_fCoolTime(0)
	, m_fPassedTime(0)
	, m_isMoveBlocked(false)
{
	m_pInteractCenter = pInteractCenter;
	m_arrPartsID[0] = "B00"; m_arrPartsID[1] = "B01"; m_arrPartsID[2] = "B02";
	m_arrPartsID[3] = "B03"; m_arrPartsID[4] = "B04";
	m_fMass = 9999.f;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Coffin");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
	m_pCCCollision = new CSphereCollision(g_vZero, 1.5f, &m_matWorld);
	SetScale(0.01f, 0.01f, 0.01f);
	SetRotationY(D3DXToRadian(0));

	float y = vPos.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPos.y - m_pCollision->GetCenter().y);
	SetPosition(vPos.x, y, vPos.z);

	if (m_pCollision)
		m_pCollision->Update();
	if (m_pCCCollision)
		m_pCCCollision->Update();
}


CPharaohCoffin::~CPharaohCoffin()
{

}

void CPharaohCoffin::Update()
{
	if (m_isInteractCalled)
	{
		m_fCoolTime += g_pTimeManager->GetElapsedTime();
		if (5.0f <= m_fCoolTime)
		{
			m_isInteractCalled = false;
			m_fCoolTime = 0.0f;
		}
	}

	if (m_isMoveBlocked)
	{
		m_fPassedTime += g_pTimeManager->GetElapsedTime();
		if (3.0f <= m_fPassedTime)
		{
			m_isMoveBlocked = false;
			m_fPassedTime = 0.0f;
		}
	}
	else
	{
		for (CCharacter* it : m_pInteractCenter->GetCharacters())
		{
			if (m_pCCCollision->Collide(it->GetCollision()))
			{
				it->DeleteCC();
			}
		}
	}
}

void CPharaohCoffin::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();
	_DEBUG_COMMENT if (m_pCCCollision)
		_DEBUG_COMMENT	m_pCCCollision->Render();
}

void CPharaohCoffin::Interact(CCharacter * pCharacter)
{
	if (!m_isInteractCalled)
	{
		m_isInteractCalled = true;
		int MakeOrCC = m_randNumGenerator.GenInt(0, 1);

		if (MakeOrCC)
		{
			if (pCharacter->GetPlayerState() == ePlayerState::None)
			{
				CParts *parts = Make();
				parts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
				m_pInteractCenter->AddParts(parts);
				pCharacter->SetParts(parts);
			}
		}
		else
		{
			m_isMoveBlocked = true;
			for (CCharacter* it : m_pInteractCenter->GetCharacters())
			{
				if (m_pCCCollision->Collide(it->GetCollision()))
				{
					it->SetCC(new CCCStopMove);
				}
			}
		}
	}
}

CParts* CPharaohCoffin::Make()
{
	CParts *parts = g_pPartsManager->CreateParts(m_arrPartsID[m_randNumGenerator.GenInt(0, 4)]);
	return parts;
}
