#include "stdafx.h"
#include "CField.h"
#include "CTile.h"

#include "CBoxCollision.h"

const float Y = -1.0f;
CField::CField(): m_stMtlTile({})
{
	m_fFriction = 0.2f; // test
	m_fMass = 9999.f;
}


CField::~CField()
{
	for each(auto c in m_vecTile)
		SafeDelete(c);
}

void CField::Setup(int iWidth, int iHeight)
{
	float fMaxX = (iWidth / 2.0f) * BLOCK_SIZE;
	float fMinX = -fMaxX;

	float fMaxZ = (iHeight / 2.0f) * BLOCK_SIZE;
	float fMinZ = -fMaxZ;
	
	for (float i = fMinZ + (BLOCK_SIZE/2); i <= fMaxZ; i+=BLOCK_SIZE)
	{
		for (float j = fMinX + (BLOCK_SIZE / 2); j <= fMaxX; j += BLOCK_SIZE)
		{
			// 타일 생성
			CTile* testSand = new CSand(D3DXVECTOR3((float)j, Y, (float)i));
			m_vecTile.push_back(testSand);
		}
	}
	m_pCollision = new CBoxCollision(D3DXVECTOR3(0, Y, 0), D3DXVECTOR3(BLOCK_SIZE * (fMaxX - fMinX), BLOCK_SIZE, BLOCK_SIZE * (fMaxZ - fMinZ)), &m_matWorld);
	
	m_pCollision->Update();
}


void CField::Render()
{
	//g_pD3DDevice->SetMaterial(&m_stMtlTile);

	for each(auto c in m_vecTile)
	{
		c->Render();
	}

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void CField::Update()
{
	
}
