#include "stdafx.h"
#include "CCharacter.h"
#include "CGameScene.h"
#include "ICollisionArea.h"
#include "CCrowdControl.h"
#include "CCCNone.h"
#include "CDashShadow.h"
#include "CSkinnedMesh.h"
#include "CUICharge.h"

CCharacter::CCharacter(int nPlayerNum) :
	m_pSkinnedMesh(nullptr),
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
	//m_stMtl({}),
	m_fMinThrowPower(0.01f),
	m_fMaxThrowPower(0.3f),
	m_fThrowPower(m_fMinThrowPower),
	m_fThrowPowerUpSpeed(0.003f),
	m_fMaxSpeed(0.2f),
	m_pCC(nullptr),
	m_pOverlappedSandpile(nullptr),
	m_vDefaultPosition(0, 0, 0),
	m_pCharge(nullptr),
	m_isDash(false)
{
	m_fBaseSpeed = 0.02f;

	m_pCC = new CCCNone;
	m_pCharge = new CUICharge(&m_vPosition);
	m_pDashShadow = new CDashShadow;
	m_vDirection = D3DXVECTOR3(0, 0, -1);
}

CCharacter::~CCharacter()
{
	//SafeDelete(m_pInteractCollision);
	//SafeRelease(m_pMesh);
	SafeDelete(m_pCC);
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pInteractCollision);
	SafeDelete(m_pCharge);
	SafeDelete(m_pDashShadow);
}

void CCharacter::Render()
{
	g_pRenderShadowManager->GetApplyShadowShader()->SetMatrix("gWorldMatrix", &m_matWorld);
	g_pRenderShadowManager->GetApplyShadowShader()->SetBool("gIsSkinned", true);
	UINT numPasses = 0;
	
	g_pRenderShadowManager->GetApplyShadowShader()->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		g_pRenderShadowManager->GetApplyShadowShader()->BeginPass(i);
		{
			if (m_pSkinnedMesh)
			{
				m_pSkinnedMesh->RenderWithShadow(nullptr);
			}
		}
		g_pRenderShadowManager->GetApplyShadowShader()->EndPass();
	}

	g_pRenderShadowManager->GetApplyShadowShader()->End();
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	

	_DEBUG_COMMENT if (m_pInteractCollision)
		_DEBUG_COMMENT m_pInteractCollision->Render();
	if (m_pCollision)
		m_pCollision->Render();

	if (m_pCharge)
		m_pCharge->Render();

	if (m_pCC)
		m_pCC->Render();

	if (m_pDashShadow)
		m_pDashShadow->Render();
}

void CCharacter::Update()
{
	Move();
	SetAnimState();
	m_vGrabPartsPosition.x = m_vPosition.x;
	m_vGrabPartsPosition.y = m_vPosition.y + 1.0f;
	m_vGrabPartsPosition.z = m_vPosition.z;

	m_pSkinnedMesh->Update();
	m_isMoveKeyDown = false;
	m_isDash = false;
	if (m_pCC->IsEnd())
		DeleteCC();

	if (m_pInteractCollision)
		m_pInteractCollision->Update();
	if (m_pCollision)
		m_pCollision->Update();
	if (m_pDashShadow)
		m_pDashShadow->Update();
}

bool CCharacter::OnEvent(eEvent eEvent, void *_value)
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

