#include "stdafx.h"
#include "CPharaohCoppin.h"
#include "ICollisionArea.h"
#include "CCharacter.h"
#include "CGameScene.h"

CPharaohCoppin::CPharaohCoppin(IInteractCenter* pInteractCenter, D3DXVECTOR3 vPos)
	: m_pSMesh(nullptr)
	,m_isInteractCalled(false)
	, m_fPassedTime(0)
{
	m_fMass = 9999.f;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Coffin");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
	SetScale(0.01f, 0.01f, 0.01f);
	SetRotationY(D3DXToRadian(0));

	float y = vPos.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPos.y - m_pCollision->GetCenter().y);
	SetPosition(vPos.x, y, vPos.z);

	if (m_pCollision)
		m_pCollision->Update();
}


CPharaohCoppin::~CPharaohCoppin()
{
}

void CPharaohCoppin::Update()
{
}

void CPharaohCoppin::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();
}

void CPharaohCoppin::Interact(CCharacter * pCharacter)
{
	if (pCharacter->GetPlayerState() == ePlayerState::None)
	{
		CParts *parts = MakeParts();
		parts->SetGrabPosition(&pCharacter->GetGrabPartsPosition());
		m_pInteractCenter->AddParts(parts);
		pCharacter->SetParts(parts);
		m_isInteractCalled = true;
	}
}

CParts* CPharaohCoppin::MakeParts()
{
	CParts *parts = g_pPartsManager->CreateParts(m_sID);
	return parts;
}

void CPharaohCoppin::StopMove()
{

}
