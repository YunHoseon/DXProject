#include "stdafx.h"
#include "CTestStair.h"

#include "CBoxCollision.h"

CTestStair::CTestStair()
{
	const float root22 = pow(2, 0.5) * 0.5;
	CBoxCollision* pCollision = new CBoxCollision(D3DXVECTOR3(0, -0.5, -0.5), D3DXVECTOR3(1, root22 * 2, root22 * 2), &m_matWorld);
	pCollision->RotateOriginAxis(D3DX_PI * 0.25f, 0, 0);
	m_pCollision = pCollision;
	//SetRotationY(D3DX_PI * 0.5f);
	SetPosition(1, 0, -4);
	m_fMass = 9999.f;
	m_fFriction = 0.2f;
	
}

CTestStair::~CTestStair()
{
}

void CTestStair::Update()
{
}

void CTestStair::Render()
{
	_DEBUG_COMMENT if (m_pCollision)
	_DEBUG_COMMENT 	m_pCollision->Render();
}
