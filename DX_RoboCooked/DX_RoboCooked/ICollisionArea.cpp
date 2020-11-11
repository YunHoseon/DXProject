#include "stdafx.h"
#include "ICollisionArea.h"

bool ICollisionArea::Collide(ICollisionArea* pTargetCollider)
{
	if (pTargetCollider->m_eType == EColideType::E_Box)
		return CollideToBox(pTargetCollider);

	if (pTargetCollider->m_eType == EColideType::E_Sphere)
		return CollideToSphere(pTargetCollider);

	return false;
}
