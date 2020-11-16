﻿#include "stdafx.h"
#include "ICollisionArea.h"
#include "CBoxCollision.h"
#include "CSphereCollision.h"

ICollisionArea::ICollisionArea(): m_eType(EColideType::E_Box), isCollide(false), stColor{}, m_pmatWorldTM(nullptr)
{
	stColor[0] = D3DCOLOR_XRGB(255, 255, 255);
	stColor[1] = D3DCOLOR_XRGB(255, 0, 0);
}

bool ICollisionArea::Collide(ICollisionArea* pTargetCollider)
{
	if (pTargetCollider->m_eType == EColideType::E_Box)
		return CollideToBox(dynamic_cast<CBoxCollision*>(pTargetCollider));

	if (pTargetCollider->m_eType == EColideType::E_Sphere)
		return CollideToSphere(dynamic_cast<CSphereCollision*>(pTargetCollider));

	return false;
}