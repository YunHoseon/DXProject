#include "stdafx.h"
#include "CActor.h"
#include "ICollisionArea.h"


CActor::CActor() :
	m_pInteractCenter(nullptr),
	m_pCollision(nullptr),
	m_fRotY(D3DX_PI),
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0, 0),
	m_fBaseSpeed(0),
	m_fMass(1),
	m_fFriction(0), m_fRepulsivePower(0.00001f),
	m_vVelocity(0, 0, 0),
	m_vAcceleration(0, 0, 0),
	m_vScale(1, 1, 1),
	m_fFlexibility(1),
	m_isCollide(false)
{
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixRotationY(&m_matR, m_fRotY);
	//D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
	m_matWorld = m_matS * m_matR * m_matT;
}


CActor::~CActor()
{
	SafeDelete(m_pCollision);
}

bool CActor::Collide(CActor* target, D3DXVECTOR3* pNormal)
{
	if(m_pCollision && target->m_pCollision)
		return m_pCollision->Collide(target->m_pCollision, pNormal);
	return false;
}

void CActor::SetScale(const D3DXVECTOR3& vScale)
{
	m_vScale = vScale;
	D3DXMatrixScaling(&m_matS, vScale.x, vScale.y, vScale.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->SetScale(vScale.x, vScale.y, vScale.z);
}

void CActor::SetScale(float x, float y, float z)
{
	m_vScale = D3DXVECTOR3(x, y, z);
	D3DXMatrixScaling(&m_matS, x, y, z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->SetScale(x, y, z);
}

void CActor::Smallize()
{
	m_vScale *= 0.8f;
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->SetScale(m_vScale.x, m_vScale.y, m_vScale.z);
}

void CActor::Unsmallize()
{
	m_vScale /= 0.8f;
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->SetScale(m_vScale.x, m_vScale.y, m_vScale.z);
}

void CActor::SetPosition(D3DXVECTOR3 vPosition)
{
	m_vPosition = vPosition;
	D3DXMatrixTranslation(&m_matT, vPosition.x, vPosition.y, vPosition.z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
}

void CActor::SetPosition(float x, float y, float z)
{
	m_vPosition = D3DXVECTOR3(x, y, z);
	D3DXMatrixTranslation(&m_matT, x, y, z);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
}

void CActor::SetRotationY(float rot)
{
	m_fRotY = rot;
	D3DXMatrixRotationY(&m_matR, m_fRotY);
	m_matWorld = m_matS * m_matR * m_matT;
	if (m_pCollision)
		m_pCollision->Update();
}

void CActor::AddAcceleration(const D3DXVECTOR3& vAccel)
{
	m_vAcceleration += vAccel;
}

void CActor::SetAcceleration(const D3DXVECTOR3& vAccel)
{
	m_vAcceleration = vAccel;
}

void CActor::AddForce(const D3DXVECTOR3& vForce)
{
	m_vAcceleration += vForce / m_fMass;
}

void CActor::SetForce(const D3DXVECTOR3& vForce)
{
	m_vAcceleration = vForce / m_fMass;
}

