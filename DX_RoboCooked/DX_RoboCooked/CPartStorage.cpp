#include "stdafx.h"
#include "CPartStorage.h"
#include "CBoxCollision.h"
#include "CParts.h"
#include "CCharacter.h"
#include "CGameScene.h"
#include "CSkinnedMesh.h"

CPartStorage::CPartStorage(IInteractCenter *pInteractCenter) : m_pSkinnedMesh(nullptr)
{
	m_pInteractCenter = pInteractCenter;
	m_fMass = 9999.f;
}

CPartStorage::~CPartStorage()
{
}

void CPartStorage::Update()
{
	m_pSkinnedMesh->Update();
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

	m_pSkinnedMesh = new CSkinnedMesh("data/model/object", "MTA_CV.X");
	//m_pCollision = new CBoxCollision((m_pSkinnedMesh->GetMax() + m_pSkinnedMesh->GetMin()) * 0.5f, m_pSkinnedMesh->GetMax() - m_pSkinnedMesh->GetMin(), &m_matWorld);
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(1 / 0.015f, 1 / 0.015f, 1 / 0.015f), &m_matWorld);

	SetRotationY(fAngle);
	SetPosition(vPosition);
	SetScale(0.015, 0.015, 0.015);

	if (m_pCollision)
		m_pCollision->Update();
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();
}

void CPartStorage::OnEvent(eEvent eEvent, void *_value)
{
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
		CParts *parts = Make();
		parts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
		m_pInteractCenter->AddParts(parts);
		pCharacter->SetParts(parts);
		//pCharacter->SetPlayerState(ePlayerState::Grab);
	}
}
