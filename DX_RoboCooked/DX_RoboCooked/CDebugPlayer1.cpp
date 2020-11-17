#include "stdafx.h"
#include "CDebugPlayer1.h"
#include "CBoxCollision.h"
#include "CSphereCollision.h"


CDebugPlayer1::CDebugPlayer1() 
	:m_fSpeed(0.02f)
	, m_fRotY(0.0f)
{
	m_vPosition = m_sphere.vCenter;
	D3DXMatrixIdentity(&m_matWorld);
	
	g_EventManager->Attach(EEvent::E_KeyPress, this);
	g_EventManager->Attach(EEvent::E_KeyRelease, this);
	g_EventManager->Attach(EEvent::E_Player1KeyChange, this);
}

CDebugPlayer1::~CDebugPlayer1()
{
}

void CDebugPlayer1::Setup()
{
	m_pCollision = new CSphereCollision(m_vPosition, 0.5f, &m_matWorld);
	m_pInteractCollision = new CBoxCollision(m_vPosition + D3DXVECTOR3(0, 0, 0.5f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), &m_matWorld);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void CDebugPlayer1::Update()
{
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pInteractCollision)
		m_pInteractCollision->Update();
	if (m_pCollision)
		m_pCollision->Update();
}

void CDebugPlayer1::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlSphere);
	m_pMeshSphere->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	_DEBUG_COMMENT if (m_pInteractCollision)
		_DEBUG_COMMENT m_pInteractCollision->Render();
	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void CDebugPlayer1::OnEvent(EEvent eEvent, void* _value)
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

void CDebugPlayer1::PressKey(void* _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);

	if (data->wKey == m_stInputKey.moveFowardKey)
	{
		m_fRotY = 0.0f;
		Rotate();
		Move(D3DXVECTOR3(0, 0, 1) * m_fSpeed);
	}
	if (data->wKey == m_stInputKey.moveLeftKey)
	{
		m_fRotY = D3DX_PI * 1.5f;
		Rotate();
		Move((D3DXVECTOR3(-1, 0, 0) * m_fSpeed));
	}
	if (data->wKey == m_stInputKey.moveBackKey)
	{
		m_fRotY = D3DX_PI;
		Rotate();
		Move(D3DXVECTOR3(0, 0, -1) * m_fSpeed);
	}
	if (data->wKey == m_stInputKey.moveRightKey)
	{
		m_fRotY = D3DX_PI * 0.5f;
		Rotate();
		Move(D3DXVECTOR3(1, 0, 0) * m_fSpeed);
	}
	if (data->wKey == m_stInputKey.interactableKey1)
	{
		g_SoundManager->PlaySFX("Melem");
	}
	if (data->wKey == m_stInputKey.interactableKey2)
	{
		g_SoundManager->PlaySFX("Melem");
	}
	if (data->wKey == m_stInputKey.interactableKey3)
	{
		g_SoundManager->PlaySFX("Melem");
	}
}

void CDebugPlayer1::ReleaseKey(void* _value)
{
	std::cout << "Release" << std::endl;
}

void CDebugPlayer1::Move(D3DXVECTOR3 _vecMove)
{
	D3DXVECTOR3 vPosition = m_vPosition;

	vPosition += _vecMove;

	m_vPosition = vPosition;

	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CDebugPlayer1::Rotate()
{
	D3DXQUATERNION qRot;
	D3DXQuaternionRotationAxis(&qRot, &D3DXVECTOR3(0, 1, 0), m_fRotY);
	D3DXMatrixRotationQuaternion(&m_matR, &qRot);
}

void CDebugPlayer1::SetKeyChange(void* _value)
{
	ST_PLAYER_INPUTKEY *data = static_cast<ST_PLAYER_INPUTKEY*>(_value);
	m_stInputKey = *data;
}

