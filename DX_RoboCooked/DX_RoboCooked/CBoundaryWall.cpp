#include "stdafx.h"
#include "CBoundaryWall.h"

#include "CWall.h"
#include "ICollisionArea.h"

CBoundaryWall::CBoundaryWall()
{
	m_vecWall.push_back(new CWall(nullptr, false, 12, 5));
	m_vecWall.push_back(new CWall(nullptr, false, 12, 5));
	m_vecWall[0]->SetPosition(-8.5 * BLOCK_SIZE, -1.5f, 0);
	m_vecWall[0]->SetRotationY(D3DX_PI * 0.5f);
	m_vecWall[1]->SetPosition(8.5 * BLOCK_SIZE, -1.5f, 0);
	m_vecWall[1]->SetRotationY(D3DX_PI * 0.5f);
	m_matWorld = g_matIdentity;

	D3DXVECTOR3 vMin(12 * -0.5f * BLOCK_SIZE, 0, -0.5f);
	D3DXVECTOR3 vMax(12 * 0.5f * BLOCK_SIZE, 5 * BLOCK_SIZE, 0.5f);
	D3DXVECTOR3 vOrigin((vMax + vMin) * 0.5f);
	vOrigin.z = -6.5f;
	m_pCollision = new CBoxCollision(vOrigin, (vMax - vMin) * 1.5f, &m_matWorld);
	m_fMass = 9999.f;
}

CBoundaryWall::~CBoundaryWall()
{
	for (vector<CWall*>::value_type p : m_vecWall)
	{
		SafeDelete(p);
	}
}

void CBoundaryWall::Render()
{
	for (vector<CWall*>::value_type p : m_vecWall)
	{
		p->Render();
	}
	_DEBUG_COMMENT if (m_pCollision)
	_DEBUG_COMMENT	m_pCollision->Render();
}

bool CBoundaryWall::Collide(CActor* target, D3DXVECTOR3* pNormal)
{
	bool b = false;
	D3DXVECTOR3 normal1(g_vZero), normal2(g_vZero), normal3(g_vZero);
	b += m_vecWall[0]->Collide(target, &normal1);
	b += m_vecWall[1]->Collide(target, &normal2);
	if (m_pCollision)
		b += m_pCollision->Collide(target->GetCollision(), &normal3);

	if (pNormal)
		*pNormal = normal1 + normal2 + normal3;
	return b;
}
