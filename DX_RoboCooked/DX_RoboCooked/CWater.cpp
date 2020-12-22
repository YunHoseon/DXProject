#include "stdafx.h"
#include "CWater.h"
#include "CBoxCollision.h"

CWater::CWater(D3DXVECTOR3 vPosition)
{
	m_eTileType = eTileType::Water;

	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Water");
	m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(100, 100, 100), &m_matWorld);

	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	SetPosition(vPosition.x, y, vPosition.z);
	m_fFriction = 0.0;
	m_fRepulsivePower = 0.f;
	m_fFlexibility = .5f;
	m_fMass = 0.01f;
	if (m_pCollision)
		m_pCollision->Update();
}


CWater::~CWater()
{
}

void CWater::Update()
{
}

bool CWater::Collide(CActor* target, D3DXVECTOR3* pNormal)
{
	bool b = CActor::Collide(target, pNormal);
	if(b)
		target->GetCollision()->SetIsCollide(false);
	return b;
}
