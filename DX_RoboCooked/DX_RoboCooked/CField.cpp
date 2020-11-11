#include "stdafx.h"
#include "CField.h"



CField::CField()
{
}


CField::~CField()
{
	for each(auto c in m_vecTile)
		SafeDelete(c);
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
	for (int i = 0; i < iHeight; ++i)
	{
		for (int j = 0; j < iWidth; ++j)
		{/*
			v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE }; v.t = D3DXVECTOR2(0, 0);
			vecPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE + BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE }; v.t = D3DXVECTOR2(1, 0);
			vecPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE -BLOCK_SIZE }; v.t = D3DXVECTOR2(0, 1);
			vecPlane.push_back(v);

			v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE + BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE };  v.t = D3DXVECTOR2(0, 1);
			vecPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE + BLOCK_SIZE, 0, fMaxZ - i * BLOCK_SIZE - BLOCK_SIZE }; v.t = D3DXVECTOR2(1, 0);
			vecPlane.push_back(v);
			v.p = D3DXVECTOR3{ fMinX + j * BLOCK_SIZE , 0, fMaxZ - i * BLOCK_SIZE - BLOCK_SIZE }; v.t = D3DXVECTOR2(1, 1);
			vecPlane.push_back(v);
		*/
			CTile* pTile = new CTile;
			//pTile->SetVertex(vecPlane);
			ST_CUBE cube;
			cube.fLength = BLOCK_SIZE;
			//cube.vCenter = D3DXVECTOR3()


			pTile->SetPlaneTexture(g_pTextureManager->GetTexture("images/Albedo00.jpg"));
			m_vecTile.push_back(pTile);
			//vecPlane.clear();
		}
	}


	ZeroMemory(&m_stMtlTile, sizeof(D3DMATERIAL9));
	m_stMtlTile.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlTile.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlTile.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}


void CField::Render()
{
	g_pD3DDevice->SetMaterial(&m_stMtlTile);

	for each(auto c in m_vecTile)
	{
		c->Render();
	}
		
}

void CField::Update()
{
	
}
