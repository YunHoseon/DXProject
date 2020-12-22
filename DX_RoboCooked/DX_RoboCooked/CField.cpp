#include "stdafx.h"
#include "CField.h"
#include "CTile.h"

#include "CBoxCollision.h"

const float Y = -1.0f;
CField::CField(eTileType type):
	m_stMtlTile({}),
	m_eTileType(type),
	m_fMinX(0),
	m_fMaxX(0),
	m_fMinZ(0),
	m_fMaxZ(0),
	m_fVoidMaxX(16 * 0.5f * BLOCK_SIZE),
	m_fVoidMaxZ(12 * 0.5f * BLOCK_SIZE),
	m_fVoidMinX(-m_fVoidMaxX),
	m_fVoidMinZ(-m_fVoidMaxZ)
{
	Setup();
}


CField::~CField()
{
	for each(auto c in m_vecTile)
		SafeDelete(c);
}

void CField::Setup(int iWidth, int iHeight)
{
	m_fMaxX = (iWidth / 2.0f) * BLOCK_SIZE;
	m_fMinX = -m_fMaxX;
	
	float fStartX = m_fMinX + BLOCK_SIZE * 0.5f;

	m_fMaxZ = (iHeight / 2.0f) * BLOCK_SIZE;
	m_fMinZ = -m_fMaxZ;
	float fStartZ = m_fMaxZ - BLOCK_SIZE * 0.5f;
	CTile* test;
	for (float i = 0; i < iWidth; ++i )
	{
		for (float j = 0; j < iHeight; ++j)
		{
			if (i > 6 && i < 23 && j > 0 && j < 13)
				continue;
			
			// 타일 생성
			switch (m_eTileType)
			{
			case eTileType::FlowSand:
				test = new CFlowSand(D3DXVECTOR3(fStartX + BLOCK_SIZE * i, Y, fStartZ - BLOCK_SIZE * j));
				break;
			case eTileType::Stair:
				test = new CStair(D3DXVECTOR3(fStartX + BLOCK_SIZE * i, Y, fStartZ - BLOCK_SIZE * j));
				break;
			case eTileType::Water:
				test = new CWater(D3DXVECTOR3(fStartX + BLOCK_SIZE * i, Y, fStartZ - BLOCK_SIZE * j));
				break;
			case eTileType::Brick:
				test = new CBrick(D3DXVECTOR3(fStartX + BLOCK_SIZE * i, Y, fStartZ - BLOCK_SIZE * j));
				break;
			case eTileType::Sand:
				test = new CSand(D3DXVECTOR3(fStartX + BLOCK_SIZE * i, Y, fStartZ - BLOCK_SIZE * j));
				break;
			case eTileType::Soil:
				test = new CSoil(D3DXVECTOR3(fStartX + BLOCK_SIZE * i, Y, fStartZ - BLOCK_SIZE * j));
				break;
			case eTileType::ThickSand:
				test = new CThickSand(D3DXVECTOR3(fStartX + BLOCK_SIZE * i, Y, fStartZ - BLOCK_SIZE * j));
				break;
			default: ;
			}
			
			m_vecTile.push_back(test);
		}
	}
	m_pCollision = new CBoxCollision(D3DXVECTOR3(0, Y, 0), D3DXVECTOR3(BLOCK_SIZE * (m_fMaxX - m_fMinX), BLOCK_SIZE, BLOCK_SIZE * (m_fMaxZ - m_fMinZ)), &m_matWorld);
	m_fFriction = m_vecTile[0]->GetFriction();
	m_fRepulsivePower = m_vecTile[0]->GetRepulsivePower();
	
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

bool CField::Collide(CActor* target, D3DXVECTOR3* pNormal)
{
	D3DXVECTOR3 pos = target->GetPosition();
	if (pos.x < m_fVoidMaxX && pos.x > m_fVoidMinX && pos.z < m_fVoidMaxZ && pos.z > m_fVoidMinZ)
		return false;
	if (pos.y > Y + 1.5f)
		return false;


	return CActor::Collide(target, pNormal);
}
