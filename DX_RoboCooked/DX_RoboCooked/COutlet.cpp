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
	m_pSkinnedMesh->DeleteTransform();
	SafeDelete(m_pSkinnedMesh);
}

void COutlet::Setup(float fAngle, D3DXVECTOR3 vPosition)
{
	m_pSkinnedMesh = new CSkinnedMesh;
	m_pSkinnedMesh->Load("data/model/object", "MTH_CV.X");
	D3DXMATRIXA16* localmat = new D3DXMATRIXA16;
	D3DXMatrixTranslation(localmat, 0, -0.35f / 0.015, 0);
	m_pSkinnedMesh->SetTransform(localmat);
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
	m_pSkinnedMesh->SetAnimationIndexBlend(0);
	m_fPassedTime = 0.0f;
	m_isInteractCalled = true;
}

void COutlet::SetPartsId(string sPartsID)
{
	D3DXMATRIXA16* mat = m_pSkinnedMesh->GetTransform();
	SafeDelete(m_pSkinnedMesh);
	m_pSkinnedMesh = new CSkinnedMesh;
	{
		if (sPartsID == "A00")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTH_CV_CA_A00.X");
		}
		else if (sPartsID == "A01")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTH_CV_CA_A01.X");
		}
		else if (sPartsID == "A02")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTH_CV_CA_A02.X");
		}
		else if (sPartsID == "A03")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTH_CV_CA_A03.X");
		}
		else
		{
			m_pSkinnedMesh->Load("data/model/object", "MTH_CV.X");
		}
	}
	m_pSkinnedMesh->SetTransform(mat);
	m_pSkinnedMesh->Update();
}

void COutlet::CreateShadowMap()
{
	g_pRenderShadowManager->GetCreateShadowShader()->SetMatrix("gWorldMatrix", &m_matWorld);
	UINT numPasses = 0;
	g_pRenderShadowManager->GetCreateShadowShader()->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		g_pRenderShadowManager->GetCreateShadowShader()->BeginPass(i);
		{
			m_pSkinnedMesh->Render(nullptr);
		}
		g_pRenderShadowManager->GetCreateShadowShader()->EndPass();
	}

	g_pRenderShadowManager->GetCreateShadowShader()->End();
}
