#include "stdafx.h"
#include "CStair.h"
#include "CBoxCollision.h"

CStair::CStair(D3DXVECTOR3 vPosition)
{
	m_pSMesh = g_pStaticMeshManager->GetStaticMesh("Stair");
	//m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(100, 100, 100), &m_matWorld);
	const float root22 = pow(2, 0.5) * 0.5;

	CBoxCollision* pCollision = new CBoxCollision(D3DXVECTOR3(0, 100 * -0.5, 100 * 0.5f), D3DXVECTOR3(1 * 100, root22 * 2 * 100, root22 * 2 * 100), &m_matWorld);
	pCollision->RotateOriginAxis(D3DX_PI * 0.25f, 0, 0);
	m_pCollision = pCollision;
	SetRotationY(0);
	SetScale(0.01f, 0.01f, 0.01f);
	SetPosition(vPosition);

	//float y = vPosition.y - 0.5f + m_pCollision->GetHeight() * 0.5f + (vPosition.y - m_pCollision->GetCenter().y);
	//SetPosition(vPosition.x, y, vPosition.z);

	if (m_pCollision)
		m_pCollision->Update();
}


CStair::~CStair()
{
}

void CStair::Render()
{
	CTile::Render();
	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT 	m_pCollision->Render();
}

