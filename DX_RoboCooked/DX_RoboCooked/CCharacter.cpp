#include "stdafx.h"
#include "CCharacter.h"
#include "CGameScene.h"
#include "ICollisionArea.h"
#include "CCrowdControl.h"
#include "CCCNone.h"
#include "CSkinnedMesh.h"

CCharacter::CCharacter(int nPlayerNum) : m_pSkinnedMesh(nullptr),
                                         m_ePlayerState(ePlayerState::None),
                                         m_pInteractCollision(nullptr),
                                         m_vGrabPartsPosition(0, 1, 0),
                                         m_pParts(nullptr),
                                         m_arrElapsedTime({0, 0, 0}),
                                         m_arrCoolDown({0, 0, 3}),
                                         m_arrKeyDown({false, false, false}),
                                         m_isMoveKeyDown(false),
                                         m_pInputKey(InputManager->GetInputKey(nPlayerNum)),
                                         //m_pMesh(nullptr),
                                         //m_stMtlSphere({}),
                                         m_fMinThrowPower(0.01f),
                                         m_fMaxThrowPower(0.1f),
                                         m_fThrowPower(m_fMinThrowPower),
                                         m_fThrowPowerUpSpeed(0.003f),
                                         m_pCC(nullptr),
                                         m_isDummy(false),
                                         m_vDefaultPosition(0, 0, 0)
{
	m_fBaseSpeed = 0.02f;

	/*ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);*/

	m_pCC = new CCCNone;
}

CCharacter::~CCharacter()
{
	//SafeDelete(m_pInteractCollision);
	//SafeRelease(m_pMesh);
	SafeDelete(m_pCC);
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pInteractCollision);
}

void CCharacter::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	m_pSkinnedMesh->Render(nullptr);

	_DEBUG_COMMENT if (m_pInteractCollision)
		_DEBUG_COMMENT m_pInteractCollision->Render();
	if (m_pCollision)
		m_pCollision->Render();
}

void CCharacter::Update()
{
	Move();
	SetAnimState();
	m_vGrabPartsPosition.x = m_vPosition.x;
	m_vGrabPartsPosition.y = m_vPosition.y + 1.0f;
	m_vGrabPartsPosition.z = m_vPosition.z;

	m_pSkinnedMesh->Update();

	if (m_pInteractCollision)
		m_pInteractCollision->Update();
	if (m_pCollision)
		m_pCollision->Update();
}

bool CCharacter::OnEvent(eEvent eEvent, void* _value)
{
	if (m_pInteractCenter->GetStop())
		return true;
	
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
	return true;
}

