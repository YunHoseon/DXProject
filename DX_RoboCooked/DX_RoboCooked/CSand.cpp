#include "stdafx.h"
#include "CSand.h"
#include "CBoxCollision.h"

CSand::CSand(D3DXVECTOR3 vPosition)
{
	m_eTileType = eTileType::Sand;
	
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Sand");
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(100, 100, 100), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);

	if (m_pCollision)
		m_pCollision->Update();

	m_fFriction = 0.4f;
}


CSand::~CSand()
{
}

void CSand::Update()
{
}
