#include "stdafx.h"
#include "CPartStorage.h"
#include "CBoxCollision.h"
#include "CParts.h"
#include "CCharacter.h"
#include "CGameScene.h"
#include "CSkinnedMesh.h"

CPartStorage::CPartStorage(IInteractCenter *pInteractCenter)
	: m_pSkinnedMesh(nullptr)
	, m_isInteractCalled(false)
	, m_fPassedTime(0)
{
	m_pInteractCenter = pInteractCenter;
	m_fMass = 9999.f;
}

CPartStorage::~CPartStorage()
{
	m_pSkinnedMesh->DeleteTransform();
	SafeDelete(m_pSkinnedMesh);
}

void CPartStorage::Update()
{
	//_DEBUG_COMMENT cout << m_pSkinnedMesh->GetCurrentAnimPeriod() << endl;
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

void CPartStorage::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSkinnedMesh->Render(nullptr);

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void CPartStorage::Setup(float fAngle, D3DXVECTOR3 vPosition, string sPartsID)
{
	m_sID = sPartsID;
	m_pSkinnedMesh = new CSkinnedMesh;
	{
		if(m_sID == "A00")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTA_CV_A00.X");
		}
		else if (m_sID == "A01")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTA_CV_A01.X");
		}
		else if (m_sID == "A02")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTA_CV_A02.X");
		}
		else if (m_sID == "A03")
		{
			m_pSkinnedMesh->Load("data/model/object", "MTA_CV_A03.X");
		}
		else
		{
			m_pSkinnedMesh->Load("data/model/object", "MTA_CV.X");
		}
	}
	D3DXMATRIXA16* localmat = new D3DXMATRIXA16;
	D3DXMatrixTranslation(localmat, 0, -0.35f / 0.015, 0);
	m_pSkinnedMesh->SetTransform(localmat);
	//m_pCollision = new CBoxCollision((m_pSkinnedMesh->GetMax() + m_pSkinnedMesh->GetMin()) * 0.5f, m_pSkinnedMesh->GetMax() - m_pSkinnedMesh->GetMin(), &m_matWorld);
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(1 / 0.015f, 1 / 0.015f, 1 / 0.015f), &m_matWorld);
	
	SetScale(0.015, 0.015, 0.015);
	SetRotationY(fAngle);
	SetPosition(vPosition);

	if (m_pCollision)
		m_pCollision->Update();
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();
}


CParts *CPartStorage::Make()
{
	CParts *parts = g_pPartsManager->CreateParts(m_sID);
	return parts;
}

void CPartStorage::Interact(CCharacter *pCharacter)
{
	if (pCharacter->GetPlayerState() == ePlayerState::None)
	{
		g_SoundManager->PlaySFX("box");

		CParts *parts = Make();
		parts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
		m_pInteractCenter->AddParts(parts);
		pCharacter->SetParts(parts);
		m_pSkinnedMesh->SetAnimationIndexBlend(0);
		m_fPassedTime = 0.0f;
		//pCharacter->SetPlayerState(ePlayerState::Grab);
		m_isInteractCalled = true;
	}
}
