#include "stdafx.h"
#include "CDebugCube.h"



CDebugCube::CDebugCube()
{
	m_stInputKey.moveFowardKey = VK_UP;
	m_stInputKey.moveLeftKey = VK_LEFT;
	m_stInputKey.moveBackKey = VK_DOWN;
	m_stInputKey.moveRightKey = VK_RIGHT;
	m_stInputKey.interactableKey1 = VK_OEM_COMMA;
	m_stInputKey.interactableKey2 = VK_OEM_PERIOD;
	m_stInputKey.interactableKey3 = VK_OEM_2;
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
	switch (InputManager->GetPressedKey())
	{

		default:
			break;
	}
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
