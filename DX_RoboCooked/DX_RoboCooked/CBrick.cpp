#include "stdafx.h"
#include "CBrick.h"
#include "CBoxCollision.h"

CBrick::CBrick(D3DXVECTOR3 vPosition)
{
	m_eTileType = eTileType::Brick;
	
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Brick");
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(100, 100, 100), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);

	if (m_pCollision)
		m_pCollision->Update();
}


CBrick::~CBrick()
{
}

void CBrick::Update()
{
}