void CCharacter::PressKey(void *_value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent *>(_value);
	const float &CurrentTime = g_pTimeManager->GetLastUpdateTime();
	if (data->wKey == m_pInputKey->moveFowardKey)
	{
		if (m_pCC->IsMovable() == false)
			return;
		if (m_pParts && m_pCC->StopWithParts())
			return;
		//g_SoundManager->PlaySFX("run_1");
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
		//g_SoundManager->PlaySFX("run_1");
		Rotate(D3DX_PI * 1.5f);
	}
	else if (data->wKey == m_pInputKey->moveBackKey)
	{
		if (m_pCC->IsMovable() == false)
			return;
		if (m_pParts && m_pCC->StopWithParts())
			return;
		//g_SoundManager->PlaySFX("run_1");
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
		//g_SoundManager->PlaySFX("run_1");
		Rotate(D3DX_PI * 0.5f);
	}
	else if (data->wKey == m_pInputKey->interactableKey1)
	{
		switch (m_ePlayerState)
		{
		case ePlayerState::None:
		{
			if (m_arrKeyDown[0] == false)
			{
				m_arrKeyDown[0] = true;
				m_pInteractCenter->GetInteractObject(this);
			}
		}
		break;
		case ePlayerState::Grab:
		{
			if (m_arrKeyDown[0] == false)
			{
				m_arrKeyDown[0] = true;
				g_SoundManager->PlaySFX("charge_up");
			}

			if (m_fThrowPower < m_fMaxThrowPower)
			{
				m_fThrowPower += m_fThrowPowerUpSpeed * TimeRevision;
			}
			if (m_fThrowPower > m_fMaxThrowPower - EPSILON)
			{
				m_fThrowPower = m_fMaxThrowPower;
				g_SoundManager->StopSFX("charge_up");
				g_SoundManager->PlaySFX("charge_complete");
			}
			if (m_pCharge)
				m_pCharge->UpdateCharging(m_fThrowPower, m_fMaxThrowPower);
			

			_DEBUG_COMMENT cout << "throw power : " << m_fThrowPower << endl;
		}
		break;
		default:;
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
					//g_SoundManager->PlaySFX("Melem");
				}
			}
		}
		break;
		default:;
		}
	}
	else if (data->wKey == m_pInputKey->interactableKey3)
	{
		if (m_arrKeyDown[2] == false)
		{
			m_arrKeyDown[2] = true;
			if (CurrentTime - m_arrElapsedTime[2] > m_arrCoolDown[2])
			{
				//dash
				D3DXVECTOR3 jump = m_vDirection;
				jump.y += .2f;
				D3DXVec3Normalize(&jump, &jump);
				SetPosition(m_vPosition.x, m_vPosition.y + 0.1f, m_vPosition.z);
				SetAcceleration(jump * 0.4f * TimeRevision);
				g_SoundManager->PlaySFX("dash");
				m_arrElapsedTime[2] = CurrentTime;
				D3DXMATRIXA16 localmat = *m_pSkinnedMesh->GetTransform();
				D3DXMatrixMultiply(&localmat, &localmat, &m_matWorld);
				m_pDashShadow->SetAnimation(&localmat);
				m_isDash = true;
			}
			//_DEBUG_COMMENT cout << "current time : " << g_pTimeManager->GetElapsedTime() << endl;
			_DEBUG_COMMENT cout << "cool down : " << CurrentTime - m_arrElapsedTime[2] << endl;
		}
	}
}

void CCharacter::ReleaseKey(void *_value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent *>(_value);
	const float &CurrentTime = g_pTimeManager->GetLastUpdateTime();
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
			g_SoundManager->StopSFX("charge_complete");
			g_SoundManager->PlaySFX("throw");
			m_fThrowPower = m_fMinThrowPower;
			if (m_pCharge)
				m_pCharge->SetChildActive(false);
			break;
		default:;
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
		default:;
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
	_DEBUG_COMMENT 	cout << "chara speed : " << m_fBaseSpeed << endl;
	_DEBUG_COMMENT 	
	_DEBUG_COMMENT }
	_DEBUG_COMMENT  else if (data->wKey == 'L')
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	m_fBaseSpeed -= 0.01f;
	_DEBUG_COMMENT 	cout << "chara speed : " << m_fBaseSpeed << endl;
	_DEBUG_COMMENT 	
	_DEBUG_COMMENT }
	_DEBUG_COMMENT else if (data->wKey == 'U')
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	m_fMaxThrowPower -= 0.01f;
	_DEBUG_COMMENT 	cout << "max throw power : " << m_fMaxThrowPower << endl;
	_DEBUG_COMMENT }
	_DEBUG_COMMENT else if (data->wKey == 'I')
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	m_fMaxThrowPower += 0.01f;
	_DEBUG_COMMENT 	cout << "max throw power : " << m_fMaxThrowPower << endl;
	_DEBUG_COMMENT 	
	_DEBUG_COMMENT }
}

void CCharacter::SetKeyChange(void *_value)
{
	ST_PLAYER_INPUTKEY *data = static_cast<ST_PLAYER_INPUTKEY *>(_value);
	m_pInputKey = data;
}

