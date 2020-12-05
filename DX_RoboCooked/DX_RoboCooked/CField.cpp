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
			CTile* testWater = new CSand3(D3DXVECTOR3((float)j, Y, (float)i));
			m_vecTile.push_back(testWater);
			
		}
	}

	//for (int i = 0; i < m_vecTile.size(); i++)
	//{
	//	if (i == 5 || i == 3)
	//		m_vecTile[i]->SetPlaneTexture(g_pTextureManager->GetTexture("data/stones.png"));
	//	else
	//		m_vecTile[i]->SetPlaneTexture(g_pTextureManager->GetTexture("data/Texture/Albedo00.jpg"));
	//}

	//ZeroMemory(&m_stMtlTile, sizeof(D3DMATERIAL9));
	//m_stMtlTile.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	//m_stMtlTile.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	//m_stMtlTile.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
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
