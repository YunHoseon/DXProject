#include "stdafx.h"
#include "CDebugSphere.h"


CDebugSphere::CDebugSphere()
{
	m_vPosition = m_sphere.vCenter;
	D3DXMatrixIdentity(&m_matWorld);
	
	m_stInputKey.moveFowardKey = 'W';
	m_stInputKey.moveLeftKey = 'A';
	m_stInputKey.moveBackKey = 'S';
	m_stInputKey.moveRightKey = 'D';
	m_stInputKey.interactableKey1 = 'F';
	m_stInputKey.interactableKey2 = 'G';
	m_stInputKey.interactableKey3 = 'H';
}

CDebugSphere::~CDebugSphere()
{
}

void CDebugSphere::Setup()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void CDebugSphere::Update()
{
	D3DXMATRIXA16 matS, matR, matT;
	D3DXVECTOR3 vPosition = m_vPosition;

	if (InputManager->GetPressedKey() == m_stInputKey.moveFowardKey
		&& InputManager->IsKeyPressed(InputManager->GetPressedKey()))
	{
		vPosition = m_vPosition - (D3DXVECTOR3(0, 0, -1) * 0.1f);
		std::cout << "↑" << std::endl;
	}
	if (InputManager->GetPressedKey() == m_stInputKey.moveLeftKey
		&& InputManager->IsKeyPressed(InputManager->GetPressedKey()))
	{
		vPosition = m_vPosition + (D3DXVECTOR3(-1, 0, 0) * 0.1f);
	}
	if (InputManager->GetPressedKey() == m_stInputKey.moveBackKey
		&& InputManager->IsKeyPressed(InputManager->GetPressedKey()))
	{
		vPosition = m_vPosition + (D3DXVECTOR3(0, 0, -1) * 0.1f);
	}
	if (InputManager->GetPressedKey() == m_stInputKey.moveRightKey
		&& InputManager->IsKeyPressed(InputManager->GetPressedKey()))
	{
		vPosition = m_vPosition - (D3DXVECTOR3(-1, 0, 0) * 0.1f);
	}
	if (InputManager->GetPressedKey() == m_stInputKey.interactableKey1
		&& InputManager->IsKeyPressed(InputManager->GetPressedKey()))
	{
		std::cout << "상호작용" << std::endl;
	}

	m_vPosition = vPosition;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matT;
}

void CDebugSphere::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
	m_pMeshSphere->DrawSubset(0);
}
