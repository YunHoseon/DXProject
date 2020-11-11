#include "stdafx.h"
#include "CDebugCube.h"


CDebugCube::CDebugCube()
{
}


CDebugCube::~CDebugCube()
{
}

void CDebugCube::Setup()
{
	D3DXCreateBox(g_pD3DDevice, 0.8f, 0.8f, 0.8f, &m_pMeshCube, NULL);

	ZeroMemory(&m_stMtlCube, sizeof(D3DMATERIAL9));
	m_stMtlCube.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlCube.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlCube.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void CDebugCube::Update()
{
}

void CDebugCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	matWorld = matS * matR;

	D3DXMatrixIdentity(&matWorld);
	matWorld._41 = m_cube.vCenter.x;
	matWorld._42 = m_cube.vCenter.y;
	matWorld._43 = m_cube.vCenter.z;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	m_pMeshCube->DrawSubset(0);
}