void CCharacter::Move()
{
	if (m_pCollision->GetIsCollide() == false && m_isMoveKeyDown)
	{
		AddForce(-m_vDirection * m_fBaseSpeed * m_pCC->MultiplySpeed() * TimeRevision);
	}
	

	m_vVelocity += m_vAcceleration;
	
	if(D3DXVec3Length(&m_vVelocity) > m_fMaxSpeed)
	{
		D3DXVec3Normalize(&m_vVelocity, &m_vVelocity);
		m_vVelocity *= m_fMaxSpeed;
	}
	
	m_vPosition += m_vVelocity;

	ST_TravelDistanceEvent data;
	data.fDistance = D3DXVec3Length(&m_vVelocity);
	g_EventManager->CallEvent(eEvent::TravelDistance, (void *)&data);

	if (m_vPosition.y < -50)
		Reset();

	D3DXMatrixTranslation(&m_matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
	SetForce();
}

void CCharacter::Rotate(float fTargetRot)
{
	if (m_isDash)
		return;

	fTargetRot += m_pCC->ReverseRotate();
	fTargetRot = fTargetRot < D3DX_PI * 2 ? fTargetRot : fTargetRot - D3DX_PI * 2;
	D3DXQUATERNION stLerpRot, stCurrentRot, stTargetRot;
	D3DXQuaternionRotationAxis(&stCurrentRot, &D3DXVECTOR3(0, 1, 0), m_fRotY);
	D3DXQuaternionRotationAxis(&stTargetRot, &D3DXVECTOR3(0, 1, 0), fTargetRot);

	D3DXQuaternionSlerp(&stLerpRot, &stCurrentRot, &stTargetRot, 0.3f);
	D3DXMatrixRotationQuaternion(&m_matR, &stLerpRot);
	
	D3DXVec3TransformNormal(&m_vDirection, &D3DXVECTOR3(0, 0, 1), &m_matR);
	m_matWorld = m_matS * m_matR * m_matT;

	SetForce(m_vDirection * m_fBaseSpeed * m_pCC->MultiplySpeed() * TimeRevision);

	m_isMoveKeyDown = true;
	if (m_pCollision)
		m_pCollision->Update();

	D3DXVECTOR3 vDummy;
	D3DXQuaternionToAxisAngle(&stLerpRot, &vDummy, &m_fRotY); // m_fRotY를 변경시켜주는 부분
}

void CCharacter::AddForce(const D3DXVECTOR3 &vForce)
{
	if (m_pParts)
		m_vAcceleration += vForce / (m_fMass + m_pParts->GetMass());
	else
		m_vAcceleration += vForce / m_fMass;
}

void CCharacter::SetForce(const D3DXVECTOR3 &vForce)
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

void CCharacter::SetCC(CCrowdControl *cc)
{
	SafeDelete(m_pCC);
	m_pCC = cc;
	m_pCC->SetTarget(&m_vGrabPartsPosition);
}

void CCharacter::CreateShadowMap()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pRenderShadowManager->GetCreateShadowShader()->SetMatrix("gWorldMatrix", &m_matWorld);
	UINT numPasses = 0;
	g_pRenderShadowManager->GetCreateShadowShader()->Begin(&numPasses, NULL);

	for (UINT i = 0; i < numPasses; ++i)
	{
		g_pRenderShadowManager->GetCreateShadowShader()->BeginPass(i);
		{
			m_pSkinnedMesh->Render(nullptr);
		}
		g_pRenderShadowManager->GetCreateShadowShader()->EndPass();
	}
	
	g_pRenderShadowManager->GetCreateShadowShader()->End();
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

	if (m_pParts)
	{
		SetPlayerState(ePlayerState::None);
		m_pParts->ThrowParts(m_vDirection * m_fThrowPower * TimeRevision);
		m_pParts = nullptr;
		m_fThrowPower = m_fMinThrowPower;
		if (m_pCharge)
			m_pCharge->SetChildActive(false);
	}
}

void CCharacter::SetAnimState()
{
	if (!m_pSkinnedMesh)
		return;

	switch (m_pSkinnedMesh->GetCurrentAnimIndex())
	{
	case Idle:
	{
		if (!m_pCC->IsMovable() || (m_pParts && m_pCC->StopWithParts()))
			m_pSkinnedMesh->SetAnimationIndexBlend(Stun);
		else if (m_isMoveKeyDown && D3DXVec3Length(&m_vVelocity) > EPSILON * 10)
			m_pSkinnedMesh->SetAnimationIndexBlend(Run);
	}
	break;
	case Run:
	{
		if (!m_pCC->IsMovable() || (m_pParts && m_pCC->StopWithParts()))
			m_pSkinnedMesh->SetAnimationIndexBlend(Stun);
		else if (!m_isMoveKeyDown || D3DXVec3Length(&m_vVelocity) < EPSILON * 10)
			m_pSkinnedMesh->SetAnimationIndexBlend(Idle);
	}
	break;
	case Spin:
	{
	}
	break;
	case Stun:
	{
		if (!(!m_pCC->IsMovable() || (m_pParts && m_pCC->StopWithParts())))
		{
			if (!m_isMoveKeyDown || D3DXVec3Length(&m_vVelocity) < EPSILON * 10)
				m_pSkinnedMesh->SetAnimationIndexBlend(Idle);
			else if (m_isMoveKeyDown && D3DXVec3Length(&m_vVelocity) > EPSILON * 10)
				m_pSkinnedMesh->SetAnimationIndexBlend(Run);
		}
	}
	break;
	default:
		break;
	}
}
