#include "stdafx.h"
#include "CDebugPlayer2.h"

#include "CBoxCollision.h"
#include "CSphereCollision.h"

CDebugPlayer2::CDebugPlayer2(IInteractCenter* pInteractCenter): CCharacter(1)
{
	m_pInteractCenter = pInteractCenter;
	//m_vPosition = m_cube.vCenter;
	m_vPosition = D3DXVECTOR3(-2, 0, 0);
	m_matWorld = m_matS * m_matR * m_matT;
	D3DXMatrixIdentity(&m_matWorld);

	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::Player2KeyChange, this);
}

CDebugPlayer2::~CDebugPlayer2()
{
	SafeDelete(m_pInteractCollision);
}

void CDebugPlayer2::Setup()
{
	//m_pCollision = new CBoxCollision(g_vZero, D3DXVECTOR3(1, 1, 1), &m_matWorld);
	m_pCollision = new CSphereCollision(g_vZero, 0.5f, &m_matWorld);
	m_pInteractCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0.5f), D3DXVECTOR3(0.5f, 0.5f, 0.5f), &m_matWorld);
	//D3DXCreateBox(g_pD3DDevice, 0.8f, 0.8f, 0.8f, &m_pMesh, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);
}
/*
void CDebugPlayer2::Update()
{
	Move();
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
}

void CDebugPlayer2::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetMaterial(&m_stMtlCube);
	m_pMeshCube->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	_DEBUG_COMMENT if (m_pCollision)
		_DEBUG_COMMENT m_pCollision->Render();
}

void CDebugPlayer2::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::KeyPress:
		PressKey(_value);
		break;
	case eEvent::KeyRelease:
		ReleaseKey(_value);
		break;
	case eEvent::Player2KeyChange:
		SetKeyChange(_value);
		break;
	}
}

void CDebugPlayer2::PressKey(void* _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);

	if (data->wKey == m_stInputKey.moveFowardKey)
	{
		Rotate(0);
		m_fSpeed = m_fBaseSpeed;
	}
	if (data->wKey == m_stInputKey.moveLeftKey)
	{
		if (m_fRotY - 0.1f < 0.f)
			m_fRotY += D3DX_PI * 2.f;
		Rotate(D3DX_PI * 1.5f);
		m_fSpeed = m_fBaseSpeed;
	}
	if (data->wKey == m_stInputKey.moveBackKey)
	{
		Rotate(D3DX_PI);
		m_fSpeed = m_fBaseSpeed;
	}
	if (data->wKey == m_stInputKey.moveRightKey)
	{
		if (m_fRotY + 0.1f > D3DX_PI * 2.f)
			m_fRotY -= D3DX_PI * 2.f;
		Rotate(D3DX_PI * 0.5f);
		m_fSpeed = m_fBaseSpeed;
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

	_DEBUG_COMMENT cout << m_fRotY << endl;
}

void CDebugPlayer2::ReleaseKey(void* _value)
{
	_DEBUG_COMMENT std::cout << "Release" << std::endl;
	m_fSpeed = 0.0f;
}

void CDebugPlayer2::Move()
{
	if (m_fSpeed == 0.0f)
		return;

	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &m_matR);

	m_vPosition += m_vDirection * m_fSpeed;

	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
}

void CDebugPlayer2::Rotate(float fTargetRot)
{
	D3DXQUATERNION stLerpRot, stCurrentRot, stTargetRot;
	D3DXQuaternionRotationAxis(&stCurrentRot, &D3DXVECTOR3(0, 1, 0), m_fRotY);
	D3DXQuaternionRotationAxis(&stTargetRot, &D3DXVECTOR3(0, 1, 0), fTargetRot);

	D3DXQuaternionSlerp(&stLerpRot, &stCurrentRot, &stTargetRot, 0.3f);
	D3DXMatrixRotationQuaternion(&m_matR, &stLerpRot);

	D3DXVECTOR3 dummy;
	D3DXQuaternionToAxisAngle(&stLerpRot, &dummy, &m_fRotY);
}

void CDebugPlayer2::SetKeyChange(void* _value)
{
	ST_PLAYER_INPUTKEY *data = static_cast<ST_PLAYER_INPUTKEY*>(_value);
	m_stInputKey = *data;
}

*/