#include "stdafx.h"
#include "CThickSand.h"
#include "CBoxCollision.h"

CThickSand::CThickSand(D3DXVECTOR3 vPosition)
{
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("ThickSand");
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(1 / 0.0021, 1 / 0.0021, 1 / 0.0021), &m_matWorld);

	SetScale(0.0021f, 0.0021f, 0.0021f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);

	if (m_pCollision)
		m_pCollision->Update();

	m_fFriction = 0.3f;
}


CThickSand::~CThickSand()
{
}

void CThickSand::Update()
{
}
