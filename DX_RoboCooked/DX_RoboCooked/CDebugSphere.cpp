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

	g_EventManager->Attach(EEvent::E_EventMovePlayer1, this);
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

	//if (InputManager->IsKeyPressed(m_stInputKey.moveFowardKey))
	//{
	//	vPosition += (D3DXVECTOR3(0, 0, 1) * 0.1f);
	//}
	//if (InputManager->IsKeyPressed(m_stInputKey.moveLeftKey))
	//{
	//	vPosition += (D3DXVECTOR3(-1, 0, 0) * 0.1f);
	//}
	//if (InputManager->IsKeyPressed(m_stInputKey.moveBackKey))
	//{
	//	vPosition += (D3DXVECTOR3(0, 0, -1) * 0.1f);
	//}
	//if (InputManager->IsKeyPressed(m_stInputKey.moveRightKey))
	//{
	//	vPosition += (D3DXVECTOR3(1, 0, 0) * 0.1f);
	//}


	
	if (InputManager->IsKeyPressed(m_stInputKey.interactableKey1))
	{
		std::cout << "상호작용" << std::endl;
	}

	m_vPosition = vPosition;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matT;
}

void CDebugSphere::Render()
{
	m_matWorld = m_matS * m_matR * m_matT;
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
	m_pMeshSphere->DrawSubset(0);
}

void CDebugSphere::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_EventMovePlayer1:
		Move(_value);
		break;
	}
}

void CDebugSphere::Move(void* _value)
{
	ST_MoveEvent *data = static_cast<ST_MoveEvent*>(_value);
	D3DXVECTOR3 vPosition = m_vPosition;
	
	/*ST_BitrhDayEvent data{ name, age };
	NotifyEvent(EEvent::E_BIRTHDAY, (void*)&data);*/

	//ST_BitrhDayEvent *data = static_cast<ST_BitrhDayEvent*>(_value);

	if (data->wKey == 'W')
	{
		vPosition += (D3DXVECTOR3(0, 0, 1) * 0.1f);
	}
	if (data->wKey == 'A')
	{
		vPosition += (D3DXVECTOR3(-1, 0, 0) * 0.1f);
	}
	if (data->wKey == 'S')
	{
		vPosition += (D3DXVECTOR3(0, 0, -1) * 0.1f);
	}
	if (data->wKey == 'D')
	{
		vPosition += (D3DXVECTOR3(1, 0, 0) * 0.1f);
	}

	
	
	m_vPosition = vPosition;

	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
}
