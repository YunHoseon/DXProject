#include "stdafx.h"
#include "CActor.h"
#include "ICollisionArea.h"


CActor::CActor()
	: m_pInteractCenter(nullptr)
	, m_pCollision(nullptr)
	, m_fRotY(0)
	, m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
	, m_fBaseSpeed(0)
	, m_fSpeed(m_fBaseSpeed)
	, m_fMass(1)
	, m_vVelocity(0,0,0)
	, m_vAcceleration(0,0,0)
{
	D3DXMatrixIdentity(&m_matS);
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixIdentity(&m_matT);
}


CActor::~CActor()
{
}

bool CActor::Collide(CActor* target, D3DXVECTOR3* pNormal)
{
	if(m_pCollision && target->m_pCollision)
		return m_pCollision->Collide(target->m_pCollision, pNormal);
	return false;
}

void CActor::AddForce(const D3DXVECTOR3& vForce)
{
	m_vAcceleration += vForce / m_fMass;
}

void CActor::SetForce(const D3DXVECTOR3& vForce)
{
	m_vAcceleration = vForce / m_fMass;
}

