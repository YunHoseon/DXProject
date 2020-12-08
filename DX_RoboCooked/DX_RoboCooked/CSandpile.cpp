#include "stdafx.h"
#include "CSandpile.h"
#include "CBoxCollision.h"
#include "IInteractCenter.h"


CSandpile::CSandpile(IInteractCenter* InteractCenter, D3DXVECTOR3 vPosition) : m_pCollsionArea(nullptr)
{
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Sandpile");
	m_pInteractCenter = InteractCenter;
	m_pCollsionArea = new CBoxCollision(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), &m_matWorld);
	SetScale(0.01f, 0.01f, 0.01f);
	SetRotationY(0);
	SetPosition(vPosition);

	m_pCollsionArea->Update();
}


CSandpile::~CSandpile()
{
}

void CSandpile::Render()
{
	if (m_pSMesh)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		m_pSMesh->Render();
	}

	_DEBUG_COMMENT if (m_pCollsionArea)
		_DEBUG_COMMENT 	m_pCollsionArea->Render();
}

void CSandpile::Update()
{
	m_pInteractCenter->CheckSandDummyArea(m_pCollsionArea);
}