void CCharacter::PressKey(void* _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);
	const float& CurrentTime = g_pTimeManager->GetLastUpdateTime();
	if (data->wKey == m_pInputKey->moveFowardKey)
	{
		if (m_pCC->IsMovable() == false)
			return;
		if (m_pParts && m_pCC->StopWithParts())
			return; 

		Rotate(0);
	}
	else if (data->wKey == m_pInputKey->moveLeftKey)
	{
		if (m_pCC->IsMovable() == false)
			return;
		if (m_pParts && m_pCC->StopWithParts())
			return;
		if (!m_pCC->ReverseRotate())
		{
			if (m_fRotY - 0.5f < 0.f)
				m_fRotY += D3DX_PI * 2.f;
		}
		else
		{
			if (m_fRotY + 0.5f > D3DX_PI * 2.f)
				m_fRotY -= D3DX_PI * 2.f;
		}
		
		Rotate(D3DX_PI * 1.5f );
	}
	else if (data->wKey == m_pInputKey->moveBackKey)
	{
		if (m_pCC->IsMovable() == false)
			return;
		if (m_pParts && m_pCC->StopWithParts())
			return;

		Rotate(D3DX_PI);
	}
	else if (data->wKey == m_pInputKey->moveRightKey)
	{
		if (m_pCC->IsMovable() == false)
			return;
		if (m_pParts && m_pCC->StopWithParts())
			return;
		if (!m_pCC->ReverseRotate())
		{
			if (m_fRotY + 0.5f > D3DX_PI * 2.f)
				m_fRotY -= D3DX_PI * 2.f;
		}
		else
		{
			if (m_fRotY - 0.5f < 0.f)
				m_fRotY += D3DX_PI * 2.f;
		}

		Rotate(D3DX_PI * 0.5f);
	}
	else if (data->wKey == m_pInputKey->interactableKey1)
	{
		switch (m_ePlayerState)
		{
		case ePlayerState::None:
			{
				if(m_arrKeyDown[0] == false)
				{
					m_arrKeyDown[0] = true;
					m_pInteractCenter->GetInteractObject(this);
					g_SoundManager->PlaySFX("Melem");	
				}
			}
			break;
		case ePlayerState::Grab:
			{
				if (m_arrKeyDown[0] == false)
					m_arrKeyDown[0] = true;

				if (m_fThrowPower < m_fMaxThrowPower)
					m_fThrowPower += m_fThrowPowerUpSpeed * TimeRevision;
				if (m_fThrowPower > m_fMaxThrowPower)
					m_fThrowPower = m_fMaxThrowPower;
			
				_DEBUG_COMMENT cout << "throw power : " << m_fThrowPower << endl;
			}
			break;
		default: ;
		}
	}
	else if (data->wKey == m_pInputKey->interactableKey2)
	{
		switch (m_ePlayerState)
		{
		case ePlayerState::None:
		{
			if (m_arrKeyDown[1] == false)
			{
				m_arrKeyDown[1] = true;
			}
		}
		break;
		case ePlayerState::Grab:
		{
			if (m_arrKeyDown[1] == false)
			{
				m_arrKeyDown[1] = true;
				if (m_pParts)
				{
					m_pParts->PartsRotate();
					g_SoundManager->PlaySFX("Melem");
				}
			}
		}
		break;
		default:;
		}

	}
	else if (data->wKey == m_pInputKey->interactableKey3)
	{
		if(m_arrKeyDown[2] == false)
		{
			m_arrKeyDown[2] = true;
			if(CurrentTime - m_arrElapsedTime[2] > m_arrCoolDown[2])
			{
				//???? -> ?????? ??????????
				D3DXVECTOR3 jump = m_vDirection;
				jump.y += .2f;
				D3DXVec3Normalize(&jump, &jump);
				SetPosition(m_vPosition.x, m_vPosition.y + 0.1f, m_vPosition.z);
				SetAcceleration(jump * 0.4f * TimeRevision);
				g_SoundManager->PlaySFX("Melem");
				m_arrElapsedTime[2] = CurrentTime;
			}
			//_DEBUG_COMMENT cout << "current time : " << g_pTimeManager->GetElapsedTime() << endl;
			_DEBUG_COMMENT cout << "cool down : " << CurrentTime - m_arrElapsedTime[2] <<endl;
		}
	}

}

void CCharacter::ReleaseKey(void* _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);
	const float& CurrentTime = g_pTimeManager->GetLastUpdateTime();
	if (data->wKey == m_pInputKey->interactableKey1)
	{
		switch (m_ePlayerState)
		{
		case ePlayerState::None: 
			if (m_pParts)
				SetPlayerState(ePlayerState::Grab);
			break;
		case ePlayerState::Grab: 
			SetPlayerState(ePlayerState::None);
			m_pParts->ThrowParts(m_vDirection * m_fThrowPower * TimeRevision);
			m_pParts = nullptr;
			
			g_SoundManager->PlaySFX("Melem");
			m_fThrowPower = m_fMinThrowPower;
			break;
		default: ;
		}
		m_arrKeyDown[0] = false;
	}
	else if (data->wKey == m_pInputKey->interactableKey2)
	{
		switch (m_ePlayerState)
		{
		case ePlayerState::None: 
			break;
		case ePlayerState::Grab:
			break;
		default: ;
		}
		m_arrKeyDown[1] = false;
	}
	else if (data->wKey == m_pInputKey->interactableKey3)
	{
		switch (m_ePlayerState)
		{
		case ePlayerState::None:
			break;
		case ePlayerState::Grab:
			break;
		default:;
		}
		m_arrKeyDown[2] = false;
	}
	
	_DEBUG_COMMENT else if (data->wKey == 'K')
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	m_fBaseSpeed += 0.01f;
	_DEBUG_COMMENT	cout << "chara speed : " << m_fBaseSpeed << endl;
	_DEBUG_COMMENT }
	_DEBUG_COMMENT else if (data->wKey == 'L')
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	m_fBaseSpeed -= 0.01f;
	_DEBUG_COMMENT	cout << "chara speed : " << m_fBaseSpeed << endl;
	_DEBUG_COMMENT }
}

void CCharacter::SetKeyChange(void* _value)
{
	ST_PLAYER_INPUTKEY* data = static_cast<ST_PLAYER_INPUTKEY*>(_value);
	m_pInputKey = data;
}

