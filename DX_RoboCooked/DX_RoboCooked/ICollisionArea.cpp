#include "stdafx.h"
#include "ICollisionArea.h"

ICollisionArea::ICollisionArea(): m_eType(EColideType::E_Box), isCollide(false), stColor{}
{
	stColor[0] = D3DCOLOR_XRGB(0, 0, 0);
	stColor[1] = D3DCOLOR_XRGB(255, 255, 255);
}

bool ICollisionArea::Collide(ICollisionArea* pTargetCollider)
{
	if (pTargetCollider->m_eType == EColideType::E_Box)
		return CollideToBox(pTargetCollider);

	if (pTargetCollider->m_eType == EColideType::E_Sphere)
		return CollideToSphere(pTargetCollider);

	return false;
}
