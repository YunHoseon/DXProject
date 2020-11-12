#include "stdafx.h"
#include "CField.h"



CField::CField()
{
}


CField::~CField()
{
	for each(auto c in m_vecTile)
		SafeDelete(c);


	SafeRelease(m_pCubeTile);
	
}

void CField::Setup(int iWidth, int iHeight)
{
	float fMaxX = (iWidth / 2) * BLOCK_SIZE;
	float fMinX = -fMaxX;

	float fMaxZ = (iHeight / 2) * BLOCK_SIZE;
	float fMinZ = -fMaxZ;


	/*ST_PNT_VERTEX	v;
	vector<ST_PNT_VERTEX> vecPlane;
	v.n = D3DXVECTOR3(0, 1, 0);*/
	//plane
	//for (int i = 0; i < iHeight; ++i)
	//{
	//	for (int j = 0; j < iWidth; ++j)
	//	{
	//		
	//		v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE }; v.t = D3DXVECTOR2(0, 0);
	//		vecPlane.push_back(v);
	//		v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE + BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE }; v.t = D3DXVECTOR2(1, 0);
	//		vecPlane.push_back(v);
	//		v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE -BLOCK_SIZE }; v.t = D3DXVECTOR2(0, 1);
	//		vecPlane.push_back(v);
	//		v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE + BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE };  v.t = D3DXVECTOR2(0, 1);
	//		vecPlane.push_back(v);
	//		v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE + BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE - BLOCK_SIZE }; v.t = D3DXVECTOR2(1, 0);
	//		vecPlane.push_back(v);
	//		v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE , 0, fMaxZ - i * BLOCK_SIZE - BLOCK_SIZE }; v.t = D3DXVECTOR2(1, 1);
	//		vecPlane.push_back(v);
	//	
	//		CTile* pTile = new CTile;
	//		pTile->SetVertex(vecPlane);
	//	
	//		pTile->SetPlaneTexture(g_pTextureManager->GetTexture("images/Albedo00.jpg"));
	//		m_vecTile.push_back(pTile);
	//		vecPlane.clear();
	//	}
	//}

	D3DXCreateBox(g_pD3DDevice, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, &m_pCubeTile, NULL);
	
	for (float i = fMinZ + (BLOCK_SIZE / 2.0f); i < fMaxZ; i+=(BLOCK_SIZE/2.0f))
	{
		for (float j = fMinX + (BLOCK_SIZE / 2.0f); j < fMaxX; j += (BLOCK_SIZE / 2.0f))
		{
			CTile* pTile = new CTile;
			ST_CUBE cube;
			cube.fLength = BLOCK_SIZE;
			cube.vCenter = D3DXVECTOR3((float)j, 0, (float)i);
			pTile->SetCube(cube);

			pTile->SetMeshCubeTile(m_pCubeTile);
			pTile->SetPlaneTexture(g_pTextureManager->GetTexture("images/Albedo00.jpg"));
			
			m_vecTile.push_back(pTile);
		}
	}


	ZeroMemory(&m_stMtlTile, sizeof(D3DMATERIAL9));
	m_stMtlTile.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlTile.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlTile.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}


void CField::Render()
{
	//g_pD3DDevice->SetMaterial(&m_stMtlTile);

	for each(auto c in m_vecTile)
	{
		c->Render();
	}
		
}

void CField::Update()
{
	
}
