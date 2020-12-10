#include "stdafx.h"
#include "CDebugPlayer1.h"
#include "CBoxCollision.h"
#include "CGameScene.h"
#include "CSphereCollision.h"


CDebugPlayer1::CDebugPlayer1(IInteractCenter* pInteractCenter)
	: CCharacter(0)
	//,m_pMeshSphere(nullptr)
	//, m_ElapsTimeF(0), m_ElapsTimeG(0), m_ElapsTimeH(0)
{
	m_pInteractCenter = pInteractCenter;
	
	m_pCollision = new CSphereCollision(g_vZero, 0.5f, &m_matWorld);
	m_pInteractCollision = new CBoxCollision(D3DXVECTOR3(0, 0, 0.5f), D3DXVECTOR3(.8f, .8f, .8f), &m_matWorld);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);

	SetPosition(g_vZero);

	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::Player1KeyChange, this);

}

CDebugPlayer1::~CDebugPlayer1()
{
	//SafeRelease(m_pMeshSphere);
	SafeDelete(m_pInteractCollision);
	SafeDelete(m_pCollision);
	SafeRelease(m_pMesh);
}

void CDebugPlayer1::Setup()
{

}
/*
void CDebugPlayer1::Update()
{
	Move();
	m_vGrabPartsPosition.x = m_vPosition.x;
	m_vGrabPartsPosition.z = m_vPosition.z;

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

void CDebugPlayer1::OnEvent(eEvent eEvent, void* _value)
{
	switch (eEvent)
	{
	case eEvent::KeyPress:
		PressKey(_value);
		break;
	case eEvent::KeyRelease:
		ReleaseKey(_value);
		break;
	case eEvent::Player1KeyChange:
		SetKeyChange(_value);
		break;
	default:
		break;
	}
}

void CDebugPlayer1::PressKey(void* _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);
	DWORD CurrentTime = GetTickCount();
	float fTestTime = 700.0f;
	if (data->wKey == m_stInputKey.moveFowardKey)
	{
		Rotate(0);
	}
	if (data->wKey == m_stInputKey.moveLeftKey)
	{
		if (m_fRotY - 0.5f < 0.f)
			m_fRotY += D3DX_PI * 2.f;
		Rotate(D3DX_PI * 1.5f);
	}
	if (data->wKey == m_stInputKey.moveBackKey)
	{
		Rotate(D3DX_PI);
	}
	if (data->wKey == m_stInputKey.moveRightKey)
	{
		if (m_fRotY + 0.5f > D3DX_PI * 2.f)
			m_fRotY -= D3DX_PI * 2.f;
		Rotate(D3DX_PI * 0.5f);
	}
	if (data->wKey == m_stInputKey.interactableKey1)
	{
		if (CurrentTime - m_ElapsTimeF >  fTestTime)
		{
			if (m_ePlayerState == ePlayerState::None)
			{
				m_pInteractCenter->GetInteractObject(this);
			}
			else if (m_ePlayerState == ePlayerState::Grab)
			{
				m_pInteractCenter->ThrowParts(this, m_pParts, m_vDirection);
			}
			g_SoundManager->PlaySFX("Melem");
			m_ElapsTimeF = CurrentTime;
		}
	}
	if (data->wKey == m_stInputKey.interactableKey2)
	{
		if (CurrentTime - m_ElapsTimeG >  fTestTime)
		{
			if (m_ePlayerState == ePlayerState::Grab)
			{
				m_pParts->PartsRotate();
			}
			g_SoundManager->PlaySFX("Melem");

			m_ElapsTimeG = CurrentTime;
		}
	}
	if (data->wKey == m_stInputKey.interactableKey3)
	{
		if (CurrentTime - m_ElapsTimeH >  fTestTime)
		{
			g_SoundManager->PlaySFX("Melem");
			m_ElapsTimeF = CurrentTime;
		}
	}

	//_DEBUG_COMMENT cout << m_fRotY << endl;
}

void CDebugPlayer1::ReleaseKey(void* _value)
{
	_DEBUG_COMMENT std::cout << "Release" << std::endl;
}

void CDebugPlayer1::Move()
{
	m_vVelocity += m_vAcceleration;
	m_vPosition += m_vVelocity;

	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
	SetForce();
}

void CDebugPlayer1::Rotate(float fTargetRot)
{

	D3DXQUATERNION stLerpRot, stCurrentRot, stTargetRot;
	D3DXQuaternionRotationAxis(&stCurrentRot, &D3DXVECTOR3(0, 1, 0), m_fRotY);
	D3DXQuaternionRotationAxis(&stTargetRot, &D3DXVECTOR3(0, 1, 0), fTargetRot);

	D3DXQuaternionSlerp(&stLerpRot, &stCurrentRot, &stTargetRot, 0.3f);
	D3DXMatrixRotationQuaternion(&m_matR, &stLerpRot);

	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &m_matR);
	m_matWorld = m_matS * m_matR * m_matT;
	SetForce(m_vDirection * m_fBaseSpeed);
	
	if (m_pCollision)
		m_pCollision->Update();

	D3DXVECTOR3 dummy;
	D3DXQuaternionToAxisAngle(&stLerpRot, &dummy, &m_fRotY);
}

void CDebugPlayer1::SetKeyChange(void* _value)
{
	ST_PLAYER_INPUTKEY *data = static_cast<ST_PLAYER_INPUTKEY*>(_value);
	m_stInputKey = *data;
}
*/