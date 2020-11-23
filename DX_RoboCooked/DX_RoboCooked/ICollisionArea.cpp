#include "stdafx.h"
#include "ICollisionArea.h"
#include "CBoxCollision.h"
#include "CSphereCollision.h"

ICollisionArea::ICollisionArea(): m_eType(EColideType::E_Box), m_isCollide(false), m_isActive(true), m_stColor{},
                                  m_pmatWorldTM(nullptr)
{
	m_stColor[0] = D3DCOLOR_XRGB(255, 255, 255);
	m_stColor[1] = D3DCOLOR_XRGB(255, 0, 0);
}

bool ICollisionArea::Collide(ICollisionArea* pTargetCollider, D3DXVECTOR3* pNormal)
{
	if (!m_isActive || !pTargetCollider->m_isActive)
		return false;
	
	if (pTargetCollider->m_eType == EColideType::E_Box)
		return CollideToBox(dynamic_cast<CBoxCollision*>(pTargetCollider), pNormal);

	if (pTargetCollider->m_eType == EColideType::E_Sphere)
		return CollideToSphere(dynamic_cast<CSphereCollision*>(pTargetCollider), pNormal);

	return false;
}
