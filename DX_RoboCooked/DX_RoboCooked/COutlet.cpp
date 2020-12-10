#include "stdafx.h"
#include "COutlet.h"
#include "ICollisionArea.h"
#include "CBoxCollision.h"
#include "CCharacter.h"
#include "IInteractCenter.h"
#include "CParts.h"
#include "CSkinnedMesh.h"

COutlet::COutlet(IInteractCenter* pInteractCenter) 
	: m_eOutletState(eOutletState::None)
	, m_PartVendingTexture(nullptr)
	, m_pMyParts(nullptr)
	, m_isInteractCalled(false)
	, m_fPassedTime(0)
{
	m_pInteractCenter = pInteractCenter;
	m_fMass = 9999.f;
}


COutlet::~COutlet()
{
}

void COutlet::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	m_pSkinnedMesh = new CSkinnedMesh;
	m_pSkinnedMesh->Load("data/model/object", "MTH_CV.X");
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(1 / 0.015f, 1 / 0.015f, 1 / 0.015f), &m_matWorld);

	SetRotationY(fAngle);
	SetPosition(vPosition);
	SetScale(0.015, 0.015, 0.015);

	if (m_pCollision)
		m_pCollision->Update();
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();

	m_vOnGrabPosition = vPosition;
	m_vOnGrabPosition.y += 1.0f;
}

void COutlet::Update()
{
	if (m_isInteractCalled)
	{
		m_fPassedTime += g_pTimeManager->GetElapsedTime();
		if (m_pSkinnedMesh->GetCurrentAnimPeriod() <= m_fPassedTime)
		{
			m_isInteractCalled = false;
			m_fPassedTime = 0.0f;
		}
		m_pSkinnedMesh->Update();
	}
}

void COutlet::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSkinnedMesh->Render(nullptr);

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void COutlet::OnEvent(eEvent eEvent, void* _value)
{
}

void COutlet::Interact(CCharacter* pCharacter)
{
	if (pCharacter->GetPlayerState() == ePlayerState::None 
		&& m_eOutletState == eOutletState::Loaded)
	{
		m_pMyParts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());	
		pCharacter->SetParts(m_pMyParts);									
		
		//pCharacter->SetPlayerState(ePlayerState::Grab);
		m_eOutletState = eOutletState::None;
		m_pMyParts = nullptr;
	}
}

void COutlet::AcceptPartsFromVending(CParts * parts)
{
	m_eOutletState = eOutletState::Loaded;
	m_pMyParts = parts;
	//parts->SetPosition(this->GetPosition() + D3DXVECTOR3(0, 1.0f, 0));
	parts->SetGrabPosition(&m_vOnGrabPosition);
	m_isInteractCalled = true;
}
