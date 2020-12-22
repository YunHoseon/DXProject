#include "stdafx.h"
#include "CCactus.h"
#include "ICollisionArea.h"

CCactus::CCactus(): m_pSMesh(nullptr)
{
	m_fFriction = 0.5;
	m_fRepulsivePower = 0.5f;
	m_fMass = 9999.f;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Cactus");
	m_pCollision = new CBoxCollision(m_pSMesh->GetMesh(), &m_matWorld);
	SetScale(0.01f, 0.01f, 0.01f);
}

CCactus::CCactus(D3DXVECTOR3 vPos) : CCactus()
{
	SetPosition(vPos);
}

CCactus::~CCactus()
{
}

void CCactus::Update()
{
}

void CCactus::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pSMesh->Render();

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT	m_pCollision->Render();
}
