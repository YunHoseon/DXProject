#include "stdafx.h"
#include "CDebugCube.h"


CDebugCube::CDebugCube()
{
	m_vPosition = m_cube.vCenter;
	D3DXMatrixIdentity(&m_matWorld);

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
	/*D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
*/
	D3DXMATRIXA16 matS, matR, matT;
	D3DXVECTOR3 vPosition = m_vPosition;
	
	if(InputManager->GetPressedKey() == m_stInputKey.moveFowardKey 
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

void CDebugCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	m_pMeshCube->DrawSubset(0);
}
