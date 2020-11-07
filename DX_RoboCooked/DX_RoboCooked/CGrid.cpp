#include "stdafx.h"
#include "CGrid.h"
#include "CPyramid.h"


CGrid::CGrid()
	:m_PlaneTexture(NULL)
{
}

CGrid::~CGrid()
{
	for each(auto p in m_vecPyramid)
	{
		SafeDelete(p);
	}
	m_vecPyramid.clear();
}

void CGrid::Setup(int nNumHalfTile, float fInterval)
{
	ZeroMemory(&m_stMt1, sizeof(D3DMATERIAL9));
	m_stMt1.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	m_stMt1.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMt1.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	
	float fMax = nNumHalfTile * fInterval;
	float fMin = -fMax;
	ST_PC_VERTEX	vc;

	//Grid
	for(int i = 1; i <= nNumHalfTile; ++i)
	{
		if (i % 5 == 0)
			vc.c = D3DCOLOR_XRGB(255, 255, 255);
		else
			vc.c = D3DCOLOR_XRGB(128, 128, 128);

		vc.p = D3DXVECTOR3(fMin, 0, i * fInterval);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(fMax, 0, i * fInterval);
		m_vecVertex.push_back(vc);

		vc.p = D3DXVECTOR3(fMin, 0, -i * fInterval);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(fMax, 0, -i * fInterval);
		m_vecVertex.push_back(vc);

		vc.p = D3DXVECTOR3(i * fInterval, 0, fMin);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(i * fInterval, 0, fMax);
		m_vecVertex.push_back(vc);

		vc.p = D3DXVECTOR3(-i * fInterval, 0, fMin);
		m_vecVertex.push_back(vc);
		vc.p = D3DXVECTOR3(-i * fInterval, 0, fMax);
		m_vecVertex.push_back(vc);
	}

	vc.c = D3DCOLOR_XRGB(240, 100, 100);
	vc.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(vc);
	vc.p = D3DXVECTOR3(fMax, 0, 0);	m_vecVertex.push_back(vc);

	vc.c = D3DCOLOR_XRGB(100, 240, 100);
	vc.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(vc);
	vc.p = D3DXVECTOR3(0, fMax, 0);	m_vecVertex.push_back(vc);

	vc.c = D3DCOLOR_XRGB(100, 100, 240);
	vc.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(vc);
	vc.p = D3DXVECTOR3(0, 0, fMax);	m_vecVertex.push_back(vc);


	CPyramid *pPyramid = NULL;
	D3DXMATRIXA16 matR;

	pPyramid = new CPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(240, 100, 100), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new CPyramid;
	D3DXMatrixRotationZ(&matR, D3DX_PI);
	pPyramid->Setup(D3DCOLOR_XRGB(100, 240, 100), matR);
	m_vecPyramid.push_back(pPyramid);

	pPyramid = new CPyramid;
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	pPyramid->Setup(D3DCOLOR_XRGB(100, 100, 240), matR);
	m_vecPyramid.push_back(pPyramid);


}

void CGrid::Render()
{
	//Grid
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(NULL, 0);
	D3DXMATRIXA16 matI2;
	D3DXMatrixIdentity(&matI2);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI2);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetTexture(NULL, 0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	for each(auto p in m_vecPyramid)
		p->Render();


}