void CCharacter::Move()
{
	if (m_pCollision->GetIsCollide() == false && m_isMoveKeyDown)
	{
		AddForce(-m_vDirection * m_fBaseSpeed  * m_pCC->MultiplySpeed() * TimeRevision) ;
		m_isMoveKeyDown = false;
	}
	
	m_vVelocity += m_vAcceleration;
	m_vPosition += m_vVelocity;

	ST_TravelDistanceEvent data;
	data.fDistance = D3DXVec3Length(&m_vVelocity);
	g_EventManager->CallEvent(eEvent::TravelDistance, (void*)&data);

	if (m_vPosition.y < -100)
		Reset();
	
	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
	SetForce();
	
}

void CCharacter::Rotate(float fTargetRot)
{
	fTargetRot += m_pCC->ReverseRotate();
	fTargetRot = fTargetRot < D3DX_PI * 2 ? fTargetRot : fTargetRot - D3DX_PI * 2;
	m_isMoveKeyDown = true;
	D3DXQUATERNION stLerpRot, stCurrentRot, stTargetRot;
	D3DXQuaternionRotationAxis(&stCurrentRot, &D3DXVECTOR3(0, 1, 0), m_fRotY);
	D3DXQuaternionRotationAxis(&stTargetRot, &D3DXVECTOR3(0, 1, 0), fTargetRot);

	D3DXQuaternionSlerp(&stLerpRot, &stCurrentRot, &stTargetRot, 0.3f);
	D3DXMatrixRotationQuaternion(&m_matR, &stLerpRot);

	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &m_matR);
	m_matWorld = m_matS * m_matR * m_matT;

	SetForce(m_vDirection * m_fBaseSpeed * m_pCC->MultiplySpeed() * TimeRevision);

	if (m_pCollision)
		m_pCollision->Update();
	
	D3DXVECTOR3 dummy;
	D3DXQuaternionToAxisAngle(&stLerpRot, &dummy, &m_fRotY);
}

void CCharacter::AddForce(const D3DXVECTOR3& vForce)
{
	if (m_pParts)
		m_vAcceleration += vForce / (m_fMass + m_pParts->GetMass());
	else
		m_vAcceleration += vForce / m_fMass;
}

void CCharacter::SetForce(const D3DXVECTOR3& vForce)
{
	if (m_pParts)
		m_vAcceleration = vForce / (m_fMass + m_pParts->GetMass());
	else
		m_vAcceleration = vForce / m_fMass;
}

float CCharacter::GetMass()
{
	if (m_pParts)
		return m_fMass + m_pParts->GetMass();
	else
		return m_fMass;
}

void CCharacter::SetCC(CCrowdControl * cc)
{
	SafeDelete(m_pCC);
	m_pCC = cc;
	
}

void CCharacter::DeleteCC()
{
	SafeDelete(m_pCC);
	m_pCC = new CCCNone;
}

void CCharacter::Reset()
{
	SetPosition(m_vDefaultPosition);
	SetRotationY(D3DX_PI);
	m_vVelocity = g_vZero;
	m_vAcceleration = g_vZero;
}

void CCharacter::SetAnimState()
{
	if (!m_pSkinnedMesh)
		return;
	
	switch (m_pSkinnedMesh->GetCurrentAnimIndex())
	{
	case Idle:
	{
		if(m_pCC->GetID() != "NONE")
			m_pSkinnedMesh->SetAnimationIndexBlend(Stun);
		else if (D3DXVec3Length(&m_vVelocity) > EPSILON * 10)
			m_pSkinnedMesh->SetAnimationIndexBlend(Run);
	}
		break;
	case Run:
	{
		if (m_pCC->GetID() != "NONE")
			m_pSkinnedMesh->SetAnimationIndexBlend(Stun);
		else if (D3DXVec3Length(&m_vVelocity) < EPSILON * 10)
			m_pSkinnedMesh->SetAnimationIndexBlend(Idle);
	}
		break;
	case Spin:
	{
		
	}
		break;
	case Stun:
	{
		if (m_pCC->GetID() == "NONE")
		{
			if (D3DXVec3Length(&m_vVelocity) < EPSILON * 10)
				m_pSkinnedMesh->SetAnimationIndexBlend(Idle);
			else if (D3DXVec3Length(&m_vVelocity) > EPSILON * 10)
				m_pSkinnedMesh->SetAnimationIndexBlend(Run);
		}
	}
		break;
	default: break;
	}
}
