#include "stdafx.h"
#include "CSandpile.h"
#include "CBoxCollision.h"
#include "IInteractCenter.h"


CSandpile::CSandpile(IInteractCenter* InteractCenter, D3DXVECTOR3 vPosition) : m_pCollisionArea(nullptr)
{
	m_fMass = 0;
	m_fFriction = 0;
	m_fRepulsivePower = 0;
	
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Sandpile");
	m_pInteractCenter = InteractCenter;
	m_pCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 100, 100), &m_matWorld);
	SetScale(0.01f, 0.01f, 0.01f);
	m_pCollision->SetActive(false);
	
	SetRotationY(0);
	SetPosition(vPosition);

	m_pCollisionArea = new CBoxCollision(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.8, 0.3, 0.8), &m_matWorld);
	m_pCollisionArea->Update();
}


CSandpile::~CSandpile()
{
	SafeDelete(m_pCollisionArea);
	SafeDelete(m_pCollision);
}

void CSandpile::Render()
{
	if (m_pSMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pSMesh->Render();
	}

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT 	m_pCollision->Render();
	_DEBUG_COMMENT if (m_pCollisionArea)
		_DEBUG_COMMENT 	m_pCollisionArea->Render();
}

void CSandpile::Update()
{
	m_pInteractCenter->CheckSandDummyArea(m_pCollisionArea);
}

void CSandpile::SetPosition(D3DXVECTOR3 vPosition)
{
	CActor::SetPosition(vPosition);
	if (m_pCollisionArea)
		m_pCollisionArea->Update();
}

void CSandpile::SetPosition(float x, float y, float z)
{
	CActor::SetPosition(x, y, z);
	if (m_pCollisionArea)
		m_pCollisionArea->Update();
}
