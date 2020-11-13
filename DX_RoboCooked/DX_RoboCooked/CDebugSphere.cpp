#include "stdafx.h"
#include "CDebugSphere.h"


CDebugSphere::CDebugSphere() :
	m_fSpeed(0.1f)
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

	g_EventManager->Attach(EEvent::E_KeyPress, this);
	g_EventManager->Attach(EEvent::E_KeyRelease, this);
	g_EventManager->Attach(EEvent::E_Player1KeyChange, this);
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
	case EEvent::E_KeyPress:
		PressKey(_value);
		break;
	case EEvent::E_KeyRelease:
		ReleaseKey(_value);
		break;
	case EEvent::E_Player1KeyChange:
		SetKeyChange(_value);
		break;
	}
}

void CDebugSphere::PressKey(void* _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);

	if (data->wKey == m_stInputKey.moveFowardKey)
	{
		Move(D3DXVECTOR3(0, 0, 1) * m_fSpeed);
	}
	if (data->wKey == m_stInputKey.moveLeftKey)
	{
		Move((D3DXVECTOR3(-1, 0, 0) * m_fSpeed));
	}
	if (data->wKey == m_stInputKey.moveBackKey)
	{
		Move(D3DXVECTOR3(0, 0, -1) * m_fSpeed);
	}
	if (data->wKey == m_stInputKey.moveRightKey)
	{
		Move(D3DXVECTOR3(1, 0, 0) * m_fSpeed);
	}
	if (data->wKey == m_stInputKey.interactableKey1)
	{

	}
	if (data->wKey == m_stInputKey.interactableKey2)
	{

	}
	if (data->wKey == m_stInputKey.interactableKey3)
	{

	}
}

void CDebugSphere::ReleaseKey(void* _value)
{
	std::cout << "Release" << std::endl;
}

void CDebugSphere::Move(D3DXVECTOR3 _vecMove)
{
	D3DXVECTOR3 vPosition = m_vPosition;

	vPosition += _vecMove;

	m_vPosition = vPosition;

	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CDebugSphere::SetKeyChange(void* _value)
{
	memcpy(&m_stInputKey, &_value, sizeof(ST_PLAYER_INPUTKEY));
}

