#include "stdafx.h"
#include "CDebugCube.h"


CDebugCube::CDebugCube() :
	m_fSpeed(0.1f)
{
	m_vPosition = m_cube.vCenter;
	D3DXMatrixIdentity(&m_matWorld);
	
	//m_stInputKey.moveFowardKey = 'W';
	
	g_EventManager->Attach(EEvent::E_KeyPress, this);
	g_EventManager->Attach(EEvent::E_KeyRelease, this);
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
	m_matWorld = m_matS * m_matR * m_matT;
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	m_pMeshCube->DrawSubset(0);
}

void CDebugCube::OnEvent(EEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case EEvent::E_KeyPress:
		PressKey(_value);
		break;
	case EEvent::E_KeyRelease:
		ReleaseKey(_value);
		break;
	}
}

void CDebugCube::PressKey(void* _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);
	
	if (data->wKey == m_stInputKey.moveFowardKey)	//이벤트 추가해야함
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

void CDebugCube::ReleaseKey(void* _value)
{
}

void CDebugCube::Move(D3DXVECTOR3 _vecMove)
{
	D3DXVECTOR3 vPosition = m_vPosition;
	vPosition += _vecMove;
	m_vPosition = vPosition;
	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}
